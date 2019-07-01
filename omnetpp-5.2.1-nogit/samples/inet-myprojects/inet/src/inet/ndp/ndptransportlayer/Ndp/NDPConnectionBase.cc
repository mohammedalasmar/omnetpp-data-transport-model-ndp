#include <string.h>
#include <assert.h>

#include "inet/ndp/ndptransportlayer/contract/ndp/NDPCommand_m.h"
#include "inet/ndp/ndptransportlayer/Ndp/NDPConnection.h"
#include "ndp_common/NDPSegment.h"
#include "Ndp.h"
#include "NDPAlgorithm.h"
#include "NDPReceiveQueue.h"
#include "NDPSendQueue.h"


using namespace std;
namespace inet {

namespace ndp {

NDPStateVariables::NDPStateVariables() {
    internal_request_id = 0;
    request_id = 0;  // source block number (8-bit unsigned integer)

    numPacketsToGet = 0;
    numPacketsToSend = 0;
    priorityValue = 0;
    isLongFlow = false;
    isSender = false;
    isReceiver =false;

    numRcvTrimmedHeader = 0;
    numberReceivedPackets = 0;
    numberSentPackets=0;
    IW = 0; // send the initial window (12 Packets as in NDP) IWWWWWWWWWWWW
    connFinished= false;

    isfinalReceivedPrintedOut = false;
//    sequenceNumber = 0;

    numRcvdPkt=0;

    request_rexmit_count = 0;
    request_rexmit_timeout = 0;
    numPullsTimeOuts = 0;
    isHeader = false;
    connNotAddedYet = true;

    active = false;
    snd_mss = 0;
    iss = 0;

    syn_rexmit_count = 0;
    syn_rexmit_timeout = 0;
}

std::string NDPStateVariables::info() const {
    std::stringstream out;
    return out.str();
}

std::string NDPStateVariables::detailedInfo() const {
    std::stringstream out;
    out << "active=" << active << "\n";
    out << "snd_mss=" << snd_mss << "\n";
    out << "iss=" << iss << "\n";
    out << "irs=" << irs << "\n";
    return out.str();
}

NDPConnection::NDPConnection() {

}


NDPConnection::NDPConnection(Ndp *_mod, int _appGateIndex, int _connId) {
    ndpMain = _mod;
    appGateIndex = _appGateIndex;
    connId = _connId;

    char fsmname[24];
    sprintf(fsmname, "fsm-%d", connId);
    fsm.setName(fsmname);
    fsm.setState(NDP_S_INIT);

    // queues and algorithm will be created on active or passive open

    requestInternalTimer = new cMessage("requestInternalTimer");
    the2MSLTimer = new cMessage("2MSL");
    connEstabTimer = new cMessage("CONN-ESTAB");
    finWait2Timer = new cMessage("FIN-WAIT-2");
    synRexmitTimer = new cMessage("SYN-REXMIT");

    requestInternalTimer->setContextPointer(this);
    the2MSLTimer->setContextPointer(this);
    connEstabTimer->setContextPointer(this);
    finWait2Timer->setContextPointer(this);
    synRexmitTimer->setContextPointer(this);

    // statistics
    if (getNDPMain()->recordStatistics) {
//        sndWndVector = new cOutVector("send window");
    }


}

NDPConnection::~NDPConnection() {

    std::list<PakcetsToSend>::iterator iter;  // received iterator
//    iter = sentPakcetsList.begin();
//    while (!sentPakcetsList.empty()) {
//        delete sentPakcetsList.front().msg;
//        iter++;
//        sentPakcetsList.pop_front();
//    }

    while (!retransmitQueue.empty()) {
              std::cout << " destructor NDPConnection " << iter->pktId << " msgName "  << iter->msg->getFullName() << "\n";
        delete retransmitQueue.front().msg;
        iter++;
        retransmitQueue.pop_front();
    }



    while (!receivedPacketsList.empty()) {
        delete receivedPacketsList.front().msg;
        receivedPacketsList.pop_front();
    }

    delete sendQueue;
//    delete rexmitQueue;
    delete receiveQueue;
    delete ndpAlgorithm;
    delete state;

    if (the2MSLTimer)
        delete cancelEvent(the2MSLTimer);
    if (connEstabTimer)
        delete cancelEvent(connEstabTimer);
    if (finWait2Timer)
        delete cancelEvent(finWait2Timer);
    if (synRexmitTimer)
        delete cancelEvent(synRexmitTimer);
    if (requestInternalTimer)
        delete cancelEvent(requestInternalTimer);

    // statistics

//    delete sndSacksVector;
}

bool NDPConnection::processTimer(cMessage *msg) {
    printConnBrief();
    EV_DETAIL << msg->getName() << " timer expired\n";
    std::cout << msg->getFullPath() << " timer expired\n";

    // first do actions
    NDPEventCode event;

    if (msg == requestInternalTimer) {
        event = NDP_E_IGNORE;
        process_TIMEOUT_REQUEST_REXMIT();
//            sendRequest();   // based on my congestion control, I send requests after receiving  a packet not based on a timer
    }

    else if (msg == the2MSLTimer) {
        event = NDP_E_TIMEOUT_2MSL;
        process_TIMEOUT_2MSL();
    } else if (msg == connEstabTimer) {
        event = NDP_E_TIMEOUT_CONN_ESTAB;
        process_TIMEOUT_CONN_ESTAB();
    } else if (msg == finWait2Timer) {
        event = NDP_E_TIMEOUT_FIN_WAIT_2;
        process_TIMEOUT_FIN_WAIT_2();
    } else if (msg == synRexmitTimer) {
        event = NDP_E_IGNORE;
//        process_TIMEOUT_SYN_REXMIT(event);
    } else {
        event = NDP_E_IGNORE;
        ndpAlgorithm->processTimer(msg, event); // seeeee processTimer method in NDPBaseAlg.cc
    }

    // then state transitions
    return performStateTransition(event);
}



bool NDPConnection::processNDPSegment(NDPSegment *ndpseg, L3Address segSrcAddr, L3Address segDestAddr) {
    printConnBrief();
    NDPEventCode event = process_RCV_SEGMENT(ndpseg, segSrcAddr, segDestAddr);
    // then state transitions
    return performStateTransition(event);
}

 bool NDPConnection::processAppCommand(cMessage *msg) {
    printConnBrief();
    NDPCommand *ndpCommand = (NDPCommand *) (msg->removeControlInfo());
    NDPEventCode event = preanalyseAppCommandEvent(msg->getKind());
    EV_INFO << "App command eventName: " << eventName(event) << "\n";
//     std::cout << "App command: " << eventName(event) << std::endl;
    switch (event) {
    case NDP_E_OPEN_ACTIVE:
        process_OPEN_ACTIVE(event, ndpCommand, msg);
        break;

    case NDP_E_OPEN_PASSIVE:
        process_OPEN_PASSIVE(event, ndpCommand, msg);
        break;

    case NDP_E_CLOSE:
//        process_CLOSE(event, ndpCommand, msg);
        break;


    default:
        throw cRuntimeError(ndpMain, "wrong event code");
    }

    // then state transitions
    return performStateTransition(event);
}

NDPEventCode NDPConnection::preanalyseAppCommandEvent(int commandCode) {
    switch (commandCode) {
    case NDP_C_OPEN_ACTIVE:
        return NDP_E_OPEN_ACTIVE;

    case NDP_C_OPEN_PASSIVE:
        return NDP_E_OPEN_PASSIVE;

    case NDP_C_SEND:
        return NDP_E_SEND;

    case NDP_C_CLOSE:
        return NDP_E_CLOSE;

    default:
        throw cRuntimeError(ndpMain, "Unknown message kind in app command");
    }
}

bool NDPConnection::performStateTransition(const NDPEventCode& event) {
    ASSERT(fsm.getState() != NDP_S_CLOSED); // closed connections should be deleted immediately

    if (event == NDP_E_IGNORE) {    // e.g. discarded segment
        EV_DETAIL << "Staying in state: " << stateName(fsm.getState())
                         << " (no FSM event)\n";
        return true;
    }

    // state machine
    // TBD add handling of connection timeout event (KEEP-ALIVE), with transition to CLOSED
    // Note: empty "default:" lines are for gcc's benefit which would otherwise spit warnings
    int oldState = fsm.getState();

    switch (fsm.getState()) {
    case NDP_S_INIT:
        switch (event) {
        case NDP_E_OPEN_PASSIVE:
            FSM_Goto(fsm, NDP_S_LISTEN);
            break;

        case NDP_E_OPEN_ACTIVE:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);

//            FSM_Goto(fsm, NDP_S_SYN_SENT); mohhh
            break;

        default:
            break;
        }
        break;

    case NDP_S_LISTEN:
        switch (event) {
        case NDP_E_OPEN_ACTIVE:
            FSM_Goto(fsm, NDP_S_SYN_SENT);
            break;

        case NDP_E_SEND:
            FSM_Goto(fsm, NDP_S_SYN_SENT);
            break;

        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_SYN:
            FSM_Goto(fsm, NDP_S_SYN_RCVD);
            break;

        default:
            break;
        }
        break;

    case NDP_S_SYN_RCVD:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_1);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_CONN_ESTAB:
            FSM_Goto(fsm, state->active ? NDP_S_CLOSED : NDP_S_LISTEN);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, state->active ? NDP_S_CLOSED : NDP_S_LISTEN);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSE_WAIT);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_SYN_SENT:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_CONN_ESTAB:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_SYN_ACK:
            FSM_Goto(fsm, NDP_S_ESTABLISHED);
            break;

        case NDP_E_RCV_SYN:
            FSM_Goto(fsm, NDP_S_SYN_RCVD);
            break;

        default:
            break;
        }
        break;

    case NDP_S_ESTABLISHED:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_1);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSE_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_CLOSE_WAIT:
        switch (event) {
        case NDP_E_CLOSE:
            FSM_Goto(fsm, NDP_S_LAST_ACK);
            break;

        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_LAST_ACK:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_FIN_WAIT_1:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_CLOSING);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_FIN_WAIT_2);
            break;

        case NDP_E_RCV_FIN_ACK:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_FIN_WAIT_2:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_FIN:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_TIMEOUT_FIN_WAIT_2:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_CLOSING:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_ACK:
            FSM_Goto(fsm, NDP_S_TIME_WAIT);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_TIME_WAIT:
        switch (event) {
        case NDP_E_ABORT:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_TIMEOUT_2MSL:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_RST:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        case NDP_E_RCV_UNEXP_SYN:
            FSM_Goto(fsm, NDP_S_CLOSED);
            break;

        default:
            break;
        }
        break;

    case NDP_S_CLOSED:
        break;
    }

    if (oldState != fsm.getState()) {
        EV_INFO << "Transition: " << stateName(oldState) << " --> "
                       << stateName(fsm.getState()) << "  (event was: "
                       << eventName(event) << ")\n";
        EV_DEBUG_C("testing") << ndpMain->getName() << ": "
                                     << stateName(oldState) << " --> "
                                     << stateName(fsm.getState()) << "  (on "
                                     << eventName(event) << ")\n";

        // cancel timers, etc.
        stateEntered(fsm.getState(), oldState, event);
    } else {
        EV_DETAIL << "Staying in state: " << stateName(fsm.getState())
                         << " (event was: " << eventName(event) << ")\n";
    }

    return fsm.getState() != NDP_S_CLOSED;
}

void NDPConnection::stateEntered(int state, int oldState, NDPEventCode event) {
    // cancel timers
    switch (state) {
    case NDP_S_INIT:
        // we'll never get back to INIT
        break;

    case NDP_S_LISTEN:
        // we may get back to LISTEN from SYN_RCVD
        ASSERT(connEstabTimer && synRexmitTimer);
        cancelEvent(connEstabTimer);
        cancelEvent(synRexmitTimer);
        break;

    case NDP_S_SYN_RCVD:
    case NDP_S_SYN_SENT:
        break;

    case NDP_S_ESTABLISHED:
        // we're in ESTABLISHED, these timers are no longer needed
        delete cancelEvent(connEstabTimer);
        delete cancelEvent(synRexmitTimer);
        connEstabTimer = synRexmitTimer = nullptr;
        // NDP_I_ESTAB notification moved inside event processing
        break;

    case NDP_S_CLOSE_WAIT:
    case NDP_S_LAST_ACK:
    case NDP_S_FIN_WAIT_1:
    case NDP_S_FIN_WAIT_2:
    case NDP_S_CLOSING:
        if (state == NDP_S_CLOSE_WAIT)
            sendIndicationToApp(NDP_I_PEER_CLOSED);
        // whether connection setup succeeded (ESTABLISHED) or not (others),
        // cancel these timers
        if (connEstabTimer)
            cancelEvent(connEstabTimer);
        if (synRexmitTimer)
            cancelEvent(synRexmitTimer);
        break;

    case NDP_S_TIME_WAIT:
        sendIndicationToApp(NDP_I_CLOSED);
        break;

    case NDP_S_CLOSED:
        if (oldState != NDP_S_TIME_WAIT && event != NDP_E_ABORT)
            sendIndicationToApp(NDP_I_CLOSED);
        // all timers need to be cancelled
        if (the2MSLTimer)
            cancelEvent(the2MSLTimer);
        if (connEstabTimer)
            cancelEvent(connEstabTimer);
        if (finWait2Timer)
            cancelEvent(finWait2Timer);
        if (synRexmitTimer)
            cancelEvent(synRexmitTimer);
        ndpAlgorithm->connectionClosed();
        break;
    }
}

} // namespace NDP

} // namespace inet


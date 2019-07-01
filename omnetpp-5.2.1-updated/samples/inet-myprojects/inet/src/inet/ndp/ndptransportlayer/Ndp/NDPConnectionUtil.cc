// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

#include <string.h>
#include <algorithm>

#include "inet/ndp/ndptransportlayer/contract/ndp/NDPCommand_m.h"
#include "inet/ndp/ndptransportlayer/Ndp/NDPConnection.h"
#include "inet/networklayer/contract/IL3AddressType.h"
#include "inet/networklayer/contract/INetworkProtocolControlInfo.h"
#include "inet/networklayer/common/IPProtocolId_m.h"
#include "inet/common/INETUtils.h"

#include "inet/ndp/application/ndpapp/GenericAppMsgNdp_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "ndp_common/NDPSegment.h"
#include "Ndp.h"
#include "NDPAlgorithm.h"
#include "NDPReceiveQueue.h"
#include "NDPSendQueue.h"

namespace inet {

namespace ndp {

//
// helper functions
//

const char *NDPConnection::stateName(int state) {
#define CASE(x)    case x: \
        s = #x + 5; break
    const char *s = "unknown";
    switch (state) {
    CASE(NDP_S_INIT)
;        CASE(NDP_S_CLOSED);
        CASE(NDP_S_LISTEN);
        CASE(NDP_S_ESTABLISHED);
    }
    return s;
#undef CASE
}

const char *NDPConnection::eventName(int event) {
#define CASE(x)    case x: \
        s = #x + 5; break
    const char *s = "unknown";
    switch (event) {
    CASE(NDP_E_IGNORE)
;        CASE(NDP_E_OPEN_ACTIVE);
        CASE(NDP_E_OPEN_PASSIVE);
        CASE(NDP_E_SEND);
        CASE(NDP_E_CLOSE);
    }
    return s;
#undef CASE
}

const char *NDPConnection::indicationName(int code) {
#define CASE(x)    case x: \
        s = #x + 5; break
    const char *s = "unknown";
    switch (code) {
    CASE(NDP_I_DATA)
;        CASE(NDP_I_URGENT_DATA);
        CASE(NDP_I_ESTABLISHED);
    }
    return s;
#undef CASE
}



void NDPConnection::sendToIP(NDPSegment *ndpseg, L3Address src, L3Address dest) {
    EV_INFO << "Sending: ";
    printSegmentBrief(ndpseg);

    IL3AddressType *addressType = dest.getAddressType();
    INetworkProtocolControlInfo *controlInfo = addressType->createNetworkProtocolControlInfo();
    controlInfo->setTransportProtocol(IP_PROT_TCP);
    controlInfo->setSourceAddress(src);
    controlInfo->setDestinationAddress(dest);
    ndpseg->setControlInfo(check_and_cast<cObject *>(controlInfo));
    ndpseg->setByteLength(ndpseg->getHeaderLength() + ndpseg->getPayloadLength());
    check_and_cast<Ndp *>(getSimulation()->getContextModule())->send(ndpseg,"ipOut");
}

NDPSegment *NDPConnection::createNDPSegment(const char *name) {
    return new NDPSegment(name);
}

void NDPConnection::signalConnectionTimeout() {
    sendIndicationToApp(NDP_I_TIMED_OUT);
}

void NDPConnection::sendIndicationToApp(int code, const int id) {
    EV_INFO << "Notifying app: " << indicationName(code) << "\n";
    cMessage *msg = new cMessage(indicationName(code));
    msg->setKind(code);
    NDPCommand *ind = new NDPCommand();
    ind->setNumRcvTrimmedHeader(state->numRcvTrimmedHeader);
    ind->setConnId(connId);
    ind->setUserId(id);
    msg->setControlInfo(ind);
    sendToApp(msg);
}

void NDPConnection::sendEstabIndicationToApp() {
    EV_INFO << "Notifying app: " << indicationName(NDP_I_ESTABLISHED) << "\n";
    cMessage *msg = new cMessage(indicationName(NDP_I_ESTABLISHED));
    msg->setKind(NDP_I_ESTABLISHED);

    NDPConnectInfo *ind = new NDPConnectInfo();
    ind->setConnId(connId);
    ind->setLocalAddr(localAddr);
    ind->setRemoteAddr(remoteAddr);
    ind->setLocalPort(localPort);
    ind->setRemotePort(remotePort);
    msg->setControlInfo(ind);
    sendToApp(msg);
}

void NDPConnection::sendToApp(cMessage *msg) {
    ndpMain->send(msg, "appOut", appGateIndex);
}

void NDPConnection::initConnection(NDPOpenCommand *openCmd) {

//
    sendQueue = ndpMain->createSendQueue();
//    receiveQueue = ndpMain->createReceiveQueue();
//
    sendQueue->setConnection(this);
//    receiveQueue->setConnection(this);

    const char *ndpAlgorithmClass = openCmd->getNdpAlgorithmClass();
    if (!ndpAlgorithmClass || !ndpAlgorithmClass[0])
        ndpAlgorithmClass = ndpMain->par("ndpAlgorithmClass");
    ndpAlgorithm = check_and_cast<NDPAlgorithm *>( inet::utils::createOne(ndpAlgorithmClass));
    ndpAlgorithm->setConnection(this);
    // create state block
    state = ndpAlgorithm->getStateVariables();
    configureStateVariables();
    ndpAlgorithm->initialize();
}

void NDPConnection::configureStateVariables() {
    state->IW = ndpMain->par("initialWindow");
    ndpMain->recordScalar("initialWindow=", state->IW);

    state->snd_mss = ndpMain->par("mss").longValue(); // Maximum Segment Size

}

void NDPConnection::selectInitialSeqNum() {
    // set the initial send sequence number
    state->iss = (unsigned long) fmod(SIMTIME_DBL(simTime()) * 250000.0,
            1.0 + (double) (unsigned) 0xffffffffUL) & 0xffffffffUL;

}



void NDPConnection::sendToIP(NDPSegment *ndpseg) {
    // final touches on the segment before sending
    ndpseg->setSrcPort(localPort);
    ndpseg->setDestPort(remotePort);

    ASSERT(ndpseg->getHeaderLength() >= NDP_HEADER_OCTETS); // NDP_HEADER_OCTETS = 20 (without options)
    ASSERT(ndpseg->getHeaderLength() <= NDP_MAX_HEADER_OCTETS); // NDP_MAX_HEADER_OCTETS = 60
    ndpseg->setByteLength(ndpseg->getHeaderLength() + ndpseg->getPayloadLength());
//    state->sentBytes = ndpseg->getPayloadLength(); // resetting sentBytes to 0 if sending a segment without data (e.g. ACK)

    EV_INFO << "Sending: ";
    printSegmentBrief(ndpseg);
    // TBD reuse next function for sending
    IL3AddressType *addressType = remoteAddr.getAddressType();
    INetworkProtocolControlInfo *controlInfo = addressType->createNetworkProtocolControlInfo();
    controlInfo->setTransportProtocol(IP_PROT_TCP); // TODO NDP ???
    controlInfo->setSourceAddress(localAddr);
    controlInfo->setDestinationAddress(remoteAddr);
    ndpseg->setControlInfo(check_and_cast<cObject *>(controlInfo));
    ndpMain->send(ndpseg, "ipOut");
}




// the receiver sends NACK when receiving a header
void NDPConnection::sendNackNdp(unsigned int nackNum) {
    NDPSegment *ndpseg = createNDPSegment("NACK");

    ndpseg->setAckBit(false);
    ndpseg->setNackBit(true);
    ndpseg->setNackNo(nackNum);

    ndpseg->setPayloadLength(1); // ooooooooo
    ndpseg->setSynBit(false);

    ndpseg->setIsDataPacket(false);
    ndpseg->setIsPullPacket(false);
    ndpseg->setIsHeader(false);

    // write header options
    writeHeaderOptions(ndpseg);

    // send it
    sendToIP(ndpseg);
}


void NDPConnection::sendAckNdp(unsigned int AckNum) {

    NDPSegment *ndpseg = createNDPSegment("ACK");
    ndpseg->setAckBit(true);
    ndpseg->setAckNo(AckNum);

    ndpseg->setNackBit(false);
    ndpseg->setPayloadLength(0);

    ndpseg->setSynBit(false);
    ndpseg->setIsDataPacket(false);
    ndpseg->setIsPullPacket(false);
    ndpseg->setIsHeader(false);

    // write header options
    writeHeaderOptions(ndpseg);

    // send it
    sendToIP(ndpseg);  // MOH: HAS BEEN REMOVED

    // notify
    ndpAlgorithm->ackSent(); //???????
}


void NDPConnection::sendRequestSegment() {
//    char msgname[16];
//
//    sprintf(msgname, "PULL-%d", state->request_id);
//    NDPSegment *ndpseg = createNDPSegment(msgname);
//    ndpseg->setPayloadLength(1);
//
//
//    ndpseg->setIsDataPacket(false);
//    ndpseg->setIsPullPacket(true);
//    ndpseg->setIsHeader(false);
//    ndpseg->setAckBit(false);
//    ndpseg->setNackBit(false);
//    ndpseg->setPullSequenceNumber(state->request_id);
}

// Added MOH
void NDPConnection::sendRequest() {
//    EV << " sending a new request \n";
//    sendRequestSegment();
}





bool NDPConnection::sendData(bool fullSegmentsOnly, uint32 congestionWindow, bool isReader ,bool isWriter,  unsigned int opcode) {
        return true;
}




const char *NDPConnection::optionName(int option) {
    switch (option) {
    case NDPOPTION_END_OF_OPTION_LIST:
        return "EOL";

    case NDPOPTION_NO_OPERATION:
        return "NOP";

    case NDPOPTION_MAXIMUM_SEGMENT_SIZE:
        return "MSS";

    case NDPOPTION_WINDOW_SCALE:
        return "WS";

    case NDPOPTION_SACK_PERMITTED:
        return "SACK_PERMITTED";

    case NDPOPTION_SACK:
        return "SACK";

    case NDPOPTION_TIMESTAMP:
        return "TS";

    default:
        return "unknown";
    }
}

void NDPConnection::printConnBrief() const {
    EV_DETAIL << "Connection " << localAddr << ":" << localPort << " to "
                     << remoteAddr << ":" << remotePort << "  on app["
                     << appGateIndex << "], connId=" << connId << "  in "
                     << stateName(fsm.getState()) << "\n";
}

void NDPConnection::printSegmentBrief(NDPSegment *ndpseg) {
    EV_INFO << "." << ndpseg->getSrcPort() << " > ";
    EV_INFO << "." << ndpseg->getDestPort() << ": ";

    if (ndpseg->getSynBit())
        EV_INFO << (ndpseg->getAckBit() ? "SYN+ACK " : "SYN ");

    if (ndpseg->getFinBit())
        EV_INFO << "FIN(+ACK) ";

    if (ndpseg->getRstBit())
        EV_INFO << (ndpseg->getAckBit() ? "RST+ACK " : "RST ");

    if (ndpseg->getPshBit())
        EV_INFO << "PSH ";

    if (ndpseg->getPayloadLength() > 0 || ndpseg->getSynBit()) {
        EV_INFO << "[" << ndpseg->getDataSequenceNumber() << ".."
                       << (ndpseg->getDataSequenceNumber() + ndpseg->getPayloadLength())
                       << ") ";
        EV_INFO << "(l=" << ndpseg->getPayloadLength() << ") ";
    }

    if (ndpseg->getAckBit())
        EV_INFO << "ack " << ndpseg->getAckNo() << " ";

    if (ndpseg->getHeaderLength() > NDP_HEADER_OCTETS) { // Header options present? NDP_HEADER_OCTETS = 20
        EV_INFO << "options ";

        for (uint i = 0; i < ndpseg->getHeaderOptionArraySize(); i++) {
            const NDPOption *option = ndpseg->getHeaderOption(i);
            short kind = option->getKind();
            EV_INFO << optionName(kind) << " ";
        }
    }
    EV_INFO << "\n";
}



void NDPConnection::sendRst(uint32 seq, L3Address src, L3Address dest,
        int srcPort, int destPort) {
    NDPSegment *ndpseg = createNDPSegment("RST");

    ndpseg->setSrcPort(srcPort);
    ndpseg->setDestPort(destPort);

    ndpseg->setRstBit(true);
    ndpseg->setDataSequenceNumber(seq);

    // send it
    sendToIP(ndpseg, src, dest);
}

void NDPConnection::sendRstAck(uint32 seq, uint32 ack, L3Address src,
        L3Address dest, int srcPort, int destPort) {
    NDPSegment *ndpseg = createNDPSegment("RST+ACK");

    ndpseg->setSrcPort(srcPort);
    ndpseg->setDestPort(destPort);

    ndpseg->setRstBit(true);
    ndpseg->setAckBit(true);
    ndpseg->setDataSequenceNumber(seq);
    ndpseg->setAckNo(ack);

    // send it
    sendToIP(ndpseg, src, dest);

    // notify
    if (ndpAlgorithm)
        ndpAlgorithm->ackSent();
}

void NDPConnection::readHeaderOptions(NDPSegment *ndpseg) {
    EV_INFO << "NDP Header Option(s) received:\n";

    for (uint i = 0; i < ndpseg->getHeaderOptionArraySize(); i++) {
        const NDPOption *option = ndpseg->getHeaderOption(i);
        short kind = option->getKind();
        short length = option->getLength();
        bool ok = true;

        EV_DETAIL << "Option type " << kind << " (" << optionName(kind)
                         << "), length " << length << "\n";

        switch (kind) {
        case NDPOPTION_END_OF_OPTION_LIST:    // EOL=0
        case NDPOPTION_NO_OPERATION:    // NOP=1
            if (length != 1) {
                EV_ERROR << "ERROR: option length incorrect\n";
                ok = false;
            }
            break;

        case NDPOPTION_MAXIMUM_SEGMENT_SIZE:    // MSS=2
            ok = processMSSOption(ndpseg,
                    *check_and_cast<const NDPOptionMaxSegmentSize *>(option));
            break;
            // TODO add new NDPOptions here once they are implemented
            // TODO delegate to NDPAlgorithm as well -- it may want to recognized additional options

        default:
            EV_ERROR << "ERROR: Unsupported NDP option kind " << kind << "\n";
            break;
        }
        (void) ok;    // unused
    }
}

bool NDPConnection::processMSSOption(NDPSegment *ndpseg,
        const NDPOptionMaxSegmentSize& option) {
    if (option.getLength() != 4) {
        EV_ERROR << "ERROR: MSS option length incorrect\n";
        return false;
    }

    if (fsm.getState() != NDP_S_LISTEN && fsm.getState() != NDP_S_SYN_SENT) {
        EV_ERROR
                        << "ERROR: NDP Header Option MSS received, but in unexpected state\n";
        return false;
    }

    state->snd_mss = std::min(state->snd_mss,
            (uint32) option.getMaxSegmentSize());

    if (state->snd_mss == 0)
        state->snd_mss = 536;

    EV_INFO << "NDP Header Option MSS(=" << option.getMaxSegmentSize()
                   << ") received, SMSS is set to " << state->snd_mss << "\n";
    return true;
}






NDPSegment NDPConnection::writeHeaderOptions(NDPSegment *ndpseg) {
    // SYN flag set and connetion in INIT or LISTEN state (or after synRexmit timeout)
    if (ndpseg->getSynBit()  && (fsm.getState() == NDP_S_INIT || fsm.getState() == NDP_S_LISTEN
                    || ((fsm.getState() == NDP_S_SYN_SENT
                            || fsm.getState() == NDP_S_SYN_RCVD)
                            && state->syn_rexmit_count > 0))) {
        // MSS header option
        if (state->snd_mss > 0) {
            NDPOptionMaxSegmentSize *option = new NDPOptionMaxSegmentSize();
            option->setMaxSegmentSize(state->snd_mss);
            ndpseg->addHeaderOption(option);
            EV_INFO << "NDP Header Option MSS(=" << state->snd_mss << ") sent\n";
        }



        // TODO add new NDPOptions here once they are implemented
    }

    if (ndpseg->getHeaderOptionArraySize() != 0) {
        uint options_len = ndpseg->getHeaderOptionArrayLength();
        if (options_len <= NDP_OPTIONS_MAX_SIZE) // Options length allowed? - maximum: 40 Bytes
            ndpseg->setHeaderLength(NDP_HEADER_OCTETS + options_len); // NDP_HEADER_OCTETS = 20
        else {
            ndpseg->setHeaderLength(NDP_HEADER_OCTETS);   // NDP_HEADER_OCTETS = 20
            ndpseg->dropHeaderOptions();    // drop all options
            EV_ERROR << "ERROR: Options length exceeded! Segment will be sent without options" << "\n";
        }
    }

    return *ndpseg;
}

uint32 NDPConnection::getTSval(NDPSegment *ndpseg) const {
    for (uint i = 0; i < ndpseg->getHeaderOptionArraySize(); i++) {
        const NDPOption *option = ndpseg->getHeaderOption(i);
        if (option->getKind() == NDPOPTION_TIMESTAMP)
            return check_and_cast<const NDPOptionTimestamp *>(option)->getSenderTimestamp();
    }

    return 0;
}

uint32 NDPConnection::getTSecr(NDPSegment *ndpseg) const {
    for (uint i = 0; i < ndpseg->getHeaderOptionArraySize(); i++) {
        const NDPOption *option = ndpseg->getHeaderOption(i);
        if (option->getKind() == NDPOPTION_TIMESTAMP)
            return check_and_cast<const NDPOptionTimestamp *>(option)->getEchoedTimestamp();
    }

    return 0;
}




uint32 NDPConnection::convertSimtimeToTS(simtime_t simtime) {
    ASSERT(SimTime::getScaleExp() <= -3);

    uint32 timestamp = (uint32) (simtime.inUnit(SIMTIME_MS));
    return timestamp;
}

simtime_t NDPConnection::convertTSToSimtime(uint32 timestamp) {
    ASSERT(SimTime::getScaleExp() <= -3);

    simtime_t simtime(timestamp, SIMTIME_MS);
    return simtime;
}



} // namespace ndp

} // namespace inet


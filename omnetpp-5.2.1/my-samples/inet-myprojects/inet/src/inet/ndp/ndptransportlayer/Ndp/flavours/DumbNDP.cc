

#include "../../../ndptransportlayer/Ndp/flavours/DumbNDP.h"

#include "../Ndp.h"

namespace inet {

namespace ndp {

Register_Class(DumbNDP);

// just a dummy value
#define REXMIT_TIMEOUT    2

DumbNDP::DumbNDP() : NDPAlgorithm(),
    state((DumbNDPStateVariables *&)NDPAlgorithm::state)
{
    rexmitTimer = nullptr;
}

DumbNDP::~DumbNDP()
{
    // cancel and delete timers
    if (rexmitTimer)
        delete conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNDP::initialize()
{
    NDPAlgorithm::initialize();

    rexmitTimer = new cMessage("DumbNDP-REXMIT");
    rexmitTimer->setContextPointer(conn);
}

void DumbNDP::established(bool active)
{
    if (active) {
        // finish connection setup with ACK (possibly piggybacked on data)
        EV_INFO << "Completing connection setup by sending ACK (possibly piggybacked on data)\n";

        if (!conn->sendData(false, 65535,true, 1, 1 )) // modified moh
            std::cout << "\n";
//            conn->sendAck();
    }
}

void DumbNDP::connectionClosed()
{
    conn->getNDPMain()->cancelEvent(rexmitTimer);
}

void DumbNDP::processTimer(cMessage *timer, NDPEventCode& event)
{
    if (timer != rexmitTimer)
        throw cRuntimeError(timer, "unrecognized timer");

//    conn->retransmitData();
    conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

void DumbNDP::sendCommandInvoked(cMessage *msg)
{
    // start sending
    conn->sendData(false, 65535 ,true, 1 ,1); // modified moh
}

void DumbNDP::receivedOutOfOrderSegment()
{
    EV_INFO << "Out-of-order segment, sending immediate ACK\n";
//    conn->sendAck();
}

void DumbNDP::receiveSeqChanged()
{
    // new data received, ACK immediately (more sophisticated algs should
    // wait a little to see if piggybacking is possible)
//    EV_INFO << "rcv_nxt changed to " << state->rcv_nxt << ", sending immediate ACK\n";
//    conn->sendAck();
}

void DumbNDP::receivedDataAck(uint32)
{
    // ack may have freed up some room in the window, try sending.
    // small segments also OK (Nagle off)
    conn->sendData(false, 65535,true, 1 ,1 );// modified moh
}

void DumbNDP::receivedDuplicateAck()
{
//    EV_INFO << "Duplicate ACK #" << state->dupacks << "\n";
}

void DumbNDP::receivedAckForDataNotYetSent(uint32 seq)
{
    EV_INFO << "ACK acks something not yet sent, sending immediate ACK\n";
//    conn->sendAck();
}

void DumbNDP::ackSent()
{
}

void DumbNDP::dataSent(uint32 fromseq)
{
    if (rexmitTimer->isScheduled())
     conn->getNDPMain()->cancelEvent(rexmitTimer);
     conn->scheduleTimeout(rexmitTimer, REXMIT_TIMEOUT);
}

void DumbNDP::segmentRetransmitted(uint32 fromseq, uint32 toseq)
{
}

void DumbNDP::restartRexmitTimer()
{
}

void DumbNDP::rttMeasurementCompleteUsingTS(uint32 echoedTS)
{
}

void DumbNDP::cancelRexmitTimer()
{
}

} // namespace NDP

} // namespace inet


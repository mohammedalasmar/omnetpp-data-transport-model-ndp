
#include "inet/common/INETDefs.h"

#include "inet/common/queue/NDPQueue.h"
//#include "inet/networklayer/ipv4/IPv4Datagram_m.h"
#include "inet/networklayer/ipv4/IPv4Datagram.h"

#include <omnetpp.h>
// #include "inet/raptorqimplementation/rqtransportlayer/RaptorQ/raptorq_common/RQSegment.h"
 #include "inet/ndp/ndptransportlayer/Ndp/ndp_common/NDPSegment.h"

#include "inet/transportlayer/tcp_common/TCPSegment.h"  //MOH: added
//using namespace inet::raptorq;
namespace inet {

Define_Module(NDPQueue);

simsignal_t NDPQueue::dataQueueLengthSignal = registerSignal("dataQueueLength");
simsignal_t NDPQueue::headersQueueLengthSignal = registerSignal("headersQueueLength");
simsignal_t NDPQueue::synAckQueueLengthSignal = registerSignal("synAckQueueLength");
simsignal_t NDPQueue::numTrimmedPktSig = registerSignal("numTrimmedPkt");

void NDPQueue::initialize()
{
    PassiveQueueBase::initialize();
    numTrimmedPacketsVec.setName("numTrimmedPacketsVec");
    weight=10;
    dataQueueLength = 0 ;
    headersQueueLength = 0;
    synAckQueueLength=0;
    numTrimmedPkt=0;

    WATCH(dataQueueLength);
    WATCH(headersQueueLength);
    WATCH(synAckQueueLength);
    WATCH(numTrimmedPkt);

    dataQueue.setName("dataQueue");
    headersQueue.setName("headerQueue");
    synAckQueue.setName("synAckQueue");


    //statistics
    emit(dataQueueLengthSignal, dataQueue.getLength());
    emit(headersQueueLengthSignal, headersQueue.getLength());
    emit(numTrimmedPktSig, numTrimmedPkt);

    outGate = gate("out");

    // configuration
    frameCapacity = par("frameCapacity");
    // moh added
    recordScalar("frameCapacity= ", frameCapacity);
}

cMessage *NDPQueue::enqueue(cMessage *msg)
{
//    std::cout << "  NDPQueue::enqueue.\n";
    IPv4Datagram *ipv4Datagram = dynamic_cast<IPv4Datagram *>(PK(msg));



//      raptorq::RQSegment *rqSeg = dynamic_cast<raptorq::RQSegment *>(ipv4Datagram->getEncapsulatedPacket());

      ndp::NDPSegment *rqSeg = dynamic_cast<ndp::NDPSegment *>(ipv4Datagram->getEncapsulatedPacket());
//
    if ( rqSeg->getAckBit()==true || rqSeg->getSynBit()==true || rqSeg->getNackBit()==true) { // getNACK for NDP not RQ (use this line with NDP)
//  if ( rqSeg->getAckBit()==true || rqSeg->getSynBit()==true) {   // this line for RQ and TCP not NDP
        synAckQueue.insert(msg);
        synAckQueueLength=synAckQueue.getLength();
        emit(synAckQueueLengthSignal, synAckQueue.getLength());
        return nullptr;
    }

    if (rqSeg->getIsHeader() == true ) {
//        std::cout << "  getIsHeader.\n";

        headersQueue.insert(msg);
        headersQueueLength = headersQueue.getLength();
        emit(headersQueueLengthSignal, headersQueue.getLength());
        return nullptr;
    }

    if (rqSeg->getIsPullPacket() == true ) {
//        std::cout << "  getIsHeader.\n";
        headersQueue.insert(msg);
        headersQueueLength = headersQueue.getLength();
        emit(headersQueueLengthSignal, headersQueue.getLength());

        return nullptr;
    }


    // dataQueue is Full ==> trim and insert header in the headersQueue
//    if ( dataQueue.getLength() >= frameCapacity || rqSeg->getAckBit()==true || rqSeg->getSynBit()==true) {
    if ( dataQueue.getLength() >= frameCapacity) {
//        std::cout << "Queue full, trimming packet.\n";
//        ipv4Datagram->decapsulate(); //no need to remove the transport segment, which is added below with zero payLoad length

        std::string header="Header-";

        if (rqSeg != nullptr) {
            std::string name=rqSeg->getName();
            std::string rename=header+name;
            rqSeg->setName(rename.c_str());
//            rqSeg->setPayloadLength(1);
            rqSeg->setIsHeader(true);
            rqSeg->setIsDataPacket(false);


//            ipv4Datagram->encapsulate(rqSeg); no need
//            ipv4Datagram->setTotalLengthField(1); no need
              ipv4Datagram->setName(rename.c_str());
              ipv4Datagram->setByteLength(0);

             //            std::cout  << "  !******************  Receiver $$$$$$$$$$$$$$$$$  HEADER arrived.  " << std::endl;

            unsigned short srcPort = rqSeg->getSrcPort();
            unsigned short destPort = rqSeg->getDestPort();
            EV << "   hhh   " << srcPort << "\n\n\n\n";
            EV << "   hhh   " << destPort << "\n\n\n\n";
            EV << "   hhh   " << rqSeg->getFullName() << "\n\n\n\n";
        }

//        cMessage *msg = dynamic_cast<cMessage *>(ipv4Datagram); no need
//        EV << "   hhh getDestAddress " << ipv4Datagram->getDestAddress().str() << "\n";
//        EV << "   hhh  getSrcAddress" << ipv4Datagram->getSrcAddress().str() << "\n\n\n\n";

        headersQueue.insert(msg);
        headersQueueLength=headersQueue.getLength();
        emit(headersQueueLengthSignal, headersQueue.getLength());


        ++numTrimmedPkt;
        numTrimmedPacketsVec.record(numTrimmedPkt);
        emit(numTrimmedPktSig, numTrimmedPkt);

        return nullptr;
//        return msg;
    } else {
       // dataQueue is not full ==> insert the incoming packet in the dataQueue
        dataQueue.insert(msg);
        emit(dataQueueLengthSignal, dataQueue.getLength());
        dataQueueLength=dataQueue.getLength();
        return nullptr;
    }
    return nullptr;
}


cMessage *NDPQueue::dequeue() {
    if (dataQueue.isEmpty() && headersQueue.isEmpty() && synAckQueue.isEmpty())
        return nullptr;
//    std::cout << "  NDPQueue::dequeue()  \n";


    if (synAckQueue.getLength()!=0){
        cMessage *msg = (cMessage *) synAckQueue.pop();
        emit(synAckQueueLengthSignal, synAckQueue.getLength());
        return msg;
    }

    if (headersQueue.getLength() == 0 && dataQueue.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueue.pop();
        emit(dataQueueLengthSignal, dataQueue.getLength());
        return msg;
    }

    if (headersQueue.getLength() != 0 && dataQueue.getLength() == 0) {
        cMessage *msg = (cMessage *) headersQueue.pop();
        emit(headersQueueLengthSignal, headersQueue.getLength());
        return msg;
    }

    if ( headersQueue.getLength() != 0 && dataQueue.getLength() != 0 && weight%10 == 0) {
        cMessage *msg = (cMessage *) dataQueue.pop();
        emit(dataQueueLengthSignal, dataQueue.getLength());
        ++weight;
        return msg;
    }

    if (headersQueue.getLength() != 0 && dataQueue.getLength() != 0 ) {
        cMessage *msg = (cMessage *) headersQueue.pop();

        EV_INFO << " get from header queue- size = " << PK(msg)->getByteLength() << "\n\n\n\n\n\n";
        emit(headersQueueLengthSignal, headersQueue.getLength());
        ++weight;
        return msg;
    }
    return nullptr;
 }

void NDPQueue::sendOut(cMessage *msg)
{
    send(msg, outGate);
}

bool NDPQueue::isEmpty()
{
    bool a = headersQueue.isEmpty();
    bool b = synAckQueue.isEmpty();
    bool c = dataQueue.isEmpty();
    bool d;
    if (a == true && b == true && c == true) {
        d = true;
    }
    else {
        d = false;
    }

    return d;
//    return  dataQueue.isEmpty();
}


void NDPQueue::refreshDisplay() const
{
     char buf[100];
    sprintf(buf, "q dataLen: %d\nq headersLen: %d\nq rcvd: %d\nq dropped: %d", dataQueueLength, headersQueueLength,numQueueReceived,numQueueDropped );
    getDisplayString().setTagArg("t", 0, buf);
}


void NDPQueue::finish(){
//      recordScalar("numTrimmedPkt ",numTrimmedPkt );
    emit(numTrimmedPktSig, numTrimmedPkt);
    if (numTrimmedPkt>0)
      std::cout << " mmmmmmmmmmmmmmmmmmmmmm " << numTrimmedPkt << "\n\n";
}



} // namespace inet



#include "inet/common/INETDefs.h"

#include "inet/common/queue/NdpPriorityQueue.h"
//#include "inet/networklayer/ipv4/IPv4Datagram_m.h"

#include <omnetpp.h>
// #include "inet/raptorqimplementation/rqtransportlayer/contract/ITransportPacket.h"
// #include "inet/raptorqimplementation/rqtransportlayer/RaptorQ/raptorq_common/RQSegment_m.h"
// #include "inet/raptorqimplementation/rqtransportlayer/RaptorQ/raptorq_common/RQSegment_m.cc"

#include "inet/transportlayer/tcp_common/TCPSegment.h"  //MOH: added
//using namespace inet::raptorq;
namespace inet {

Define_Module(NdpPriorityQueue);

simsignal_t NdpPriorityQueue::dataQueueLengthSignalPriorityQueu = registerSignal("dataQueueLength");
simsignal_t NdpPriorityQueue::headersQueueLengthSignalPriorityQueu = registerSignal("headersQueueLength");
simsignal_t NdpPriorityQueue::synAckQueueLengthSignalPriorityQueu = registerSignal("synAckQueueLength");
simsignal_t NdpPriorityQueue::numTrimmedPktSigPriorityQueu = registerSignal("numTrimmedPkt");

void NdpPriorityQueue::initialize()
{
    PassiveQueueBase::initialize();
    numTrimmedPacketsVec.setName("numTrimmedPacketsVec");
    weight=10;

//    dataQueuePriority1Length = 0;
//    dataQueuePriority2Length = 0;
//    dataQueuePriority3Length = 0;
//    dataQueuePriority4Length = 0;
//    dataQueuePriority5Length = 0;


    dataQueueLength = 0 ;
    headersQueueLength = 0;
    synAckQueueLength=0;
    numTrimmedPkt=0;

    WATCH(dataQueueLength);
    WATCH(headersQueueLength);
    WATCH(synAckQueueLength);
    WATCH(numTrimmedPkt);


    dataQueuePriority1.setName("dataQueuePriority1");
    dataQueuePriority2.setName("dataQueuePriority2");
    dataQueuePriority3.setName("dataQueuePriority3");
    dataQueuePriority4.setName("dataQueuePriority4");
    dataQueueLowestPriority.setName("dataQueueLowestPriority");

    dataQueue.setName("dataQueue");
    headersQueue.setName("headerQueue");
    synAckQueue.setName("synAckQueue");


    //statistics
    emit(dataQueueLengthSignalPriorityQueu, dataQueue.getLength());
    emit(headersQueueLengthSignalPriorityQueu, headersQueue.getLength());
    emit(numTrimmedPktSigPriorityQueu, numTrimmedPkt);

    outGate = gate("out");

    // configuration
    frameCapacity = par("frameCapacity");
    // moh added
    recordScalar("frameCapacity= ", frameCapacity);
}

cMessage *NdpPriorityQueue::enqueue(cMessage *msg)
{
//    std::cout << "  NdpPriorityQueue::enqueue.\n";
    IPv4Datagram *ipv4Datagram = dynamic_cast<IPv4Datagram *>(PK(msg));
//    raptorq::RQSegment *rqSeg = dynamic_cast<raptorq::RQSegment *>(ipv4Datagram->getEncapsulatedPacket());

     ndp::NDPSegment *rqSeg  = dynamic_cast<ndp::NDPSegment *>(ipv4Datagram->getEncapsulatedPacket());

  if ( rqSeg->getAckBit()==true || rqSeg->getSynBit()==true || rqSeg->getNackBit()==true) { // getNACK for NDP not RQ (use this line with NDP)
//    if (rqSeg->getAckBit() == true || rqSeg->getSynBit() == true) { // this line for RQ and TCP not NDP
        synAckQueue.insert(msg);
        synAckQueueLength = synAckQueue.getLength();
        emit(synAckQueueLengthSignalPriorityQueu, synAckQueue.getLength());
        return nullptr;
    }

    if (rqSeg->getIsHeader() == true) {
//        std::cout << "  getIsHeader.\n";

        headersQueue.insert(msg);
        headersQueueLength = headersQueue.getLength();
        emit(headersQueueLengthSignalPriorityQueu, headersQueue.getLength());
        return nullptr;
    }

    if (rqSeg->getIsPullPacket() == true) {
//        std::cout << "  getIsHeader.\n";
        headersQueue.insert(msg);
        headersQueueLength = headersQueue.getLength();
        emit(headersQueueLengthSignalPriorityQueu, headersQueue.getLength());
        return nullptr;
    }

    unsigned int priority = rqSeg->getPriorityValue();
//    std::cout << "\n\n\n\n  priority = " << priority << "\n\n\n\n";


    switch (priority) {
    case 0:
        if (getCurrentSharedMemeoryLength() >= frameCapacity) {
            trimPacketAndInsertHeader(msg, ipv4Datagram, rqSeg);
            return nullptr;
        } else {
            dataQueueLowestPriority.insert(msg);
            return nullptr;
        }
        break;
    case 1:
        if (getCurrentSharedMemeoryLength() >= frameCapacity) {
            trimPacketAndInsertHeader(msg, ipv4Datagram, rqSeg);
            return nullptr;
        } else {
            // dataQueue is not full ==> insert the incoming packet in the dataQueue
            dataQueuePriority1.insert(msg);
            return nullptr;
        }
        break;
    case 2:
        if (getCurrentSharedMemeoryLength() >= frameCapacity) {
            trimPacketAndInsertHeader(msg, ipv4Datagram, rqSeg);
            return nullptr;
        } else {
            dataQueuePriority2.insert(msg);
            return nullptr;
        }
        break;
    case 3:
        if (getCurrentSharedMemeoryLength() >= frameCapacity) {
            trimPacketAndInsertHeader(msg, ipv4Datagram, rqSeg);
            return nullptr;
        } else {
            dataQueuePriority3.insert(msg);
            return nullptr;
        }
        break;

    case 4:
        if (getCurrentSharedMemeoryLength() >= frameCapacity) {
            trimPacketAndInsertHeader(msg, ipv4Datagram, rqSeg);
            return nullptr;
        } else {
            dataQueuePriority4.insert(msg);
            return nullptr;
        }
        break;
    default:
        std::cout << " error priority value!! \n\n";
        break;
    }

    return nullptr;
}


cMessage *NdpPriorityQueue::dequeue() {
    if (isAllQueuesEmpty())
        return nullptr;
//     std::cout << " £££££££ NdpPriorityQueue::dequeue()  \n";

    ////////////////////////////////////////////////////////////////////////////////////
    if (synAckQueue.getLength()!=0){
        cMessage *msg = (cMessage *) synAckQueue.pop();
        return msg;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    // (( 1 ))    no headers, no data packets
    if (headersQueue.getLength() == 0 && getCurrentSharedMemeoryLength() == 0) {
          return nullptr;
     }
    ////////////////////////////////////////////////////////////////////////////////////
    // (( 2 ))   no headers, just data packets
    if (headersQueue.getLength() == 0 && getCurrentSharedMemeoryLength() != 0) {
         cMessage *msg = (cMessage *)  popNextPacket();
         return msg;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    //  (( 3 ))    no data packets, just headers
    if (headersQueue.getLength() != 0 && getCurrentSharedMemeoryLength() == 0) {
        cMessage *msg = (cMessage *) headersQueue.pop();
        return msg;
    }
    ////////////////////////////////////////////////////////////////////////////////////
    //  (( 4 ))   headers & data packets
    if ( headersQueue.getLength() != 0 && getCurrentSharedMemeoryLength() != 0 && weight%10 == 0) {
//        std::cout << " £££££££ NdpPriorityQueue::popNextPacket()  \n";

        cMessage *msg = (cMessage *)  popNextPacket();
        ++weight;
        return msg;
    }

    if (headersQueue.getLength() != 0 && getCurrentSharedMemeoryLength() != 0 ) {
//        std::cout << " £££££££  pop pop headersQueue()  \n";

        cMessage *msg = (cMessage *) headersQueue.pop();
        ++weight;
        return msg;
    }
    return nullptr;
 }

void NdpPriorityQueue::sendOut(cMessage *msg)
{
    send(msg, outGate);
}

bool NdpPriorityQueue::isEmpty()
{
    return isAllQueuesEmpty();
}


void NdpPriorityQueue::refreshDisplay() const
{
     char buf[100];
    sprintf(buf, "q dataLen: %d\nq headersLen: %d\nq rcvd: %d\nq dropped: %d", dataQueueLength, headersQueueLength,numQueueReceived,numQueueDropped );
    getDisplayString().setTagArg("t", 0, buf);
}


void NdpPriorityQueue::finish(){
//      recordScalar("numTrimmedPkt ",numTrimmedPkt );
    emit(numTrimmedPktSigPriorityQueu, numTrimmedPkt);
    if (numTrimmedPkt>0) {

      std::cout << " aaaaaaaaaaaaaaaaa " << numTrimmedPkt << "\n\n";
      std::cout << " mmmmmmmmmmmmmmmmmmmmmm  dataQueueLowestPriority.getLength()" << dataQueueLowestPriority.getLength() << "\n\n";
    }

}





// trim new incoming packet (when data queue is full) and add the header to the headers queue
void NdpPriorityQueue::trimPacketAndInsertHeader(cMessage *msg, IPv4Datagram *ipv4Datagram , ndp::NDPSegment *rqSeg) {
//    std::cout << " \n\n\n frameCapacity =" << getCurrentSharedMemeoryLength() << " \n\n";
//    std::cout << "NdpPriorityQueue::trimPacketAndInsertHeader(IPv4Datagram *ipv4Datagram , raptorq::RQSegment *rqSeg) \n\n\n";
//    ipv4Datagram->decapsulate(); // to remove the transport segment, which is added below with zero payLoad length
    std::string header = "Header-";
    if (rqSeg != nullptr) {
        std::string name = rqSeg->getName();
        std::string rename = header + name;
        rqSeg->setName(rename.c_str());
//        rqSeg->setPayloadLength(0);
        rqSeg->setIsHeader(true);
        rqSeg->setIsDataPacket(false); //addddddddddd for ndp


//         ipv4Datagram->encapsulate(rqSeg); //no need
//        ipv4Datagram->setTotalLengthField(1); //no need
        ipv4Datagram->setName(rename.c_str());
        ipv4Datagram->setByteLength(0);

//        std::cout  << "  !******************  Receiver $$$$$$$$$$$$$$$$$  HEADER arrived.  " << std::endl;
        unsigned short srcPort = rqSeg->getSrcPort();
        unsigned short destPort = rqSeg->getDestPort();
    }

//    cMessage *msg = dynamic_cast<cMessage *>(ipv4Datagram);
//    std::cout  << "  !******************  Receiver 222 $$$$$$$$$$$$$$$$$  HEADER arrived.  " << std::endl;

    headersQueue.insert(msg);
    headersQueueLength = headersQueue.getLength();
    emit(headersQueueLengthSignalPriorityQueu, headersQueue.getLength());

    ++numTrimmedPkt;
    numTrimmedPacketsVec.record(numTrimmedPkt);
    emit(numTrimmedPktSigPriorityQueu, numTrimmedPkt);
}

// data queues only
unsigned int NdpPriorityQueue::getCurrentSharedMemeoryLength(){
    unsigned int bufferMemory = dataQueueLowestPriority.getLength() + dataQueuePriority1.getLength() + dataQueuePriority2.getLength() + dataQueuePriority3.getLength() + dataQueuePriority4.getLength();
return bufferMemory;
}

bool NdpPriorityQueue::isAllQueuesEmpty() {
    if (dataQueueLowestPriority.isEmpty() && headersQueue.isEmpty()
            && synAckQueue.isEmpty() && dataQueuePriority1.isEmpty()
            && dataQueuePriority2.isEmpty() && dataQueuePriority3.isEmpty()
            && dataQueuePriority4.isEmpty()) {
        return true;
    } else {
        return false;
    }
}

cMessage *NdpPriorityQueue::popNextPacket() {
    if (dataQueuePriority1.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueuePriority1.pop();
        return msg;
    } else if (dataQueuePriority2.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueuePriority2.pop();
        return msg;
    } else if (dataQueuePriority3.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueuePriority3.pop();
        return msg;
    } else if (dataQueuePriority4.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueuePriority4.pop();
        return msg;
    } else if (dataQueueLowestPriority.getLength() != 0) {
        cMessage *msg = (cMessage *) dataQueueLowestPriority.pop();
        return msg;
    } else {
        std::cout << " none \n\n";
        return nullptr;
    }
}



} // namespace inet


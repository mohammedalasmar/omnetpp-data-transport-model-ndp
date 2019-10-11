
#include "inet/ndp/ndptransportlayer/Ndp/queues/NDPMsgBasedSendQueue.h"
#include "inet/ndp/application/ndpapp/GenericAppMsgNdp_m.h"

#include "inet/ndp/ndptransportlayer/Ndp/ndp_common/NDPSegment.h"

namespace inet {

namespace ndp {

Register_Class(NDPMsgBasedSendQueue);

NDPMsgBasedSendQueue::NDPMsgBasedSendQueue() : NDPSendQueue()
{
//    begin = end = 0;
}

NDPMsgBasedSendQueue::~NDPMsgBasedSendQueue()
{
    for (auto & elem : dataToSendQueue)
        delete elem.msg;

    for (auto & elem : sentDataQueue)
          delete elem.msg;


}

void NDPMsgBasedSendQueue::init(unsigned int numPacketsToSend , unsigned int mss)
{
        // filling the dataToSendQueue queue with (random data) packets based on the numPacketsToSend value that the application passes
        // TODO: I would update this to get  bytes stream from the application then packetise this data at the transport layer
         EV_INFO << "\n\n\n\n\n\n\n\n\n generateSymbolsList "     << "\n";
        char msgname[16];
        for (int i = 1; i <= numPacketsToSend; i++) {
            sprintf(msgname, "DATAPKT-%d", i);
            GenericAppMsgNdp *datamsg = new GenericAppMsgNdp(msgname); // state->iss
            Payload payload;
            payload.sequenceNo = i;
            payload.msg = PK(datamsg);
            payload.msg->setByteLength(mss);
            dataToSendQueue.push_back(payload);
        }
        auto it = dataToSendQueue.begin();
        while (it != dataToSendQueue.end()) {
            EV_INFO << " SQN: " << it->sequenceNo << " msgName " << it->msg->getFullName() << "\n";
            it++;
        }
}

NDPSegment *NDPMsgBasedSendQueue::getNdpSegment()
{

//    ASSERT(seqLE(begin, fromSeq) && seqLE(fromSeq + numBytes, end));
    if (dataToSendQueue.size() > 0) {
        NDPSegment *ndpseg = new NDPSegment(nullptr);
        ndpseg->setPayloadLength(1500);

        std::list<Payload>::iterator iter = dataToSendQueue.begin();
//        auto iter = dataToSendQueue.begin();
        const char *payloadName = iter->msg->getName();
        ndpseg->addPayloadMessage(iter->msg->dup(), 1);
        ndpseg->setName(payloadName);
        ndpseg->setDataSequenceNumber(iter->sequenceNo);

//        ndpseg->isLastPktToSend(isLastSymbolToSend);

        EV_INFO << "  \n\n\n\n\n\n getNewNDP segment ........." << iter->sequenceNo << " \n\n\n";
        removeFromDataQueueToSentQueue(iter);

        return ndpseg;
    } else {
        EV_INFO << " Nothing to send !! \n";
        return nullptr;
    }
}

void NDPMsgBasedSendQueue::removeFromDataQueueToSentQueue( std::list<Payload>::iterator iter) {
    Payload payload;
    payload.sequenceNo = iter->sequenceNo;
    payload.msg = iter->msg;
    payload.msg->setByteLength(1500);
    sentDataQueue.push_back(payload);

//    delete iter->msg;
    dataToSendQueue.erase(iter);
}


void NDPMsgBasedSendQueue::moveFrontDataQueue( std::list<Payload>::iterator iter) {
    Payload payload;
    payload.sequenceNo = iter->sequenceNo;
    payload.msg = iter->msg;
    payload.msg->setByteLength(1500);
    dataToSendQueue.push_front(payload);

//    delete iter->msg;
    sentDataQueue.erase(iter);
}

void NDPMsgBasedSendQueue::ackArrivedFreeBuffer(unsigned int ackNum){
    EV_INFO << " ackArrivedFreeBuffer: " <<  ackNum << "\n";


    auto iter = sentDataQueue.begin();
    while (iter != sentDataQueue.end()) {
        if (iter->sequenceNo == ackNum) {
            EV_INFO << "ackArrivedFreeBuffer erase pktId: " << iter->sequenceNo << "\n\n";
//            delete iter->msg;
            sentDataQueue.erase(iter);
//            printAllInfoInQueue();
            break;
        } else {
//        MY_COUT << " SQN: " << iter->pktId << " msgName "  << iter->msg->getFullName() << "\n";
            iter++;
        }
    }
    printAllInfoInQueue();
}

void NDPMsgBasedSendQueue::nackArrivedMoveFront(unsigned int nackNum){

    EV_INFO << " nack arrived: " <<  nackNum << "\n";

    auto iter = sentDataQueue.begin();
    while (iter != sentDataQueue.end()) {
        if (iter->sequenceNo == nackNum) {
            moveFrontDataQueue(iter);
            break;
        } else {
            iter++;
        }
    }
    printAllInfoInQueue();
}




//NDPSegment *NDPMsgBasedSendQueue::getNdpSegment(unsigned int seqNo)
//{
////    ASSERT(seqLE(begin, fromSeq) && seqLE(fromSeq + numBytes, end));
//    NDPSegment *ndpseg = new NDPSegment(nullptr);
//
//    ndpseg->setSequenceNo(seqNo);
//    ndpseg->setPayloadLength(1500);
//
//    auto iter = dataToSendQueue.begin();
//
//     while (iter != dataToSendQueue.end()) {
//         if (iter->sequenceNo == seqNo) {
//             EV_INFO << "found: " << iter->sequenceNo << "\n\n";
//             const char *payloadName = nullptr;
//             payloadName = iter->msg->getName();
//             ndpseg->addPayloadMessage(iter->msg->dup(), 1);
//             // why 1 ==> each segment has one symbol, we don't send segment with multiple packets as in TCP
//             ndpseg->setName(payloadName);
//             return ndpseg;
//             break;
//         } else {
// //        MY_COUT << " SQN: " << iter->pktId << " msgName "  << iter->msg->getFullName() << "\n";
//             ++iter;
//         }
//     }
//     return nullptr;
//}



void NDPMsgBasedSendQueue::printAllInfoInQueue(){
    EV_INFO << " \n\n\n\n\n\n  dataToSendQueue \n" ;
    for (auto iter = dataToSendQueue.begin(); iter != dataToSendQueue.end() ; ++iter){
        EV_INFO << " dataToSendQueue In = " << iter->msg->getName() << "\n";
    }
    EV_INFO << " sentDataQueue \n" ;

    for (auto iter = sentDataQueue.begin(); iter != sentDataQueue.end() ; ++iter){
        EV_INFO << " sentDataQueue In = " << iter->msg->getName() << "\n";
    }

}














std::string NDPMsgBasedSendQueue::info() const
{
    int begin=0; int end =0;
    std::stringstream out;
    out << "[" << begin << ".." << end << "), " << dataToSendQueue.size() << " packets";
    return out.str();
}

void NDPMsgBasedSendQueue::enqueueAppData(cPacket *msg)
{
//     end += msg->getByteLength();
//    if (seqLess(end, begin))
//        throw cRuntimeError("Send queue is full");

    Payload payload;
    payload.sequenceNo = 0;
    payload.msg = msg;
    dataToSendQueue.push_back(payload);
}

uint32 NDPMsgBasedSendQueue::getBufferStartSeq()
{
//    return begin;
}

uint32 NDPMsgBasedSendQueue::getBufferEndSeq()
{
//    return end;
}

NDPSegment *NDPMsgBasedSendQueue::createSegmentWithBytes(uint32 fromSeq, ulong numBytes)
{
    //NDPEV << "sendQ: " << info() << " createSeg(seq=" << fromSeq << " len=" << numBytes << ")\n";
//    ASSERT(seqLE(begin, fromSeq) && seqLE(fromSeq + numBytes, end));

    NDPSegment *ndpseg = new NDPSegment(nullptr);

    ndpseg->setDataSequenceNumber(fromSeq);
    ndpseg->setPayloadLength(numBytes);

    // add payload messages whose endSequenceNo is between fromSeq and fromSeq + numBytes
    auto i = dataToSendQueue.begin();

    while (i != dataToSendQueue.end() && seqLE(i->sequenceNo, fromSeq))
        ++i;

    uint32 toSeq = fromSeq + numBytes;
    const char *payloadName = nullptr;

    while (i != dataToSendQueue.end() && seqLE(i->sequenceNo, toSeq)) {
        if (!payloadName)
            payloadName = i->msg->getName();

        ndpseg->addPayloadMessage(i->msg->dup(), i->sequenceNo);
        ++i;
    }

    // give segment a name
    char msgname[80];
    if (!payloadName)
        sprintf(msgname, "ndpseg(l=%lu,%dmsg)", numBytes, ndpseg->getPayloadArraySize());
    else
        sprintf(msgname, "%.10s(l=%lu,%dmsg)", payloadName, numBytes, ndpseg->getPayloadArraySize());
    ndpseg->setName(msgname);

    return ndpseg;
}

void NDPMsgBasedSendQueue::discardUpTo(uint32 seqNum)
{
    //NDPEV << "sendQ: " << info() << " discardUpTo(seq=" << seqNum << ")\n";

//    ASSERT(seqLE(begin, seqNum) && seqLE(seqNum, end));

    int begin = seqNum;

    // remove payload messages whose endSequenceNo is below seqNum
    while (!dataToSendQueue.empty() && seqLE(dataToSendQueue.front().sequenceNo, seqNum)) {
        delete dataToSendQueue.front().msg;
        dataToSendQueue.pop_front();
    }
}

} // namespace ndp

} // namespace inet



#include "inet/ndp/ndptransportlayer/Ndp/queues/receiveQueue.h"
#include "inet/ndp/application/ndpapp/GenericAppMsgNdp_m.h"

#include "inet/ndp/ndptransportlayer/Ndp/ndp_common/NDPSegment.h"

namespace inet {

namespace ndp {

Register_Class(receiveQueue);

receiveQueue::receiveQueue() : NDPReceiveQueue()
{
//    begin = end = 0;
}

receiveQueue::~receiveQueue()
{
    for (auto & elem : receiveDataQueue)
        delete elem.packet;
}

void receiveQueue::init(unsigned int numSymbolsToSend)
{

}

//void receiveQueue::addToReceiveQueue(unsigned int numSymbolsToSend)
//{
//    receiveDataQueue.push_back(__x);
//}







void receiveQueue::printAllInfoInQueue(){
//    EV_INFO << " \n\n\n\n\n\n  dataToSendQueue \n" ;
//    for (auto iter = dataToSendQueue.begin(); iter != dataToSendQueue.end() ; ++iter){
//        EV_INFO << " dataToSendQueue In = " << iter->msg->getName() << "\n";
//    }
//    EV_INFO << " sentDataQueue \n" ;
//
//    for (auto iter = sentDataQueue.begin(); iter != sentDataQueue.end() ; ++iter){
//        EV_INFO << " sentDataQueue In = " << iter->msg->getName() << "\n";
//    }

}














std::string receiveQueue::info() const
{
    int begin=0; int end =0;
    std::stringstream out;
    out << "[" << begin << ".." << end << "), " << receiveDataQueue.size() << " packets";
    return out.str();
}





} // namespace ndp

} // namespace inet


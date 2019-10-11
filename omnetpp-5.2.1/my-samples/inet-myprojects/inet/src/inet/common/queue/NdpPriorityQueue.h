

#ifndef __INET_NdpPriorityQueue_H
#define __INET_NdpPriorityQueue_H

#include "inet/common/INETDefs.h"

#include "inet/common/queue/PassiveQueueBase.h"
#include "inet/networklayer/ipv4/IPv4Datagram.h"
#include "inet/ndp/ndptransportlayer/Ndp/ndp_common/NDPSegment.h"

namespace inet {

/**
 * Drop-front queue. See NED for more info.
 */
class INET_API NdpPriorityQueue : public PassiveQueueBase
{
  protected:
    // configuration
    unsigned int frameCapacity;
//    unsigned int sharedMemeoryLength;

    // 0     --> 10KB    P1
    // 10KB  --> 100KB   P2
    // 100KB --> 1MB     P3
    // 1MB   --> 10MB    P4
    // else   P5
    cQueue dataQueuePriority1;
    cQueue dataQueuePriority2;
    cQueue dataQueuePriority3;
    cQueue dataQueuePriority4;

    cQueue dataQueueLowestPriority;

    cQueue dataQueue;
    cQueue headersQueue;
    cQueue synAckQueue;

    cOutVector numTrimmedPacketsVec;
//    unsigned int dataQueuePriority1Length;
//    unsigned int dataQueuePriority2Length;
//    unsigned int dataQueuePriority3Length;
//    unsigned int dataQueuePriority4Length;
//    unsigned int dataQueuePriority5Length;

   unsigned int dataQueueLength;
   unsigned int headersQueueLength;
   unsigned int synAckQueueLength;

   unsigned int weight;
   unsigned int numTrimmedPkt ;

    cGate *outGate;

    // statistics
    static simsignal_t dataQueueLengthSignalPriorityQueu;
    static simsignal_t headersQueueLengthSignalPriorityQueu;
    static simsignal_t synAckQueueLengthSignalPriorityQueu;
    static simsignal_t numTrimmedPktSigPriorityQueu;


  protected:
    virtual void initialize() override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *enqueue(cMessage *msg) override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual cMessage *dequeue() override;

    /**
     * Redefined from PassiveQueueBase.
     */
    virtual void sendOut(cMessage *msg) override;
    void trimPacketAndInsertHeader(cMessage *msg, IPv4Datagram *ipv4Datagram, ndp::NDPSegment *rqSeg);
    unsigned int getCurrentSharedMemeoryLength();
    bool isAllQueuesEmpty();
    cMessage  *popNextPacket();

    /**
     * Redefined from IPassiveQueue.
     */
    virtual bool isEmpty() override;
    virtual void finish() override;

    virtual void refreshDisplay() const override;

};

} // namespace inet

#endif // ifndef __INET_NdpPriorityQueue_H


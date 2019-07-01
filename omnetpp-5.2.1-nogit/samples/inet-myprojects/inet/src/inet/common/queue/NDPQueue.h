

#ifndef __INET_NDPQueue_H
#define __INET_NDPQueue_H

#include "inet/common/INETDefs.h"

#include "inet/common/queue/PassiveQueueBase.h"

namespace inet {

/**
 * Drop-front queue. See NED for more info.
 */
class INET_API NDPQueue : public PassiveQueueBase
{
  protected:
    // configuration
    int frameCapacity;

    // state
    cQueue dataQueue;
    cQueue headersQueue;
    cQueue synAckQueue;

    cOutVector numTrimmedPacketsVec;

   unsigned int dataQueueLength;
   unsigned int headersQueueLength;
   unsigned int synAckQueueLength;

   unsigned int weight;
   unsigned int numTrimmedPkt ;

    cGate *outGate;

    // statistics
    static simsignal_t dataQueueLengthSignal;
    static simsignal_t headersQueueLengthSignal;
    static simsignal_t synAckQueueLengthSignal;
    static simsignal_t numTrimmedPktSig;


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

    /**
     * Redefined from IPassiveQueue.
     */
    virtual bool isEmpty() override;
    virtual void finish() override;

    virtual void refreshDisplay() const override;

};

} // namespace inet

#endif // ifndef __INET_NDPQueue_H


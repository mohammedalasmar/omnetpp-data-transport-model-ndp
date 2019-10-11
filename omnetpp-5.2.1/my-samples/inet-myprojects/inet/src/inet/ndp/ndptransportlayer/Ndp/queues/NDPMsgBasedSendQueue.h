
#ifndef __INET_NDPMSGBASEDSENDQUEUE_H
#define __INET_NDPMSGBASEDSENDQUEUE_H

#include <list>

#include "../NDPSendQueue.h"

namespace inet {

namespace ndp {

/**
 * Send queue that manages messages.
 *
 * @see NDPMsgBasedRcvQueue
 */
class INET_API NDPMsgBasedSendQueue : public NDPSendQueue
{
  protected:
    struct Payload
    {
        unsigned int sequenceNo;
        cPacket *msg;
    };
    typedef std::list<Payload> PayloadQueue;
    PayloadQueue dataToSendQueue;
    PayloadQueue sentDataQueue;


  public:
    /**
     * Ctor
     */
    NDPMsgBasedSendQueue();

    /**
     * Virtual dtor.
     */
    virtual ~NDPMsgBasedSendQueue();

    /**
     *
     */
    virtual void init(unsigned int numPacketsToSend , unsigned int mss) override;

    /**
     * Returns a string with the region stored.
     */
    virtual std::string info() const override;

    /**
     *
     */
    virtual void enqueueAppData(cPacket *msg) override;

    /**
     *
     */
    virtual uint32 getBufferStartSeq() override;

    /**
     *
     */
    virtual uint32 getBufferEndSeq() override;

    /**
     *
     */
    virtual NDPSegment *createSegmentWithBytes(uint32 fromSeq, ulong numBytes) override;
//    virtual NDPSegment *getNdpSegment(unsigned int seqNo) override;
    virtual void ackArrivedFreeBuffer(unsigned int ackNum) override;
    virtual void nackArrivedMoveFront(unsigned int nackNum) override;


    virtual NDPSegment *getNdpSegment() override;


    void removeFromDataQueueToSentQueue(std::list<Payload>::iterator iter);
    void moveFrontDataQueue(std::list<Payload>::iterator iter);

    void printAllInfoInQueue();

    /**
     *
     */
    virtual void discardUpTo(uint32 seqNum) override;
};

} // namespace raptoNDP

} // namespace inet

#endif // ifndef __INET_NDPMSGBASEDSENDQUEUE_H


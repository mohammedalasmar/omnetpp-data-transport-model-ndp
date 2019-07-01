
#ifndef __INET_receiveQueue_H
#define __INET_receiveQueue_H

#include <list>

#include "../NDPReceiveQueue.h"

namespace inet {

namespace ndp {

/**
 * Send queue that manages messages.
 *
 * @see NDPMsgBasedRcvQueue
 */
class INET_API receiveQueue : public NDPReceiveQueue
{
  protected:
    struct PayloadItem
    {
        unsigned int sequenceNo;
        cPacket *packet;
        PayloadItem(uint32 _seqNo, cPacket *_packet) : sequenceNo(_seqNo), packet(_packet) {}

    };
    typedef std::list<PayloadItem> PayloadQueue;
    PayloadQueue receiveDataQueue;




  public:
    /**
     * Ctor
     */
    receiveQueue();

    /**
     * Virtual dtor.
     */
    virtual ~receiveQueue();

    /**
     *
     */
    virtual void init(unsigned int numSymbolsToSend) override;

    /**
     * Returns a string with the region stored.
     */
    virtual std::string info() const override;




    void printAllInfoInQueue();

    /**
     *
     */
 };

} // namespace raptoNDP

} // namespace inet

#endif // ifndef __INET_receiveQueue_H


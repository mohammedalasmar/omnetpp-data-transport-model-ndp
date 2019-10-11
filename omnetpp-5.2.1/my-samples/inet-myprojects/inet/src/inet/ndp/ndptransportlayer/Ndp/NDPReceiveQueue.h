
#ifndef __INET_NDPRECEIVEQUEUE_H
#define __INET_NDPRECEIVEQUEUE_H

#include "inet/common/INETDefs.h"
#include "NDPConnection.h"


namespace inet {

class NDPCommand;

namespace ndp {

class NDPSegment;

/**
 * Abstract base class for NDP receive queues. This class represents
 * data received by NDP but not yet passed up to the application.
 * The class also accomodates for selective retransmission, i.e.
 * also acts as a segment buffer.
 *
 * This class goes hand-in-hand with NDPSendQueue.
 *
 * This class is polymorphic because depending on where and how you
 * use the NDP model you might have different ideas about "sending data"
 * on a simulated connection: you might want to transmit real bytes,
 * "dummy" (byte count only), cMessage objects, etc; see discussion
 * at NDPSendQueue. Different subclasses can be written to accomodate
 * different needs.
 *
 * @see NDPSendQueue
 */
class INET_API NDPReceiveQueue : public cObject
{
  protected:
    NDPConnection *conn;    // the connection that owns this queue

  public:
    /**
     * Ctor.
     */
    NDPReceiveQueue() { conn = nullptr; }

    /**
     * Virtual dtor.
     */
    virtual ~NDPReceiveQueue() {}

    /**
     * Set the connection that owns this queue.
     */
//    virtual void setConnection(NDPConnection *_conn) { conn = _conn; }

    /**
     * Set initial receive sequence number.
     */
    virtual void init(uint32 startSeq) = 0;

    /**
     * Called when a NDP segment arrives, it should extract the payload
     * from the segment and store it in the receive queue. The segment
     * object should *not* be deleted.
     *
     * The method should return the sequence number to be ACKed.
     */
//    virtual uint32 insertBytesFromSegment(NDPSegment *NDPseg) = 0;

    /**
     * Should create a packet to be passed up to the app, up to (but NOT
     * including) the given sequence no (usually rcv_nxt).
     * It should return nullptr if there's no more data to be passed up --
     * this method is called several times until it returns nullptr.
     */
//    virtual cPacket *extractBytesUpTo(uint32 seq) = 0;

    /**
     * Returns the number of bytes (out-of-order-segments) currently buffered in queue.
     */
//    virtual uint32 getAmountOfBufferedBytes() = 0;

    /**
     * Returns the number of bytes currently free (=available) in queue. freeRcvBuffer = maxRcvBuffer - usedRcvBuffer
     */
//    virtual uint32 getAmountOfFreeBytes(uint32 maxRcvBuffer) = 0;

    /**
     * Returns the number of blocks currently buffered in queue.
     */
//    virtual uint32 getQueueLength() = 0;

    /**
     * Shows current queue status.
     */
//    virtual void getQueueStatus() = 0;

    /**
     * Returns left edge of enqueued region.
     */
//    virtual uint32 getLE(uint32 fromSeqNum) = 0;

    /**
     * Returns right edge of enqueued region.
     */
//    virtual uint32 getRE(uint32 toSeqNum) = 0;

    /** Returns the minimum of first byte seq.no. in queue and rcv_nxt */
//    virtual uint32 getFirstSeqNo() = 0;
};

} // namespace ndp

} // namespace inet

#endif // ifndef __INET_NDPRECEIVEQUEUE_H


//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_NDPSENDQUEUE_H
#define __INET_NDPSENDQUEUE_H

#include "../../ndptransportlayer/Ndp/NDPConnection.h"
#include "inet/common/INETDefs.h"
#include "ndp_common/NDPSegment.h"


namespace inet {

namespace ndp {

class INET_API NDPSendQueue : public cObject
{
  protected:
    NDPConnection *conn;    // the connection that owns this queue

  public:
    /**
     * Ctor.
     */
    NDPSendQueue() { conn = nullptr; }

    /**
     * Virtual dtor.
     */
    virtual ~NDPSendQueue() {}

    /**
     * Set the connection that owns this queue.
     */
    virtual void setConnection(NDPConnection *_conn) { conn = _conn; }

    /**
     * Initialize the object. The startSeq parameter tells what sequence number the first
     * byte of app data should get. This is usually ISS + 1 because SYN consumes
     * one byte in the sequence number space.
     *
     * init() may be called more than once; every call flushes the existing contents
     * of the queue.
     */
    virtual void init(unsigned int numPacketsToSend, unsigned int mss) = 0;

    /**
     * Called on SEND app command, it inserts in the queue the data the user
     * wants to send. Implementations of this abstract class will decide
     * what this means: copying actual bytes, just increasing the
     * "last byte queued" variable, or storing cMessage object(s).
     * The msg object should not be referenced after this point (sendQueue may
     * delete it.)
     */
    virtual void enqueueAppData(cPacket *msg) = 0;

    /**
     * Returns the sequence number of the first byte stored in the buffer.
     */
    virtual uint32 getBufferStartSeq() = 0;

    /**
     * Returns the sequence number of the last byte stored in the buffer plus one.
     * (The first byte of the next send operation would get this sequence number.)
     */
    virtual uint32 getBufferEndSeq() = 0;

    virtual NDPSegment *getNdpSegment() = 0;

    virtual void ackArrivedFreeBuffer(unsigned int ackNum) = 0;
    virtual void nackArrivedMoveFront(unsigned int nackNum) = 0;


    /**
     * Utility function: returns how many bytes are available in the queue, from
     * (and including) the given sequence number.
     */
    inline ulong getBytesAvailable(uint32 fromSeq)
    {
        uint32 bufEndSeq = getBufferEndSeq();
        return seqLess(fromSeq, bufEndSeq) ? bufEndSeq - fromSeq : 0;
    }

    /**
     * Called when the NDP wants to send or retransmit data, it constructs
     * a NDP segment which contains the data from the requested sequence
     * number range. The actually returned segment may contain less than
     * maxNumBytes bytes if the subclass wants to reproduce the original
     * segment boundaries when retransmitting.
     */
    virtual NDPSegment *createSegmentWithBytes(uint32 fromSeq, ulong maxNumBytes) = 0;

    /**
     * Tells the queue that bytes up to (but NOT including) seqNum have been
     * transmitted and ACKed, so they can be removed from the queue.
     */
    virtual void discardUpTo(uint32 seqNum) = 0;
};

} // namespace raptoNDP

} // namespace inet

#endif // ifndef __INET_NDPSENDQUEUE_H


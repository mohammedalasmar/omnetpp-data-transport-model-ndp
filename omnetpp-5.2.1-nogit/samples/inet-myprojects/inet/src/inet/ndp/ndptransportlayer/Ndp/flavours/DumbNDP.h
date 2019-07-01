
#ifndef __INET_DUMBNDP_H
#define __INET_DUMBNDP_H

#include "../NDPAlgorithm.h"
#include "inet/common/INETDefs.h"


namespace inet {

namespace ndp {

/**
 * State variables for DumbNDP.
 */
class INET_API DumbNDPStateVariables : public NDPStateVariables
{
  public:
    //...
};

/**
 * A very-very basic NDPAlgorithm implementation, with hardcoded
 * retransmission timeout and no other sophistication. It can be
 * used to demonstrate what happened if there was no adaptive
 * timeout calculation, delayed acks, silly window avoidance,
 * congestion control, etc.
 */
class INET_API DumbNDP : public NDPAlgorithm
{
  protected:
    DumbNDPStateVariables *& state;    // alias to TCLAlgorithm's 'state'

    cMessage *rexmitTimer;    // retransmission timer

  protected:
    /** Creates and returns a DumbNDPStateVariables object. */
    virtual NDPStateVariables *createStateVariables() override
    {
        return new DumbNDPStateVariables();
    }

  public:
    /** Ctor */
    DumbNDP();

    virtual ~DumbNDP();

    virtual void initialize() override;

    virtual void established(bool active) override;

    virtual void connectionClosed() override;

    virtual void processTimer(cMessage *timer, NDPEventCode& event) override;

    virtual void sendCommandInvoked(cMessage *msg) override;

    virtual void receivedOutOfOrderSegment() override;

    virtual void receiveSeqChanged() override;

    virtual void receivedDataAck(uint32 firstSeqAcked) override;

    virtual void receivedDuplicateAck() override;

    virtual void receivedAckForDataNotYetSent(uint32 seq) override;

    virtual void ackSent() override;

    virtual void dataSent(uint32 fromseq) override;

    virtual void segmentRetransmitted(uint32 fromseq, uint32 toseq) override;

    virtual void restartRexmitTimer() override;
    virtual void cancelRexmitTimer() override;



    virtual void rttMeasurementCompleteUsingTS(uint32 echoedTS) override;
};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_DUMBNDP_H


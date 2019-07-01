
#ifndef __INET_NdpSinkApp_H
#define __INET_NdpSinkApp_H

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/lifecycle/LifecycleOperation.h"
//#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "inet/ndp/ndptransportlayer/contract/ndp/NDPSocket.h"




namespace inet {

/**
 * Accepts any number of incoming connections, and discards whatever arrives
 * on them.
 */
class INET_API NdpSinkApp : public cSimpleModule, public ILifecycle
{
  protected:
    long bytesRcvd;
    NDPSocket socket;

    unsigned int multiCastGroupId;
    unsigned int multiSrcGroupId;


     //statistics:
    static simsignal_t rcvdPkSignalNDP;
//    static simsignal_t fctRecordv1;

    cMessage *timeoutMsg = nullptr;
    // MOH: added
    simtime_t tStartAdded;
    simtime_t tEndAdded;
    unsigned int numRcvTrimmedHeader = 0 ;


    bool firstDataReceived = true;
    bool isLongFlow;

    cGate *gateToNdp;


    virtual void sendRequest();
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    virtual void allReceivedCloseAllMultiSourcingConns(); // for multi sourcing


    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) override
    { Enter_Method_Silent(); throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName()); return true; }
};

} // namespace inet

#endif // ifndef __INET_NdpSinkApp_H


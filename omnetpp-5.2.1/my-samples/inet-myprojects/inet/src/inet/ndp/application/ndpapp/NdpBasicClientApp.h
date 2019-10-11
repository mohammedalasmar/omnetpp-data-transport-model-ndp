
#ifndef __INET_NdpBasicClientApp_H
#define __INET_NdpBasicClientApp_H
#include "inet/ndp/application/ndpapp/NdpAppBase.h"
#include "inet/common/INETDefs.h"

#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/lifecycle/ILifecycle.h"

namespace inet {

/**
 * An example request-reply based client application.
 */
class INET_API NdpBasicClientApp : public NdpAppBase, public ILifecycle
{
  protected:
    cMessage *timeoutMsg = nullptr;
    NodeStatus *nodeStatus = nullptr;

    static simsignal_t rcvdPacketSignal; // moh


    simtime_t startTime;
    simtime_t stopTime;
    unsigned int sendBytes = 0;


    #define NDP_TIMEOUT_REQUEST_REXMIT_MAX    240  // 4 mins (will only be used with request)
    #define MAX_REQUEST_REXMIT_COUNT         5     // (Added)
    #define NDP_TIMEOUT_REQUEST_REXMIT        1     // (Added)  request timeout
    int request_rexmit_count;                      // (Added) number of request retransmissions
    simtime_t request_rexmit_timeout;              // (Added) current request retransmission timeout
    cMessage *requestRexmitTimer = nullptr;        // (Added) for retransmitting request


     virtual void sendWriteRequest();
     virtual void sendData();

    virtual void rescheduleOrDeleteTimer(simtime_t d, short int msgKind);
//    virtual void  startRequestRexmitTimer(); // Added

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleTimer(cMessage *msg) override;
    virtual void socketEstablished(int connId, void *yourPtr) override;
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) override;
    virtual void socketClosed(int connId, void *yourPtr) override;
    virtual void socketFailure(int connId, void *yourPtr, int code) override;
    virtual bool isNodeUp();
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) override;

  public:
    NdpBasicClientApp() {}
    virtual ~NdpBasicClientApp();
};

} // namespace inet

#endif // ifndef __INET_NdpBasicClientApp_H




#ifndef __INET_RAPTONDPAPPBASE_H
#define __INET_RAPTONDPAPPBASE_H

#include "inet/common/INETDefs.h"
#include "inet/ndp/ndptransportlayer/contract/ndp/NDPSocket.h"
#include "inet/ndp/ndptransportlayer/Ndp/Ndp.h"

namespace inet {

/**
 * Base class for clients app for NDP-based request-reply protocols or apps.
 * Handles a single session (and NDP connection) at a time.
 *
 * It needs the following NED parameters: localAddress, localPort, connectAddress, connectPort.
 */
class INET_API NdpAppBase : public cSimpleModule, public NDPSocket::CallbackInterface
{
  protected:
    NDPSocket socket;

    // statistics
    int numSessions;
    int numBroken;
    int packetsSent;
    int packetsRcvd;
    int bytesSent;
    long bytesRcvd;




  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    /* Utility functions */
    virtual void connect();
    virtual void close();
    virtual void sendPacket(cPacket *pkt);
    virtual void setStatusString(const char *s);

    /* NDPSocket::CallbackInterface callback methods */
    virtual void handleTimer(cMessage *msg) = 0;
    virtual void socketEstablished(int connId, void *yourPtr) override;
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) override;
    virtual void socketPeerClosed(int connId, void *yourPtr) override;
    virtual void socketClosed(int connId, void *yourPtr) override;
    virtual void socketFailure(int connId, void *yourPtr, int code) override;
    virtual void socketStatusArrived(int connId, void *yourPtr, NDPStatusInfo *status) override { delete status; }
};

} // namespace inet

#endif // ifndef __INET_RAPTONDPAPPBASE_H


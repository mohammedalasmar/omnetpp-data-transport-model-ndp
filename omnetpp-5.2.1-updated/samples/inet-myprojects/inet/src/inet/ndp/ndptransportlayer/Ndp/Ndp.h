// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

#ifndef __INET_NDP_H
#define __INET_NDP_H

#include <map>
#include <set>

#include "inet/common/INETDefs.h"

#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/networklayer/common/L3Address.h"
#include "../contract/ndp/NDPCommand_m.h"
//#include "../../FatTreeNDP/CentralScheduler.h"

namespace inet {

namespace ndp {

// Forward declarations:
class NDPConnection;
class NDPSegment;
class NDPSendQueue;
class NDPReceiveQueue;

class INET_API Ndp : public cSimpleModule, public ILifecycle
{
  public:
    struct AppConnKey    // XXX this class is redundant since connId is already globally unique
    {
        int appGateIndex;
        int connId;

        inline bool operator<(const AppConnKey& b) const
        {
            if (appGateIndex != b.appGateIndex)
                return appGateIndex < b.appGateIndex;
            else
                return connId < b.connId;
        }
    };

    struct SockPair
    {
        L3Address localAddr;
        L3Address remoteAddr;
        int localPort;    // -1: unspec
        int remotePort;    // -1: unspec


        inline bool operator<(const SockPair& b) const
        {
            if (remoteAddr != b.remoteAddr)
                return remoteAddr < b.remoteAddr;
            else if (localAddr != b.localAddr)
                return localAddr < b.localAddr;
            else if (remotePort != b.remotePort)
                return remotePort < b.remotePort;
            else
                return localPort < b.localPort;
        }
    };

    // ^^^^^^^^^^^^^^^^^ Multicast
    struct SockPairMulticast
    {
        L3Address localAddr;
//        L3Address remoteAddr;
        int localPort;    // -1: unspec
//        int remotePort;    // -1: unspec

         int multicastGid;    // multicast group id

        inline bool operator<(const SockPairMulticast& b) const
        {
            if (localAddr != b.localAddr)
                return localAddr < b.localAddr;
//            else if (localAddr != b.localAddr)
//                return localAddr < b.localAddr;
//            else if (remotePort != b.remotePort)
//                return remotePort < b.remotePort;
            else
                return localPort < b.localPort;
        }
    };



    cMessage *requestTimerMsg = nullptr;


    // MOH
    std::map<int, int> appGateIndexTimeOutMap;  // moh: contains num of timeouts for each app
    bool test = true;

//    struct connRequests
//    {
////        int appGateIndex;
//        int connId;
//        int numQueuedRequests;
//    };
//    typedef std::map<connRequests,NDPConnection *> ConnRequestMap;
//    ConnRequestMap conniRequestMap;

//    std::map<int,int> connRequestMap;

    std::map< int,  NDPConnection * > requestCONNMap;
    int connIndex = 0;

   int counter=0;
   int timeOut = 0;
   int times=0;
   bool nap=false;




  protected:
    typedef std::map<AppConnKey, NDPConnection *> NdpAppConnMap;
    typedef std::map<SockPair, NDPConnection *> NdpConnMap;

    NdpAppConnMap ndpAppConnMap;
    NdpConnMap ndpConnMap;
    cOutVector requestTimerStamps;

    ushort lastEphemeralPort = (ushort)-1;
    std::multiset<ushort> usedEphemeralPorts;






  protected:
    /** Factory method; may be overriden for customizing NDP */
    virtual NDPConnection *createConnection(int appGateIndex, int connId);

    // utility methods
    virtual NDPConnection *findConnForSegment(NDPSegment *ndpseg, L3Address srcAddr, L3Address destAddr);



    virtual NDPConnection *findConnForApp(int appGateIndex, int connId);

    virtual void segmentArrivalWhileClosed(NDPSegment *ndpseg, L3Address src, L3Address dest);
    virtual void removeConnection(NDPConnection *conn);
    virtual void updateDisplayString();

  public:
    static bool testing;    // switches between tcpEV and testingEV
    static bool logverbose;    // if !testing, turns on more verbose logging

    bool recordStatistics = false;    // output vectors on/off
    bool isOperational = false;    // lifecycle: node is up/down

    bool useDataNotification = false;

  public:
    Ndp() {}
    virtual ~Ndp();

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

  public:
    /**
     * To be called from NDPConnection when a new connection gets created,
     * during processing of OPEN_ACTIVE or OPEN_PASSIVE.
     */
    virtual void addSockPair(NDPConnection *conn, L3Address localAddr, L3Address remoteAddr, int localPort, int remotePort);

    /**
     * To be called from NDPConnection when socket pair (key for NDPConnMap) changes
     * (e.g. becomes fully qualified).
     */
    virtual void updateSockPair(NDPConnection *conn, L3Address localAddr, L3Address remoteAddr, int localPort, int remotePort);


    /**
     * To be called from NDPConnection: reserves an ephemeral port for the connection.
     */
    virtual ushort getEphemeralPort();

    /**
     * To be called from NDPConnection: create a new send queue.
     */
    virtual NDPSendQueue *createSendQueue();

    /**
     * To be called from NDPConnection: create a new receive queue.
     */
    virtual NDPReceiveQueue *createReceiveQueue();

    // ILifeCycle:
    virtual bool handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) override;

    // called at shutdown/crash
    virtual void reset();

    virtual void  requestTimer();

    virtual void  cancelRequestTimer();
    virtual bool   getNapState();
    virtual bool allPullQueuesEmpty();
    virtual bool allConnFinished();
    virtual void updateConnMap();
    virtual void  sendFirstRequest();
    virtual void  process_REQUEST_TIMER();
    virtual void  printConnRequestMap();



};

} // namespace ndp

} // namespace inet

#endif // ifndef __INET_NDP_H


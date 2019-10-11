#ifndef __INET_CentralSchedulerNdp_H
#define __INET_CentralSchedulerNdp_H
#include <chrono>  // for high_resolution_clock
#include <fstream>
#include <map>
#include <set>
#include <algorithm>    // std::random_shuffle
#include <vector>
#include <random>
#include <cmath>
#include <time.h>
#include <fstream>

#include "inet/common/INETDefs.h"
#include "inet/common/ModuleAccess.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/lifecycle/ILifecycle.h"

#include "inet/ndp/application/ndpapp/NdpBasicClientApp.h"
#include "inet/ndp//application/ndpapp/NdpSinkApp.h"
#include <algorithm>

namespace inet {
class INET_API CentralSchedulerNdp: public cSimpleModule, public ILifecycle {

protected:
    bool isWebSearchWorkLoad;
    unsigned int indexWorkLoad;
    std::vector<unsigned int> flowSizeWebSeachWorkLoad;

    std::ofstream myfile;

    // daisyChainGFS: sorting the nodes (1 source& 3 replicas) based on how far is each dest from the source
    struct differenceBetweenSrcNodeAndDestNode {
        unsigned int diff, dest ;
        bool operator<(const differenceBetweenSrcNodeAndDestNode& a) const
          {
              return diff < a.diff; // ascending order
          }
    };

    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    simtime_t totalSimTime;
    cOutVector permMapLongFlowsVec;
    cOutVector permMapShortFlowsVec;

    cOutVector randMapShortFlowsVec;
    cOutVector permMapShortFlowsVector;

    cOutVector numTcpSessionAppsVec;
    cOutVector numTcpSinkAppsVec;
    cOutVector nodes;
    cOutVector matSrc; // record all the source servers of the created short flows
    cOutVector matDest; // record all the dest servers of the created short flows

    cMessage *startManagerNode;
    int kValue;

    unsigned int IW;
    unsigned int ndpSwitchQueueLength;
    bool perFlowEcmp;
    bool perPacketEcmp;

    const char *trafficMatrixType; // either "permTM"  or "randTM"
    unsigned int test = 0;
    unsigned int arrivalRate; // lamda of an exponential distribution (Morteza uses 256 and 2560)
    unsigned int flowSize;
    unsigned int numServers;
    unsigned int numShortFlows;
    unsigned int longFlowSize;
    double percentLongFlowNodes;
    unsigned int numCompletedShortFlows = 0;
    cMessage *stopSimulation;
    std::vector<unsigned int> permServers;

    std::vector<unsigned int> permLongFlowsServers;
    std::vector<unsigned int> permShortFlowsServers;

    unsigned int numlongflowsRunningServers; // 33% of nodes run long flows
    unsigned int numshortflowRunningServers;

    unsigned int numIncastSenders;
    ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
    bool oneToOne = false;
//    const char *runMulticast; // for   multicasting
    bool oneToMany; // for   multicasting
    unsigned int numRunningMulticastGroups;
//    const char * manyToOne;
    bool manyToOne;
    unsigned int  numRunningMultiSourcingGroups;
    unsigned int  numReplica;
    bool daisyChainGFS;
////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////

    virtual bool handleOperationStage(LifecycleOperation *operation, int stage,
            IDoneCallback *doneCallback) override
            {
        Enter_Method_Silent(); throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName()); return true;}

    //  <dest, src>
    std::map<unsigned int, unsigned int> permMapLongFlows;
    std::map<unsigned int, unsigned int> permMapShortFlows;

    double sumArrivalTimes = 0;
    double newArrivalTime;
    bool shuffle = false;

    struct NodeLocation
    {
        unsigned int pod;
        unsigned int rack;
        unsigned int node;
        unsigned int index;

        unsigned int numTCPSink;
        unsigned int numTCPSession;
    };

    typedef std::list<NodeLocation> NodeLocationList;
    NodeLocationList nodeLocationList;

    unsigned int seedValue;
    std::mt19937 PRNG;
    std::exponential_distribution<double> expDistribution;

    struct RecordMat
    {
        unsigned int recordSrc;
        unsigned int recordDest;
    };
    typedef std::list<RecordMat> RecordMatList;
    RecordMatList recordMatList;


public:
    CentralSchedulerNdp()
    {
    }
    virtual ~CentralSchedulerNdp();

protected:
    virtual void initialize(int stage) override;
    //virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void handleParameterChange(const char *parname) override;

    void serversLocations();
    void generateTM();

    void getNewDestRandTM(std::string& itsSrc, std::string& newDest);
    void getNewDestPremTM(std::string& itsSrc, std::string& newDest);

    void findLocation(unsigned int nodeIndex, std::string& nodePodRackLoc);
    void scheduleLongFlows();
    void deleteAllSubModuleApp(const char *subModuleToBeRemoved);
    int findNumSumbodules(cModule* nodeModule, const char *subModuleType);
    void scheduleNewShortFlow(std::string itsSrc, std::string newDest);


    // multicast & multiSourcing
    void getNewThreeDestRandTMForMulticast(std::string& itsSrc, std::vector<std::string>& newDest );
    void scheduleNewMultiCastSession(std::string itsSrc, std::vector<std::string> newDest , unsigned int multicastGrpId);
    void scheduleNewDaisyChainSession(std::string itsSrc, std::vector<std::string> newDest , unsigned int multicastGrpId);

    void sortDaisyChainNodesBasedOnTopologicallyNearest(unsigned int sourceNode, std::vector<unsigned int> destinationNodes,  std::vector<unsigned int>& sortedNodes);
    void getNewThreeSrcRandTMForMultiSourcing(std::string& destNode, std::vector<std::string>& senders );
    void scheduleNewMultiSourcingSession(std::string dest, std::vector<std::string> senders , unsigned int multiSrcGroupId);

    void scheduleIncast(unsigned int numSenders);
    void getWebSearchWorkLoad();
    unsigned int getNewFlowSizeFromWebSearchWorkLoad();
    unsigned int getPriorityValue(unsigned int flowSize);


};

}

#endif // ifndef __INET_RQ_H


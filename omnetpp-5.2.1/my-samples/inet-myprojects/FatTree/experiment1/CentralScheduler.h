#ifndef __INET_RQ_H
#define __INET_RQ_H
#include <chrono>  // for high_resolution_clock

#include <map>
#include <set>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>
#include <cmath>
#include <time.h>       /* time */

#include "inet/common/INETDefs.h"

#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/applications/tcpapp/TCPSessionApp.h"

namespace inet {
class CentralScheduler : public cSimpleModule
{
//private:
protected:
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    simtime_t  totalSimTime;
    cOutVector permMapLongFlowsVec;
    cOutVector permMapShortFlowsVec;
    
    cOutVector randMapShortFlowsVec;
    cOutVector permMapShortFlowsVector;
    
    cOutVector numTcpSessionAppsVec;
    cOutVector numTcpSinkAppsVec;
    cOutVector nodes;
    cOutVector matSrc; // record all the source servers of the created short flows
    cOutVector matDest;// record all the dest servers of the created short flows
    

    cMessage *startManagerNode;
    int kValue;
    const char *trafficMatrixType;// either "permTM"  or "randTM"

    unsigned int arrivalRate; // lamda of an exponential distribution (Morteza uses 256 and 2560)
    unsigned int flowSize;
    unsigned int numServers;
    unsigned int numShortFlows;
    unsigned int  longFlowSize;
    double percentLongFlowNodes;
//    int matrix[4][numServers];
    unsigned int numCompletedShortFlows = 0;
    cMessage *stopSimulation;
    std::vector<unsigned int> permServers;

    std::vector<unsigned int> permLongFlowsServers;
    std::vector<unsigned int> permShortFlowsServers;

    unsigned int numlongflowsRunningServers; // 33% of nodes run long flows
    unsigned int numshortflowRunningServers;

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

// std::random_device rd; // uniformly-distributed integer random number generator
// std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation

    
    
    struct RecordMat
    {
        unsigned int recordSrc;
        unsigned int recordDest;
    };
    typedef std::list<RecordMat> RecordMatList;
    RecordMatList recordMatList;
    

    
public:
    CentralScheduler()
    {
    }
    virtual ~CentralScheduler();
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

    void permTM(const char *longOrShortFlows);

};

}

#endif // ifndef __INET_RQ_H


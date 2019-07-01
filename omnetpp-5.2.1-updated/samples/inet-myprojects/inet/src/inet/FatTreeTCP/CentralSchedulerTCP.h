// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

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
class CentralSchedulerTCP : public cSimpleModule
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
    //const char *multiUnicasting; // for tcp multicasting
    bool multiUnicasting;
    unsigned int numMulticastSessions;
   // const char * multiUniSourcing;
    unsigned int numReplicas;
    bool multiUniSourcing;
    unsigned int  numMultisourceSessions;
    bool oneToOne;
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
    unsigned int  numIncastSenders;
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
    CentralSchedulerTCP()
    {
    }
    virtual ~CentralSchedulerTCP();
protected:
    virtual void initialize(int stage) override;
    //virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual void handleParameterChange(const char *parname) override;

    void serversLocations();
    void generateTM();
    void getNewOutcast(std::string& itsSrc, std::string& newDest, unsigned int newSrc, unsigned int destNode);

    void getNewDestRandTM(std::string& itsSrc, std::string& newDest);
    void getNewDestPremTM(std::string& itsSrc, std::string& newDest);
    void getNewThreeDestRandTMForMultiUnicasting(std::string& itsSrc, std::vector<std::string>& newDest);
    void scheduleNewMultiCastSession(std::string  itsSrc, std::vector<std::string>  newDest ,  unsigned int multicastGrpId);

    void getNewThreeSrcRandTMForMultiSourcing(std::string& destNode, std::vector<std::string>& senders );
    void scheduleNewMultiSourcingSession(std::string  dest, std::vector<std::string>  senders , int multiSrcGroupId);

    void findLocation(unsigned int nodeIndex, std::string& nodePodRackLoc);
    void scheduleLongFlows();
    void deleteAllSubModuleApp(const char *subModuleToBeRemoved);
    int findNumSumbodules(cModule* nodeModule, const char *subModuleType);
    void scheduleNewShortFlow(std::string itsSrc, std::string newDest);
    void scheduleIncast(unsigned int senders);


};

}

#endif // ifndef __INET_RQ_H


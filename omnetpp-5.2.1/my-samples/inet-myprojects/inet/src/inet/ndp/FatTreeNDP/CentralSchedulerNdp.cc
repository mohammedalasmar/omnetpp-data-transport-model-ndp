
#include "CentralSchedulerNdp.h"

using namespace std;
using namespace std::chrono;

namespace inet {

Define_Module(CentralSchedulerNdp);

CentralSchedulerNdp::~CentralSchedulerNdp()
{
    cancelAndDelete(startManagerNode);
    cancelAndDelete(stopSimulation);

}

void CentralSchedulerNdp::initialize(int stage)
{
    myfile.open ("aaaaaaa.csv");
    isWebSearchWorkLoad = par("isWebSearchWorkLoad");
    indexWorkLoad = 0;

    // Record start time
    t1 = high_resolution_clock::now();
//    omnetpp::envir::Stopwatch stopwatch;
//    stopwatch.setRealTimeLimit(5);
    numCompletedShortFlows = par("numCompletedShortFlows");
    WATCH(numCompletedShortFlows);

    IW = par("IW");
    ndpSwitchQueueLength = par("ndpSwitchQueueLength");
    perFlowEcmp = par("perFlowEcmp");
    perPacketEcmp = par("perPacketEcmp");

    randMapShortFlowsVec.setName("randMapShortFlowsVec");
    permMapShortFlowsVector.setName("permMapShortFlowsVector");
    
    permMapLongFlowsVec.setName("permMapLongFlowsVec");
    permMapShortFlowsVec.setName("permMapShortFlowsVec");
    numTcpSessionAppsVec.setName("numTcpSessionAppsVec");
    numTcpSinkAppsVec.setName("numTcpSinkAppsVec");
    matSrc.setName("matSrc");
    matDest.setName("matDest");
    nodes.setName("nodes");
    
    std::cout << "\n\n Central flow scheduler \n";
    kValue = par("kValue");
    trafficMatrixType = par("trafficMatrixType");
    arrivalRate = par("arrivalRate");

    // seed vale and rng
     seedValue = par("seedValue");
     srand(seedValue);   //  srand(time(NULL));
     PRNG = std::mt19937(seedValue);
     expDistribution = std::exponential_distribution<double> (arrivalRate);


    flowSize = par("flowSize");
    numShortFlows = par("numShortFlows");
    longFlowSize = par("longFlowSize");
    numServers = std::pow(kValue, 3) / 4;
    shuffle = par("shuffle");

    percentLongFlowNodes = par("percentLongFlowNodes");
    numIncastSenders = par("numIncastSenders");
    oneToOne = par("oneToOne");
    daisyChainGFS = par("daisyChainGFS");
    // multicast variables multiSourcing
    oneToMany = par("oneToMany");
    numRunningMulticastGroups = par("numRunningMulticastGroups");
    manyToOne = par("manyToOne");
    numRunningMultiSourcingGroups = par("numRunningMultiSourcingGroups");

    numReplica = par("numReplica");
    std::cout << " =====  SIMULATION CONFIGURATIONS ========= " << "\n";
    std::cout << " =====  numServers   : " << numServers << "         ========= \n";
    std::cout << " =====  ShortflowSize: " << flowSize << "      ========= \n";
    std::cout << " =====  numShortFlows: " << numShortFlows << "          ========= \n";
    std::cout << " =====  arrivalRate  : " << arrivalRate << "       ========= \n";
    std::cout << " ========================================== " << "\n";
    stopSimulation=  new cMessage("stopSimulation");

    startManagerNode = new cMessage("startManagerNode");
    scheduleAt(0.0, startManagerNode);
}

void CentralSchedulerNdp::handleMessage(cMessage *msg)
{
    if (msg == stopSimulation) {
        std::cout << " All shortFlows COMPLETED  " << std::endl;
        totalSimTime=simTime();
        endSimulation();
    }

    std::cout << "******************** CentralSchedulerNdp::handleMessage .. ********************  \n";

    //  % of short flows and % of long flows
//    numlongflowsRunningServers = floor(numServers * 0.33); // 33% of nodes run long flows
    numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); // 33% of nodes run long flows , TODO throw error as it shouldn't be 1
    numshortflowRunningServers = numServers - numlongflowsRunningServers;
    std::cout << "numshortflowRunningServers:  " << numshortflowRunningServers << std::endl;
    std::cout << "numlongflowsRunningServers:  " << numlongflowsRunningServers << std::endl;

    generateTM();
    serversLocations();

    std::string itsSrc;
    std::string newDest;

    deleteAllSubModuleApp("ndpApp[0]");

    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    std::cout << "\n\n ******************** schedule Incast  .. ********************  \n";
    //    scheduleIncast(numIncastSenders);
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    std::cout << "\n\n ******************** schedule Long flows .. ********************  \n";
    scheduleLongFlows();


    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    if (oneToMany == true && manyToOne == false && oneToOne == false && daisyChainGFS == false) {
        for (unsigned int i = 1; i <= numRunningMulticastGroups ; i++) {
             std::cout << "\n\n\n multicast Group ID: " << i << std::endl;
             std::vector<std::string> replicasNodes;
             getNewThreeDestRandTMForMulticast(itsSrc, replicasNodes); // ndp multicasting (3 replicas) based on multi Unicasting
             scheduleNewMultiCastSession(itsSrc , replicasNodes , i);
        }
    }
    ////// daisyChainGFS  multicast
    else if (oneToMany  == false && manyToOne == false && oneToOne == false && daisyChainGFS == true) {
        for (unsigned int i = 1; i <= numRunningMulticastGroups ; i++) {
             std::cout << "\n\n\n daisyChainGFS ::: multicast Group ID: " << i << std::endl;
             std::vector<std::string> replicasNodes;
             getNewThreeDestRandTMForMulticast(itsSrc, replicasNodes); //   (3 replicas)
             scheduleNewDaisyChainSession(itsSrc , replicasNodes , i);
        }
    }
    ////////// ^^^^^^^
    else if (oneToMany  == false && manyToOne == true && oneToOne == false && daisyChainGFS == false) {
        for (unsigned int i = 1; i <= numRunningMultiSourcingGroups ; i++) {
            std::cout << "\n\n\n multi-sourcing Group ID: " << i << std::endl;
            std::vector<std::string> senders;
            getNewThreeSrcRandTMForMultiSourcing(newDest , senders); // ndp multisourcing (3 replicas) based on multi Unicasting
            scheduleNewMultiSourcingSession(newDest , senders ,  i);
        }
    }
    ////////
    else if (oneToMany  == false && manyToOne == false && oneToOne == true && daisyChainGFS == false) {
        if ( isWebSearchWorkLoad == true) getWebSearchWorkLoad();

        for (unsigned int i = 1; i <= numShortFlows; i++) {
            std::cout << "\n\n ******************** schedule Short flows .. ********************  \n";
            std::cout << " Shortflow ID: " << i << std::endl;
            if (strcmp(trafficMatrixType, "randTM") == 0)  getNewDestRandTM(itsSrc, newDest);
            if (strcmp(trafficMatrixType, "permTM") == 0)  getNewDestPremTM(itsSrc, newDest);
             scheduleNewShortFlow(itsSrc, newDest);
        }
    }
    std::cout << "\n\n\n";


}





void CentralSchedulerNdp::serversLocations()
{
    std::cout << "\n\n ******************** serversLocations .. ********************  \n";
    int totalNumberofPods = kValue;
    int totalNumberofRacks = (kValue / 2) * kValue;
    int racksPerPod = totalNumberofRacks / totalNumberofPods;
    int serversPerPod = pow(kValue, 2) / 4;
    int serversPerRack = kValue / 2;

    for (int m = 0; m < numServers; m++) {
        NodeLocation nodeLocation;
        nodeLocation.index = permServers.at(m);
        nodeLocation.pod = floor(permServers.at(m) / serversPerPod);
        nodeLocation.rack = floor((permServers.at(m) % serversPerPod) / serversPerRack);
        nodeLocation.node = permServers.at(m) % serversPerRack;
        nodeLocation.numTCPSink = 0;
        nodeLocation.numTCPSession = 0;
        nodeLocationList.push_back(nodeLocation);
    }

    std::list<NodeLocation>::iterator it;
    it = nodeLocationList.begin();
    while (it != nodeLocationList.end()) {
        std::cout << " index: " << it->index << " ==> " << " [pod, rack, node] =   ";
        std::cout << " [" << it->pod << ", " << it->rack << ", " << it->node << "] \n";
        it++;
    }
}


// random TM
void CentralSchedulerNdp::getNewDestRandTM(std::string& itsSrc, std::string& newDest) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination RandTM .. ********************  \n";
//    int newDestination = test;
    unsigned int newDestination = 0;
    unsigned int srcNewDestination = 0;
    while (newDestination == srcNewDestination) { // the dest should be different from the src
         newDestination = permServers.at( numlongflowsRunningServers+ (std::rand() % (numshortflowRunningServers)));
       //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
         srcNewDestination = permServers.at( numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    }
    std::cout << "@@@ newDestination " << newDestination << " , its src   "<< srcNewDestination << "\n";

    CentralSchedulerNdp::findLocation(newDestination, newDest);
    CentralSchedulerNdp::findLocation(srcNewDestination, itsSrc);
    
    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    
    // can be replaced by recordMatList ( see Finish())
    randMapShortFlowsVec.record(srcNewDestination);
    randMapShortFlowsVec.record(newDestination);
}


// permutation TM
void CentralSchedulerNdp::generateTM()
{
//    std::random_device rd; // uniformly-distributed integer random number generator-- seed
//    std::mt19937 rng(rd());
    std::cout << "\n\n ******************** generate TM maps.. ********************  \n";
    for (int i = 0; i < numServers; ++i)
        permServers.push_back(i);
     if (shuffle)
       std::shuffle(permServers.begin(), permServers.end(), PRNG); ///////////// TODO ooooooooooooooooooo

    for (int i = 0; i < numServers; ++i) {
        if (i < numlongflowsRunningServers) {
            permLongFlowsServers.push_back(permServers.at(i));
            permMapLongFlows.insert(std::pair<int, int>(permServers.at((i + 1) % numlongflowsRunningServers), permServers.at(i)));  // < dest, src >
        }
        else if (i >= numlongflowsRunningServers && i < numServers - 1) {
            permShortFlowsServers.push_back(permServers.at(i));
            permMapShortFlows.insert(std::pair<int, int>(permServers.at(i + 1), permServers.at(i)));  // < dest, src >
        }
        else if (i == numServers - 1) {
//            permShortFlowsServers.push_back(permServers.at(numlongflowsRunningServers));
            permShortFlowsServers.push_back(permServers.at(i));
            permMapShortFlows.insert(std::pair<int, int>(permServers.at(numlongflowsRunningServers), permServers.at(i)));  // < dest, src >
        }
    }

    std::cout << "permServers:                ";
    for (std::vector<unsigned int>::iterator it = permServers.begin(); it != permServers.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "permLongFlowsServers:       ";
    for (std::vector<unsigned int>::iterator it = permLongFlowsServers.begin(); it != permLongFlowsServers.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "permShortFlowsServers:      ";
    for (std::vector<unsigned int>::iterator it = permShortFlowsServers.begin(); it != permShortFlowsServers.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "permMapLongFlows:                 \n";
    for (std::map<unsigned int, unsigned int>::iterator iter = permMapLongFlows.begin(); iter != permMapLongFlows.end(); ++iter) {
        cout << "  src " << iter->second << " ==> ";
        cout << "  dest " << iter->first << "\n";
        permMapLongFlowsVec.record(iter->second);
        permMapLongFlowsVec.record( iter->first);
    }

    std::cout << "permMapShortFlows:                 \n";
    for (std::map<unsigned int, unsigned int>::iterator iter = permMapShortFlows.begin(); iter != permMapShortFlows.end(); ++iter) {
        cout << "   src " << iter->second << " ==> ";
        cout << "   dest " << iter->first << "\n";
        permMapShortFlowsVec.record(iter->second );
        permMapShortFlowsVec.record(iter->first );
    }

}

void CentralSchedulerNdp::getNewDestPremTM(std::string& itsSrc, std::string& newDest)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination PremTM .. ********************  \n";
    int newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));

    int srcNewDestination = permMapShortFlows.find(newDestination)->second;
    std::cout << "@@@ newDestination " << newDestination << " , its src   " << srcNewDestination << "\n";

    CentralSchedulerNdp::findLocation(newDestination, newDest);
    CentralSchedulerNdp::findLocation(srcNewDestination, itsSrc);
//    std::cout << " newDest " << newDest << "\n";
//    std::cout << " itsSrc " << itsSrc << "\n";
    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    
    permMapShortFlowsVector.record(srcNewDestination);
    permMapShortFlowsVector.record(newDestination);
}

void CentralSchedulerNdp::findLocation(unsigned int nodeIndex, std::string& nodePodRackLoc)
{
    std::list<NodeLocation>::iterator itt;
    itt = nodeLocationList.begin();
    while (itt != nodeLocationList.end()) {
        if (itt->index == nodeIndex) {
            nodePodRackLoc = "FatTreeNdp.Pod[" + std::to_string(itt->pod) + "].racks[" + std::to_string(itt->rack) + "].servers[" + std::to_string(itt->node) + "]";
        }
        itt++;
    }
}

void CentralSchedulerNdp::scheduleLongFlows()
{
    std::cout << "\n\n ******************** scheduleLongFlows .. ********************  \n";
    std::string dest;
    std::string source;

// iterate permMapLongFlows
    for (std::map<unsigned int, unsigned int>::iterator iter = permMapLongFlows.begin(); iter != permMapLongFlows.end(); ++iter) {
        cout << "\n\n NEW LONGFLOW :)   ";
        cout << "  host(SRC.)= " << iter->second << " ==> " << "  host(DEST.)= " << iter->first << "\n";

        RecordMat recordMat;
        recordMat.recordSrc = iter->second ;
        recordMat.recordDest = iter->first;
        recordMatList.push_back(recordMat);
        
        CentralSchedulerNdp::findLocation(iter->first, dest);
        CentralSchedulerNdp::findLocation(iter->second, source);
        cout << "  nodePodRackLoc:  " << iter->second << " == " << source << " ==> " << iter->first << " == " << dest << "\n";

        cModule* srcModule = getModuleByPath(source.c_str());
        cModule* destModule = getModuleByPath(dest.c_str());


        // Receiver sink app
        cModule* ndpDestModule = destModule->getSubmodule("ndp");
        int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
        int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
        ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
        ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
        int newNumNdpSinkAppsDest = findNumSumbodules(destModule, "inet.ndp.application.ndpapp.NdpSinkApp") + 1;
        cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp");
        std::string nameNdpAppDest = "ndpApp[" + std::to_string(newNumNdpSinkAppsDest - 1) + "]";
        cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);
        newDestAppModule->par("isLongFlow").setBoolValue(true);
        //   --------<ndpIn         appOut[]<----------
        //     ndpApp                          ndp
        //   -------->ndpOut        appIn[] >----------
        cGate *gateNdpInDest = ndpDestModule->gate("appIn", newNdpGateOutSizeDest - 1);
        cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
        cGate *gateInDest = newDestAppModule->gate("ndpIn");
        cGate *gateOutDest = newDestAppModule->gate("ndpOut");
        gateNdpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateNdpInDest);
        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();
        newDestAppModule->par("localAddress").setStringValue(dest.c_str());
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);
        newDestAppModule->par("isLongFlow").setBoolValue(true);


        // Sender  app
        cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
        int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
        int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
        ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
        ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
        int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
        cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp");
        std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);
        newSrcAppModule->par("localAddress").setStringValue(source.c_str());
        newSrcAppModule->par("connectAddress").setStringValue(dest.c_str());
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);
        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl());
        // >>>>>>
        newSrcAppModule->par("numPacketsToSend").setDoubleValue(longFlowSize); // should be longFlowSize
        unsigned int priority = 0; // TODO
        newSrcAppModule->par("priorityValue").setDoubleValue(priority);
        //   --------<ndpIn         appOut[]<----------
        //     ndpApp                          ndp
        //   -------->ndpOut        appIn[] >----------
        cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
        cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
        cGate *gateIn = newSrcAppModule->gate("ndpIn");
        cGate *gateOut = newSrcAppModule->gate("ndpOut");
        gateNdpOut->connectTo(gateIn);
        gateOut->connectTo(gateNdpIn);
        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();
        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl());
    }
}



void CentralSchedulerNdp::scheduleIncast(unsigned int numSenders)
{

    std::string itsSrc;
    std::string newDest;
    unsigned int newDestination = 0;
    CentralSchedulerNdp::findLocation(newDestination, newDest);


    sumArrivalTimes = 0;


    // get the src ndp module
    cModule* destModule = getModuleByPath(newDest.c_str());
    cModule* ndpDestModule = destModule->getSubmodule("ndp");
    unsigned int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
    unsigned int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
    ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
    ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
    unsigned int newNumNdpSinkAppsDest = findNumSumbodules(destModule, "inet.ndp.application.ndpapp.NdpSinkApp") + 1;
    cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp");
    std::string nameNdpAppDest = "ndpApp[" + std::to_string(newNumNdpSinkAppsDest - 1) + "]";
    cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
    newDestAppModule->par("localPort").setDoubleValue(80 +newNumNdpSinkAppsDest);

    newDestAppModule->par("isLongFlow").setBoolValue(false);
    cGate *gateNdpInDest = ndpDestModule->gate("appIn", newNdpGateOutSizeDest - 1);
    cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
    cGate *gateInDest = newDestAppModule->gate("ndpIn");
    cGate *gateOutDest = newDestAppModule->gate("ndpOut");
    gateNdpOutDest->connectTo(gateInDest);
    gateOutDest->connectTo(gateNdpInDest);
    newDestAppModule->finalizeParameters();
    newDestAppModule->buildInside();
    newDestAppModule->scheduleStart(simTime());
    newDestAppModule->callInitialize();

    for (int i=0; i< numSenders; ++i){


    unsigned int srcNewDestination = 0;
    while (newDestination == srcNewDestination) {
        srcNewDestination = permServers.at(  numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    }

    CentralSchedulerNdp::findLocation(srcNewDestination, itsSrc);

    cModule* srcModule = getModuleByPath(itsSrc.c_str());  // const char* c_str Return pointer to the string.
    cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
    unsigned int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
    unsigned int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
    ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
    ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
    unsigned int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
    cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp");
    std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
    cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);
    newSrcAppModule->par("connectAddress").setStringValue(newDest);
    newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);  //??? to be checked
    newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl()+ sumArrivalTimes);
    newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //


    cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
    cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
    cGate *gateIn = newSrcAppModule->gate("ndpIn");
    cGate *gateOut = newSrcAppModule->gate("ndpOut");
    gateNdpOut->connectTo(gateIn);
    gateOut->connectTo(gateNdpIn);
    newSrcAppModule->finalizeParameters();
    newSrcAppModule->buildInside();
    newSrcAppModule->scheduleStart(simTime());
    newSrcAppModule->callInitialize();
    newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl()+ sumArrivalTimes);
    }
}




void CentralSchedulerNdp::scheduleNewShortFlow(std::string itsSrc, std::string newDest)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewShortFlow .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " newDest " << newDest << "\n";
    std::cout << " itsSrc " << itsSrc << "\n";

    newArrivalTime = expDistribution.operator()(PRNG);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;
    std::cout << " newArrivalTime = " << newArrivalTime << "\n\n";
    cModule* srcModule = getModuleByPath(itsSrc.c_str());
    cModule* destModule = getModuleByPath(newDest.c_str());
    std::cout << "srcModule:  " << srcModule->getFullPath()<< "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;

    // sink app
    cModule* ndpDestModule = destModule->getSubmodule("ndp");
    unsigned int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
    unsigned int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
    ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
    ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
    unsigned int newNumNdpSinkAppsDest = findNumSumbodules(destModule,"inet.ndp.application.ndpapp.NdpSinkApp") + 1;
    // find factory object
    cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp");
    std::string nameNdpAppDest = "ndpApp["+ std::to_string(newNumNdpSinkAppsDest - 1) + "]";
    // create module and build its submodules (if any)
    cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
    newDestAppModule->par("localAddress").setStringValue(newDest);
    newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);
    newDestAppModule->par("isLongFlow").setBoolValue(false);


    //   --------<ndpIn         ndpOut[]<----------
    //     ndpApp                          ndp
    //   -------->ndpOut        appIn[] >----------
    cGate *gateNdpInDest = ndpDestModule->gate("appIn",newNdpGateOutSizeDest - 1);
    cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
    cGate *gateInDest = newDestAppModule->gate("ndpIn");
    cGate *gateOutDest = newDestAppModule->gate("ndpOut");
    gateNdpOutDest->connectTo(gateInDest);
    gateOutDest->connectTo(gateNdpInDest);
    newDestAppModule->finalizeParameters();
    newDestAppModule->buildInside();
    newDestAppModule->scheduleStart(simTime());
    newDestAppModule->callInitialize();


    // src app
    cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
    unsigned int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
    unsigned int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
    ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
    ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
    unsigned int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
    // find factory object
    cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp");
    std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
    cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);

    newSrcAppModule->par("localAddress").setStringValue(itsSrc);
    newSrcAppModule->par("connectAddress").setStringValue(newDest);
    newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);
    newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    // >>>>>>
    if (isWebSearchWorkLoad == false){
        newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
        unsigned int priority = getPriorityValue(flowSize);
        newSrcAppModule->par("priorityValue").setDoubleValue(priority);
    } else if (isWebSearchWorkLoad == true){
        unsigned int newFlowSize = getNewFlowSizeFromWebSearchWorkLoad();
        newSrcAppModule->par("numPacketsToSend").setDoubleValue(newFlowSize); //
        unsigned int priority = getPriorityValue(newFlowSize);
        newSrcAppModule->par("priorityValue").setDoubleValue(priority);
    }
    // <<<<<<<<

    //   --------<ndpIn         appOut[]<----------
    //     ndpApp                          ndp
    //   -------->ndpOut        appIn[] >----------
    cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
    cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
    cGate *gateIn = newSrcAppModule->gate("ndpIn");
    cGate *gateOut = newSrcAppModule->gate("ndpOut");
    gateNdpOut->connectTo(gateIn);
    gateOut->connectTo(gateNdpIn);
    newSrcAppModule->finalizeParameters();
    newSrcAppModule->buildInside();
    newSrcAppModule->scheduleStart(simTime());
    newSrcAppModule->callInitialize();
    newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl()+ sumArrivalTimes);
}

int CentralSchedulerNdp::findNumSumbodules(cModule* nodeModule, const char *subModuleType)
{
    unsigned int rep = 0;
    for (cModule::SubmoduleIterator iter(nodeModule); !iter.end(); iter++) {
        cModule *subModule = *iter;
        if (strcmp(subModule->getModuleType()->getFullName(), subModuleType) == 0) {
            rep++;
        }
    }
    return rep;
}

void CentralSchedulerNdp::deleteAllSubModuleApp(const char *subModuleToBeRemoved)
{
    std::cout << "\n\n ******************** deleteAll temp SubModuleApp  .. ********************  \n";
    std::string node;
    for (int i = 0; i < numServers; i++) {
        CentralSchedulerNdp::findLocation(i, node);
        cModule* nodeModule = getModuleByPath(node.c_str());
        // delete ndpApp[0]

        cModule* tempTcpAppModule = nullptr;
        for (cModule::SubmoduleIterator iter(nodeModule); !iter.end(); iter++) {
            cModule *subModule = *iter;
            if (strcmp(subModule->getFullName(), subModuleToBeRemoved) == 0) {
                tempTcpAppModule = subModule;
            }
        }
        tempTcpAppModule->deleteModule();
        cModule* ndpSrcModule = nodeModule->getSubmodule("ndp");
        ndpSrcModule->setGateSize("appOut", 0);
        ndpSrcModule->setGateSize("appIn", 0);
    }
    std::cout << " Done.. \n";
}


void CentralSchedulerNdp::finish()
{
    myfile.close();
    for (std::vector<unsigned int>::iterator iter = permServers.begin(); iter != permServers.end(); ++iter) {
        cout << "  NODE= " << *iter << "  ";
        nodes.record(*iter);

        std::string source;
        CentralSchedulerNdp::findLocation(*iter, source); // get dest value
//        cout << "  nodePodRackLoc:  " << iter->second << " == " << source << " ==> " << iter->first << " == " << dest << "\n";
        cModule* srcModule = getModuleByPath(source.c_str());

        int finalNumTcpSessionApps = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp");
        int finalNumTcpSinkApps = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpSinkApp");

        std::cout << "  finalNumTcpSessionApps:  " << finalNumTcpSessionApps << ",  finalNumTcpSinkApps: " << finalNumTcpSinkApps << "\n";
        numTcpSessionAppsVec.record(finalNumTcpSessionApps);
        numTcpSinkAppsVec.record(finalNumTcpSinkApps);
    }

    std::cout << "numshortflowRunningServers:  " << numshortflowRunningServers << std::endl;
    std::cout << "numlongflowsRunningServers:  " << numlongflowsRunningServers << std::endl;

    std::cout << "permLongFlowsServers:       ";
    for (std::vector<unsigned int>::iterator it = permLongFlowsServers.begin(); it != permLongFlowsServers.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';




    // Record end time
    t2 = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(t2 - t1).count();
    std::cout << "=================================================== "  << std::endl;
    std::cout << " total Wall Clock Time (Real Time) = " << duration <<  " minutes" << std::endl;
    std::cout << " total Simulation Time      = " << totalSimTime <<  " sec" << std::endl;
    std::cout << "=================================================== "  << std::endl;
    std::cout << " num completed shortflows = " << numCompletedShortFlows << std::endl;


    recordScalar("simTimeTotal=", totalSimTime);
    recordScalar("numShortFlows=", numShortFlows);
    recordScalar("flowSize=", flowSize);
    recordScalar("percentLongFlowNodes=", percentLongFlowNodes);
    recordScalar("arrivalRate=", arrivalRate);
    if (strcmp(trafficMatrixType, "permTM") == 0)  recordScalar("permTM", 1);
    if (strcmp(trafficMatrixType, "randTM") == 0)  recordScalar("randTM", 1);
    recordScalar("wallClockTime=", duration);


    recordScalar("IW=", IW);
    recordScalar("ndpSwitchQueueLength=", ndpSwitchQueueLength);

    recordScalar("perFlowEcmp=", perFlowEcmp);
    recordScalar("perPacketEcmp=", perPacketEcmp);
    recordScalar("oneToOne=", oneToOne);
    recordScalar("oneToMany=", oneToMany);
    recordScalar("manyToOne=", manyToOne);
    recordScalar("seedValue=", seedValue);
    recordScalar("kValue=", kValue);

    recordScalar("numReplica=", numReplica);
    recordScalar("numRunningMulticastGroups=", numRunningMulticastGroups);
    recordScalar("numRunningMultiSourcingGroups=", numRunningMultiSourcingGroups);
    recordScalar("isWebSearchWorkLoad=", isWebSearchWorkLoad);


    //   int i=0;
    std::list<RecordMat>::iterator itt;
    itt = recordMatList.begin();
    while (itt != recordMatList.end()) {
        matSrc.record(itt->recordSrc);
        matDest.record(itt->recordDest);
        //        std::cout << " flowNumber = " << ++i  << " src: " << itt->recordSrc << " , destttttt= " << itt->recordDest << std::endl;
        itt++;
    }
}

void CentralSchedulerNdp::handleParameterChange(const char *parname)
{
      std::cout << " CentralSchedulerNdp num completed shortflows = " << numCompletedShortFlows << std::endl;
    if (parname && strcmp(parname, "numCompletedShortFlows") == 0) {
//        numCompletedShortFlows = par("numCompletedShortFlows");
        ++numCompletedShortFlows;
        std::cout << " num completed shortflows = " << numCompletedShortFlows << "\n\n\n\n";

        if (oneToOne == true && numCompletedShortFlows == numShortFlows && oneToMany == false && manyToOne == false) {
//             getSimulation()->callFinish();
            scheduleAt(simTime(), stopSimulation);
        }

        if (oneToMany == true && manyToOne == false && oneToOne == false && numCompletedShortFlows == numReplica*numRunningMulticastGroups) {
            scheduleAt(simTime(), stopSimulation);
        }

        if (oneToMany == false && manyToOne == true && oneToOne == false && numCompletedShortFlows == numReplica*numRunningMultiSourcingGroups) {
            scheduleAt(simTime(), stopSimulation);
        }


    }
}






void CentralSchedulerNdp::getWebSearchWorkLoad() {
    unsigned int numFlows = numShortFlows;
    double a[numFlows];
    std::ifstream myfile("../inputWokLoad.txt");
    if (myfile.is_open()) {
        int i = 0;
        while (i < numFlows && myfile >> a[i]) {
            flowSizeWebSeachWorkLoad.push_back(a[i]);
             std::cout << a[i] << " ";
            i++;
        }
        myfile.close();
    } else
        std::cerr << "Unable to open file" << endl;

    for (auto iter = flowSizeWebSeachWorkLoad.begin();
            iter != flowSizeWebSeachWorkLoad.end(); ++iter) {
//           std::cout << " \nooooo = " << *iter << "\n";
    }
}

unsigned int CentralSchedulerNdp::getNewFlowSizeFromWebSearchWorkLoad() {
    unsigned int newFLowSize = flowSizeWebSeachWorkLoad.at(indexWorkLoad);
    ++indexWorkLoad;
    return newFLowSize;
}


// 0     --> 10KB    P=1
// 10KB  --> 100KB   P=2
// 100KB --> 1MB     P=3
// 1MB   --> 10MB    P=4
// otherwise (longflows)         P=0 (RaptorQBasicClientApp.ned --> int priorityValue = default(0);)
unsigned int CentralSchedulerNdp::getPriorityValue(unsigned int flowSize) {
//    std::cout << "CentralSchedulerNdp::getPriorityValue \n\n ";
    unsigned int priorityValue;
    if (flowSize >=1 && flowSize <=7) {
        priorityValue = 1;
        return priorityValue;
    }

    if (flowSize >=8 && flowSize <=67) {
        priorityValue = 2;
        return priorityValue;
    }

    if (flowSize >=68 && flowSize <=667) {
        priorityValue = 3;
        return priorityValue;
    }

    if (flowSize >=668 && flowSize <=6667) {
        priorityValue = 4;
        return priorityValue;
    }

    return 0;
}






// ;;;;;;;;;;;;;;;;;;












// random TM for multicasting (multicast 3 replicas)
void CentralSchedulerNdp::getNewThreeDestRandTMForMulticast(std::string& itsSrc, std::vector<std::string>& newDest ) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewThreeDestRandTMForoneToMany    3 replicas multicast .. ********************  \n";
//    int newDestination = test;
    unsigned int newDestination = 0;
    unsigned int srcNewDestination = 0;
    unsigned int oldDest ;

    std::vector<unsigned int> destinationNodes;
    std::vector<unsigned int> sortedNodes;

    srcNewDestination = permServers.at( numlongflowsRunningServers  + (std::rand() % (numshortflowRunningServers)));
    newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    std::string  selectedDest;
    for (int i = 0; i < numReplica; ++i) {
        while (newDestination == srcNewDestination) {
            newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
            if (newDestination == oldDest ) newDestination=srcNewDestination; // to get unique destinations for this multicast group
            //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
//            std::cout << "wwwwwwww " << newDestination << " , multicast source node   " << srcNewDestination << "\n";

        }
        std::cout << "@@@ newDestination " << newDestination << " , multicast source node   " << srcNewDestination << "\n";
        oldDest = newDestination;

        destinationNodes.push_back(newDestination);

         // identifying the servers locations: FatTreeTopology.Pod[].racks[].servers[]
//        CentralSchedulerNdp::findLocation(newDestination, selectedDest);
//        newDest.push_back(selectedDest);
        newDestination = srcNewDestination;
    }

    // NB: this only works for 3 replicas
    // 162 --> destinationNodes (13--> 90 --> 234)
    // 162 --> sortedNodes(90 --> 234 --> 13)
    // 162 --> sortedNodes4 (90 --> 13 --> 234)
     sortDaisyChainNodesBasedOnTopologicallyNearest(srcNewDestination, destinationNodes , sortedNodes );

     std::vector<unsigned int> sortedNodes2(2);
     sortedNodes2.at(0) = sortedNodes.at(1);
     sortedNodes2.at(1) = sortedNodes.at(2);
     std::vector<unsigned int> sortedNodes3;

     sortDaisyChainNodesBasedOnTopologicallyNearest(sortedNodes.at(0), sortedNodes2 , sortedNodes3 );

     std::vector<unsigned int> sortedNodes4(3);
     sortedNodes4.at(0) = sortedNodes.at(0);
     sortedNodes4.at(1) = sortedNodes3.at(0);
     sortedNodes4.at(2) = sortedNodes3.at(1);


    for (auto iter = sortedNodes4.begin(); iter!= sortedNodes4.end(); ++iter){
        std::cout << " moh ........ "<< *iter<<"\n\n\n";

        CentralSchedulerNdp::findLocation(*iter, selectedDest);
        newDest.push_back(selectedDest);
    }


    CentralSchedulerNdp::findLocation(srcNewDestination, itsSrc);
}

// daisy chain GFS sorting the selected destination nodes (src-->replica1-->replica2-->replica3) based on nearest
//  Sender writes to the topologically nearest replica
void CentralSchedulerNdp::sortDaisyChainNodesBasedOnTopologicallyNearest(unsigned int sourceNode, std::vector<unsigned int> destinationNodes,  std::vector<unsigned int>& sortedNodes){
    std::vector <unsigned int> diff;
//    struct diffDest {
//        unsigned int diff, dest ;
//    };
    unsigned int difference;
    std::vector<differenceBetweenSrcNodeAndDestNode> diffDestValues;
    differenceBetweenSrcNodeAndDestNode diffDestStru;
    for (auto iter = destinationNodes.begin(); iter!= destinationNodes.end(); ++iter){
        if(sourceNode >= *iter){
            difference = sourceNode - *iter;
            diffDestStru.dest =  *iter;
            diffDestStru.diff = difference;
            diffDestValues.push_back(diffDestStru);
        } else {
            difference = *iter - sourceNode;
            diffDestStru.dest =  *iter;
            diffDestStru.diff = difference;
            diffDestValues.push_back(diffDestStru);        }
    }

//    for (auto x : diffDestValues)
//            cout << "[" << x.diff << ", " << x.dest << "] ";

    std::sort(diffDestValues.begin(), diffDestValues.end());
    for (auto iter = diffDestValues.begin(); iter!= diffDestValues.end(); ++iter){
        sortedNodes.push_back(iter->dest);
//        cout << " diff = " << iter->diff << " dest" << iter->dest << "\n";
    }

}



// random TM for manyToOne (fetch 3 replicas) multisourcing
void CentralSchedulerNdp::getNewThreeSrcRandTMForMultiSourcing(std::string& destNode, std::vector<std::string>& senders ) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNew  Three  Src RandTM  For   MultiSourcing   fetch 3 replicas   .. ********************  \n";
    //    int newDestination = test;
        unsigned int src = 0;
        unsigned int destination = 0;
        unsigned int oldDest ;

        destination = permServers.at( numlongflowsRunningServers  + (std::rand() % (numshortflowRunningServers)));
        src = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
        std::string  selectedSrc;
        for (int i = 0; i < numReplica; ++i) {
            while (src == destination) {
                src = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
                if (src == oldDest ) src=destination; // to get unique destinations for this multicast group
                //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
    //            std::cout << "wwwwwwww " << newDestination << " , multicast source node   " << srcNewDestination << "\n";

            }
            std::cout << "@@@ MultiSourcing src " << src << " ,  dest   " <<destination << "\n";
             oldDest = src;

             // identifying the servers locations: FatTreeTopology.Pod[].racks[].servers[]
            CentralSchedulerNdp::findLocation(src, selectedSrc);
            senders.push_back(selectedSrc);
            src = destination;
        }
        CentralSchedulerNdp::findLocation(destination, destNode);
}



void CentralSchedulerNdp::scheduleNewDaisyChainSession(std::string itsSrc, std::vector<std::string> newDest, unsigned int multicastGrpId) // three replicas
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewMultiCastSession three replicas .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " itsSrc " << itsSrc << "\n";

    newArrivalTime = expDistribution.operator()(PRNG);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;

    // multicasting
    // ===================================== Daisy Chain GFS workload ============================================
    //            Sender                                                                           ===
    //       --------------------------------                           -------------------        ===
    //       |  NdpBasicClientApp --> conn1 -|-------------------->     | Receiver 1 Sink  |       ===
    //       --------------------------------                            ------------------        ===
    //                                                                           v
    //                                                                           v
    //                                                                   ------------------        ===
    //                                                                  | Receiver 2 Sink  |       ===
    //                                                                   ------------------        ===
    //                                                                           v
    //                                                                           v
    //                                                                   ------------------        ===
    //                                                                  | Receiver 3 Sink  |       ===
    //                                                                   ------------------        ===

    // NOTE: all connections start at the same sumArrivalTimes (this is not realistic)
    // In reality: Pipelined: each replica forwards as it receives
    //      goodput = ave(goodputs: sink1,sink2,sink3)                                            ===
    // ==============================================================================================

//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;
    for (auto iter = newDest.begin(); iter != newDest.end(); ++iter) {
        std::string thisDest = *iter;
        std::cout << " \n\n\n\n NEW conn in DAISY CHAIN ........... " << newArrivalTime <<"\n";

        std::cout << " itsSrc " << itsSrc << "\n";
        std::cout << " newDest " << thisDest << "\n";
        cModule* destModule = getModuleByPath(thisDest.c_str());
        cModule* ndpDestModule = destModule->getSubmodule("ndp");
        unsigned int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
        unsigned int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
        ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
        ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
        unsigned int newNumNdpSinkAppsDest = findNumSumbodules(destModule, "inet.ndp.application.ndpapp.NdpSinkApp") + 1;
        std::cout << "Dest  NumTCPSinkApp   =  " << newNumNdpSinkAppsDest << "\n";
        cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp"); // find factory object
        std::string nameNdpAppDest = "ndpApp[" + std::to_string(newNumNdpSinkAppsDest - 1) + "]";

        std::string sinkName = thisDest + "." + nameNdpAppDest;

        myfile << sinkName << "\n";

        std::cout << " newDest sinkName: " << sinkName << "\n";

        cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);

        newDestAppModule->par("isLongFlow").setBoolValue(false);
        newDestAppModule->par("multiCastGroupId").setDoubleValue(multicastGrpId);

        cGate *gateNdpInDest = ndpDestModule->gate("appIn", newNdpGateOutSizeDest - 1);
        cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
        cGate *gateInDest = newDestAppModule->gate("ndpIn");
        cGate *gateOutDest = newDestAppModule->gate("ndpOut");
        gateNdpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateNdpInDest);
        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();

        // get the src ndp module
        cModule* srcModule = getModuleByPath(itsSrc.c_str()); // const char* c_str Return pointer to the string.
        cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
        unsigned int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
        unsigned int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
        ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
        ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
        unsigned int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
        std::cout << "Src  numTCPSessionApp =  " << newNumNdpSessionAppsSrc << "\n";
        cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp"); // find factory object
        std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);

        newSrcAppModule->par("connectAddress").setStringValue(thisDest);
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);  //??? to be checked

        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);

//        newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
        /// >>>>>>>>>>>>
        if (isWebSearchWorkLoad == false){
             newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
            // aha .....
            unsigned int priority = getPriorityValue(flowSize);
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }

        if (isWebSearchWorkLoad == true){
            unsigned int newFlowSize = getNewFlowSizeFromWebSearchWorkLoad();
            newSrcAppModule->par("numPacketsToSend").setDoubleValue(newFlowSize); //

            unsigned int priority = getPriorityValue(newFlowSize);

            std::cout << " getPriorityValueppp = " <<priority <<"\n\n";
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }
        /// >>>>>>>>>>>

        cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
        cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
        cGate *gateIn = newSrcAppModule->gate("ndpIn");
        cGate *gateOut = newSrcAppModule->gate("ndpOut");
        gateNdpOut->connectTo(gateIn);
        gateOut->connectTo(gateNdpIn);
        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();
        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);
        //
        // NEW daisy chain next
        //
         itsSrc = thisDest;
//         newArrivalTime=newArrivalTime+0.000001;
    }
}



void CentralSchedulerNdp::scheduleNewMultiCastSession(std::string itsSrc, std::vector<std::string> newDest, unsigned int multicastGrpId) // three replicas
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewMultiCastSession three replicas .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " itsSrc " << itsSrc << "\n";

    newArrivalTime = expDistribution.operator()(PRNG);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;

    // multicasting
    // ===================================== ONE SESSION ============================================
    //            Sender                                                                          ===
    //       --------------------------------                           -------------------       ===
    //       |  NdpBasicClientApp --> conn1 -|-------------------->    | Receiver 1 Sink  |       ===
    //       |                               |                           ------------------       ===
    //       |                               |                           ------------------       ===
    //       |  NdpBasicClientApp --> conn2 -|-------------------->    | Receiver 2 Sink  |       ===
    //       |                               |                           ------------------       ===
    //       |                               |                           ------------------       ===
    //       |  NdpBasicClientApp --> conn3 -|-------------------->    | Receiver 3 Sink  |       ===
    //       --------------------------------                           -------------------       ===
    //      goodput = ave(goodputs: sink1,sink2,sink3)                                            ===
    // ==============================================================================================

//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;
    for (auto iter = newDest.begin(); iter != newDest.end(); ++iter) {
        std::string thisDest = *iter;
        std::cout << " newDest " << thisDest << "\n";
        cModule* destModule = getModuleByPath(thisDest.c_str());
        cModule* ndpDestModule = destModule->getSubmodule("ndp");
        unsigned int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
        unsigned int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
        ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
        ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
        unsigned int newNumNdpSinkAppsDest = findNumSumbodules(destModule, "inet.ndp.application.ndpapp.NdpSinkApp") + 1;
        std::cout << "Dest  NumTCPSinkApp   =  " << newNumNdpSinkAppsDest << "\n";
        cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp"); // find factory object
        std::string nameNdpAppDest = "ndpApp[" + std::to_string(newNumNdpSinkAppsDest - 1) + "]";

        std::string sinkName = thisDest + "." + nameNdpAppDest;

        myfile << sinkName << "\n";

        std::cout << " newDest sinkName: " << sinkName << "\n";

        cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);

        newDestAppModule->par("isLongFlow").setBoolValue(false);
        newDestAppModule->par("multiCastGroupId").setDoubleValue(multicastGrpId);

        cGate *gateNdpInDest = ndpDestModule->gate("appIn", newNdpGateOutSizeDest - 1);
        cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
        cGate *gateInDest = newDestAppModule->gate("ndpIn");
        cGate *gateOutDest = newDestAppModule->gate("ndpOut");
        gateNdpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateNdpInDest);
        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();

        // get the src ndp module
        cModule* srcModule = getModuleByPath(itsSrc.c_str()); // const char* c_str Return pointer to the string.
        cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
        unsigned int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
        unsigned int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
        ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
        ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
        unsigned int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
        std::cout << "Src  numTCPSessionApp =  " << newNumNdpSessionAppsSrc << "\n";
        cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp"); // find factory object
        std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);

        newSrcAppModule->par("connectAddress").setStringValue(thisDest);
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);  //??? to be checked

        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);



//        newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
        /// >>>>>>>>>>>>
        if (isWebSearchWorkLoad == false){
             newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
            // aha .....
            unsigned int priority = getPriorityValue(flowSize);
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }

        if (isWebSearchWorkLoad == true){
            unsigned int newFlowSize = getNewFlowSizeFromWebSearchWorkLoad();
            newSrcAppModule->par("numPacketsToSend").setDoubleValue(newFlowSize); //

            unsigned int priority = getPriorityValue(newFlowSize);

            std::cout << " getPriorityValueppp = " <<priority <<"\n\n";
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }
        /// >>>>>>>>>>>

        cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
        cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
        cGate *gateIn = newSrcAppModule->gate("ndpIn");
        cGate *gateOut = newSrcAppModule->gate("ndpOut");
        gateNdpOut->connectTo(gateIn);
        gateOut->connectTo(gateNdpIn);
        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();
        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    }
}


void CentralSchedulerNdp::scheduleNewMultiSourcingSession(std::string dest, std::vector<std::string> senders, unsigned int multiSrcGroupId) // three replicas
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewMultiSourcingSession fetch three replicas  multi sourcing .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " dest nodes: " << dest << "\n";

// this block used to be here not in the for loop below
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>>
    //    newArrivalTime = expDistribution.operator()(PRNG);   // >>>>>>>>>
    //    sumArrivalTimes = sumArrivalTimes + newArrivalTime;  // >>>>>>>>
    // >>>>>>>>>>>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>>





//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;

// multi-sourcing
// ===================================== ONE SESSION ============================================
//          Receiver
//   --------        ------------
//   |      |        |   conn1  |   <------------------    Sender 1 (NdpBasicClientApp) object1
//   | SINK |  <---- |   conn2  |   <------------------    Sender 2 (NdpBasicClientApp) object2
//   |      |        |   conn3  |   <------------------    Sender 3 (NdpBasicClientApp) object3
//   --------        ------------
//      goodput = SINK ? but this gives high goodput as three connections serve the sink
// ==============================================================================================
// to use this way take  WAY-I block outside the for loop
  int test = 0;
  newArrivalTime = expDistribution.operator()(PRNG);
  sumArrivalTimes = sumArrivalTimes + newArrivalTime;
    for (auto iter = senders.begin(); iter != senders.end(); ++iter) {
//        ++test;
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>>
//            newArrivalTime = expDistribution.operator()(PRNG);   // >>>>>>>>>

//            sumArrivalTimes = sumArrivalTimes + newArrivalTime;
//
//             if (test < 3)  sumArrivalTimes = sumArrivalTimes + newArrivalTime;  // >>>>>>>>
//            if (test == 2)  sumArrivalTimes = sumArrivalTimes + newArrivalTime;  // >>>>>>>>

        // >>>>>>>>>>>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>> >>>>>>>>>>>

        // multi-sourcing
        //            Receiver
        //       --------------------
        //       |  sink1 <-- conn1  |   <------------------    Sender 1 (NdpBasicClientApp)
        //       |  sink2 <-- conn2  |   <------------------    Sender 2 (NdpBasicClientApp)
        //       |  sink3 <-- conn3  |   <------------------    Sender 3 (NdpBasicClientApp)
        //       ---------------------
        //      goodput = ave(goodputs: sink1,sink2,sink3)

        ////////////////////////////  WAY-I  /////////////////////////////////////
        std::cout << " dest: " << dest << "\n";
        cModule* destModule = getModuleByPath(dest.c_str());
        cModule* ndpDestModule = destModule->getSubmodule("ndp");
        unsigned int newNdpGateOutSizeDest = ndpDestModule->gateSize("appOut") + 1;
        unsigned int newNdpGateInSizeDest = ndpDestModule->gateSize("appIn") + 1;
        ndpDestModule->setGateSize("appOut", newNdpGateOutSizeDest);
        ndpDestModule->setGateSize("appIn", newNdpGateInSizeDest);
        unsigned int newNumNdpSinkAppsDest = findNumSumbodules(destModule, "inet.ndp.application.ndpapp.NdpSinkApp") + 1;
        std::cout << "Dest  NumNDPSinkApp   =  " << newNumNdpSinkAppsDest << "\n";
        cModuleType *moduleTypeDest = cModuleType::get("inet.ndp.application.ndpapp.NdpSinkApp"); // find factory object
        std::string nameNdpAppDest = "ndpApp[" + std::to_string(newNumNdpSinkAppsDest - 1) + "]";
        cModule *newDestAppModule = moduleTypeDest->create(nameNdpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumNdpSinkAppsDest);

        newDestAppModule->par("isLongFlow").setBoolValue(false);
        newDestAppModule->par("multiSrcGroupId").setDoubleValue(multiSrcGroupId); // added new

        cGate *gateNdpInDest = ndpDestModule->gate("appIn", newNdpGateOutSizeDest - 1);
        cGate *gateNdpOutDest = ndpDestModule->gate("appOut", newNdpGateOutSizeDest - 1);
        cGate *gateInDest = newDestAppModule->gate("ndpIn");
        cGate *gateOutDest = newDestAppModule->gate("ndpOut");

        gateNdpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateNdpInDest);
        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();
        ////////////////////////////  WAY-I  /////////////////////////////////////

        // get the src ndp module
        std::string itsSender = *iter;
        cModule* srcModule = getModuleByPath(itsSender.c_str()); // const char* c_str Return pointer to the string.
        cModule* ndpSrcModule = srcModule->getSubmodule("ndp");
        unsigned int newNDPGateOutSizeSrc = ndpSrcModule->gateSize("appOut") + 1;
        unsigned int newNDPGateInSizeSrc = ndpSrcModule->gateSize("appIn") + 1;
        ndpSrcModule->setGateSize("appOut", newNDPGateOutSizeSrc);
        ndpSrcModule->setGateSize("appIn", newNDPGateInSizeSrc);
        unsigned int newNumNdpSessionAppsSrc = findNumSumbodules(srcModule, "inet.ndp.application.ndpapp.NdpBasicClientApp") + 1;
        std::cout << "Src  numTCPSessionApp =  " << newNumNdpSessionAppsSrc << "\n";
        cModuleType *moduleTypeSrc = cModuleType::get("inet.ndp.application.ndpapp.NdpBasicClientApp"); // find factory object
        std::string nameNdpAppSrc = "ndpApp[" + std::to_string(newNumNdpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameNdpAppSrc.c_str(), srcModule);

        newSrcAppModule->par("connectAddress").setStringValue(dest);
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumNdpSinkAppsDest);  //??? to be checked

        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);


        /// >>>>>>>>>>>>
        if (isWebSearchWorkLoad == false){
//               flowSize = flowSize/3; ??????????????????
            newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //
            // aha .....
            unsigned int priority = getPriorityValue(flowSize);
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }

        if (isWebSearchWorkLoad == true){
            unsigned int newFlowSize = getNewFlowSizeFromWebSearchWorkLoad();
            newSrcAppModule->par("numPacketsToSend").setDoubleValue(newFlowSize); //

            unsigned int priority = getPriorityValue(newFlowSize);
            newSrcAppModule->par("priorityValue").setDoubleValue(priority); //RaptorQBasicClientApp
        }
        /// >>>>>>>>>>>>
//        newSrcAppModule->par("numPacketsToSend").setDoubleValue(flowSize); //


        cGate *gateNdpIn = ndpSrcModule->gate("appIn", newNDPGateInSizeSrc - 1);
        cGate *gateNdpOut = ndpSrcModule->gate("appOut", newNDPGateOutSizeSrc - 1);
        cGate *gateIn = newSrcAppModule->gate("ndpIn");
        cGate *gateOut = newSrcAppModule->gate("ndpOut");
        gateNdpOut->connectTo(gateIn);
        gateOut->connectTo(gateNdpIn);
        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();
        newSrcAppModule->par("startTime").setDoubleValue(simTime().dbl() + sumArrivalTimes);

        newArrivalTime = expDistribution.operator()(PRNG);
        sumArrivalTimes = sumArrivalTimes + newArrivalTime;
    }
}







} //namespace inet


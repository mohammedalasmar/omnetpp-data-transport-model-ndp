#include "CentralScheduler.h"
//#include "/Volumes/LocalDataHD/m/ma/ma777/Desktop/omnetpp-5.2/src/envir/stopwatch.h"

using namespace std;
using namespace std::chrono;

namespace inet {

Define_Module(CentralScheduler);

CentralScheduler::~CentralScheduler()
{
    cancelAndDelete(startManagerNode);
    cancelAndDelete(stopSimulation);

}

void CentralScheduler::initialize(int stage)
{

    // Record start time
    t1 = high_resolution_clock::now();

//    omnetpp::envir::Stopwatch stopwatch;
//    stopwatch.setRealTimeLimit(5);

    numCompletedShortFlows = par("numCompletedShortFlows");
    
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
    flowSize = par("flowSize");
    numShortFlows = par("numShortFlows");
    longFlowSize = par("longFlowSize");
    numServers = std::pow(kValue, 3) / 4;
    shuffle = par("shuffle");
    percentLongFlowNodes = par("percentLongFlowNodes");

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

void CentralScheduler::handleMessage(cMessage *msg)
{


    if (msg == stopSimulation) {
        std::cout << " All shortFlows COMPLETED  " << std::endl;
        totalSimTime=simTime();
//       cancelAndDelete   stopSimulation = nullptr;
//       cancelAndDelete(stopSimulation);
        endSimulation();
    }

    std::random_device rd; // uniformly-distributed integer random number generator
    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation
    std::cout << "\n\n\n ";
    std::cout << "******************** CentralScheduler::handleMessage .. ********************  \n";

    //  % of short flows and % of long flows
//    numlongflowsRunningServers = floor(numServers * 0.33); // 33% of nodes run long flows
    numlongflowsRunningServers = floor(numServers * percentLongFlowNodes); // 33% of nodes run long flows , TODO throw error as it shouldn't be 1
    numshortflowRunningServers = numServers - numlongflowsRunningServers;
    std::cout << "numshortflowRunningServers:  " << numshortflowRunningServers << std::endl;
    std::cout << "numlongflowsRunningServers:  " << numlongflowsRunningServers << std::endl;


    generateTM();

    serversLocations();
    srand(time(NULL));
    std::string itsSrc;
    std::string newDest;

    deleteAllSubModuleApp("tcpApp[0]");
    scheduleLongFlows();
//
    for (unsigned int i = 1; i <= numShortFlows; i++) {
        std::cout << "\n\n\n Shortflow ID: " << i << std::endl;

        if (strcmp(trafficMatrixType, "randTM") == 0) getNewDestRandTM(itsSrc, newDest);
        if (strcmp(trafficMatrixType, "permTM") == 0) getNewDestPremTM(itsSrc, newDest);
        // identifying the servers locations: FatTree.Pod[].racks[].servers[]
        scheduleNewShortFlow(itsSrc, newDest);
    }

    std::cout << "\n\n\n";
}

void CentralScheduler::serversLocations()
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
void CentralScheduler::getNewDestRandTM(std::string& itsSrc, std::string& newDest) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination RandTM .. ********************  \n";
//    int newDestination = test;
    unsigned int newDestination = 0;
    unsigned int srcNewDestination = 0;
    while (newDestination == srcNewDestination) {
         newDestination = permServers.at( numlongflowsRunningServers+ (std::rand() % (numshortflowRunningServers)));
       //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
         srcNewDestination = permServers.at( numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    }
    std::cout << "@@@ newDestination " << newDestination << " , its src   "<< srcNewDestination << "\n";

    CentralScheduler::findLocation(newDestination, newDest);
    CentralScheduler::findLocation(srcNewDestination, itsSrc);
    
    
    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    

    
    // can be replaced by recordMatList ( see Finish())
    randMapShortFlowsVec.record(srcNewDestination);
    randMapShortFlowsVec.record(newDestination);
}


// permutation TM
void CentralScheduler::generateTM()
{
    std::random_device rd; // uniformly-distributed integer random number generator-- seed
    std::mt19937 rng(rd());
    std::cout << "\n\n ******************** generate TM maps.. ********************  \n";
    for (int i = 0; i < numServers; ++i)
        permServers.push_back(i);
     if (shuffle)
       std::shuffle(permServers.begin(), permServers.end(), rng); ///////////// TODO ooooooooooooooooooo

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

void CentralScheduler::getNewDestPremTM(std::string& itsSrc, std::string& newDest)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination PremTM .. ********************  \n";
//    int newDestination = test;
    int newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    int srcNewDestination = permMapShortFlows.find(newDestination)->second;
    std::cout << "@@@ newDestination " << newDestination << " , its src   " << srcNewDestination << "\n";

    CentralScheduler::findLocation(newDestination, newDest);
    CentralScheduler::findLocation(srcNewDestination, itsSrc);

//    std::cout << " newDest " << newDest << "\n";
//    std::cout << " itsSrc " << itsSrc << "\n";

    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    
    permMapShortFlowsVector.record(srcNewDestination);
    permMapShortFlowsVector.record(newDestination);
}

void CentralScheduler::findLocation(unsigned int nodeIndex, std::string& nodePodRackLoc)
{
    std::list<NodeLocation>::iterator itt;
    itt = nodeLocationList.begin();
    while (itt != nodeLocationList.end()) {
        if (itt->index == nodeIndex) {
            nodePodRackLoc = "FatTree.Pod[" + std::to_string(itt->pod) + "].racks[" + std::to_string(itt->rack) + "].servers[" + std::to_string(itt->node) + "]";
        }
        itt++;
    }
}

void CentralScheduler::scheduleLongFlows()
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

        
        CentralScheduler::findLocation(iter->first, dest); // get dest value
        CentralScheduler::findLocation(iter->second, source);

        cout << "  nodePodRackLoc:  " << iter->second << " == " << source << " ==> " << iter->first << " == " << dest << "\n";

        cModule* srcModule = getModuleByPath(source.c_str());
        cModule* destModule = getModuleByPath(dest.c_str());

//        std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;

        // get the src tcp module
        cModule* tcpSrcModule = srcModule->getSubmodule("tcp");
        cModule* tcpDestModule = destModule->getSubmodule("tcp");

        int newTCPGateOutSizeSrc = tcpSrcModule->gateSize("appOut") + 1;
        int newTCPGateInSizeSrc = tcpSrcModule->gateSize("appIn") + 1;
        int newTCPGateOutSizeDest = tcpDestModule->gateSize("appOut") + 1;
        int newTCPGateInSizeDest = tcpDestModule->gateSize("appIn") + 1;

        tcpSrcModule->setGateSize("appOut", newTCPGateOutSizeSrc);
        tcpSrcModule->setGateSize("appIn", newTCPGateInSizeSrc);
        tcpDestModule->setGateSize("appOut", newTCPGateOutSizeDest);
        tcpDestModule->setGateSize("appIn", newTCPGateInSizeDest);

//        std::cout << "aaaaaaaaa tcpSrcModule->gateSize(appOut) =  " << tcpSrcModule->gateSize("appOut") << std::endl;
//        std::cout << "aaaaaaaaa tcpSrcModule->gateSize(appIn)  =  " << tcpSrcModule->gateSize("appIn") << std::endl;

        int newNumTcpSessionAppsSrc = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") + 1;
        int newNumTcpSinkAppsDest = findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") + 1;

//        std::cout << "wwwwww 1111111  =  " << findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") << std::endl;
//        std::cout << "wwwwww 22222222 =  " << findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") << std::endl;

        std::cout << "Src  numTCPSessionApp =  " << newNumTcpSessionAppsSrc << "\n";
        std::cout << "Dest  NumTCPSinkApp   =  " << newNumTcpSinkAppsDest << "\n";

        // find factory object
        cModuleType *moduleTypeSrc = cModuleType::get("inet.applications.tcpapp.TCPSessionApp");
        cModuleType *moduleTypeDest = cModuleType::get("inet.applications.tcpapp.TCPSinkApp");

        std::string nameTcpAppSrc = "tcpApp[" + std::to_string(newNumTcpSessionAppsSrc - 1) + "]";
        std::string nameTcpAppDest = "tcpApp[" + std::to_string(newNumTcpSinkAppsDest - 1) + "]";






        // DESTttttttt  TCPSinkApp
        // create (possibly compound) module and build its submodules (if any)
        cModule *newDestAppModule = moduleTypeDest->create(nameTcpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumTcpSessionAppsSrc);
        newDestAppModule->par("isLongFlow").setBoolValue(true);
        //   --------<tcpIn         appOut[]<----------
        //     tcpApp                          tcp
        //   -------->tcpOut        appIn[] >----------
        cGate *gateTcpInDest = tcpDestModule->gate("appIn", newTCPGateOutSizeDest - 1);
        cGate *gateTcpOutDest = tcpDestModule->gate("appOut", newTCPGateOutSizeDest - 1);

        cGate *gateInDest = newDestAppModule->gate("tcpIn");
        cGate *gateOutDest = newDestAppModule->gate("tcpOut");

        gateTcpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateTcpInDest);

        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();

        newDestAppModule->par("localPort").setDoubleValue(80 + newNumTcpSessionAppsSrc);

        // SOURCeeeeee  TCPSessionApp

        //  Can we change the numTcpApps in the standardHost compund module ? ( ans: no, To be confimed)
//        int currentNumTcpApp = srcModule->par("numTcpApps").doubleValue();
//        srcModule->par("numTcpApps").setDoubleValue(3);
        cModule *newSrcAppModule = moduleTypeSrc->create(nameTcpAppSrc.c_str(), srcModule);

        newSrcAppModule->par("connectAddress").setStringValue(dest.c_str());
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumTcpSessionAppsSrc);
        newSrcAppModule->par("sendBytes").setDoubleValue(longFlowSize);
        newSrcAppModule->par("tOpen").setDoubleValue(simTime().dbl());
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl());

        //   --------<tcpIn         appOut[]<----------
        //     tcpApp                          tcp
        //   -------->tcpOut        appIn[] >----------
        cGate *gateTcpIn = tcpSrcModule->gate("appIn", newTCPGateInSizeSrc - 1);
        cGate *gateTcpOut = tcpSrcModule->gate("appOut", newTCPGateOutSizeSrc - 1);

        cGate *gateIn = newSrcAppModule->gate("tcpIn");
        cGate *gateOut = newSrcAppModule->gate("tcpOut");

        gateTcpOut->connectTo(gateIn);
        gateOut->connectTo(gateTcpIn);

        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();

//        std::cout << "wwwwww 22222222  =  " << findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") << std::endl;

        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl());
//        std::cout << "mohModule->gateCount(); " << newSrcAppModule->gateCount() << std::endl;

//        std::cout << "gateTcpIn  " << gateTcpIn->getBaseName() << "  " << gateTcpIn->getIndex() << std::endl;
//        std::cout << "gateTcpOut  " << gateTcpOut->getBaseName() << " " << gateTcpIn->getIndex() << std::endl;
//        std::cout << "gateIn  " << gateIn->getBaseName() << std::endl;
//        std::cout << "gateOut  " << gateOut->getBaseName() << std::endl;

    }
}

void CentralScheduler::scheduleNewShortFlow(std::string itsSrc, std::string newDest)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewShortFlow .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";

    std::cout << " newDest " << newDest << "\n";
    std::cout << " itsSrc " << itsSrc << "\n";

    std::random_device rd; // uniformly-distributed integer random number generator-- seed
    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation

    //  arrivalRate = 2560; //lamda
    //  double averageArrivalTime = 1/arrivalRate;
    std::exponential_distribution<double> exp(arrivalRate);

    newArrivalTime = exp.operator()(rng);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;
//    appModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);

    cModule* srcModule = getModuleByPath(itsSrc.c_str());  // const char* c_str Return pointer to the string.
    cModule* destModule = getModuleByPath(newDest.c_str());

//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;

    // get the src tcp module
    cModule* tcpSrcModule = srcModule->getSubmodule("tcp");
    cModule* tcpDestModule = destModule->getSubmodule("tcp");

    unsigned int newTCPGateOutSizeSrc = tcpSrcModule->gateSize("appOut") + 1;
    unsigned int newTCPGateInSizeSrc = tcpSrcModule->gateSize("appIn") + 1;
    unsigned int newTCPGateOutSizeDest = tcpDestModule->gateSize("appOut") + 1;
    unsigned int newTCPGateInSizeDest = tcpDestModule->gateSize("appIn") + 1;

    tcpSrcModule->setGateSize("appOut", newTCPGateOutSizeSrc);
    tcpSrcModule->setGateSize("appIn", newTCPGateInSizeSrc);
    tcpDestModule->setGateSize("appOut", newTCPGateOutSizeDest);
    tcpDestModule->setGateSize("appIn", newTCPGateInSizeDest);

//    std::cout << "aaaaaaaaa tcpSrcModule->gateSize(appOut) =  " << tcpSrcModule->gateSize("appOut") << std::endl;
//    std::cout << "aaaaaaaaa tcpSrcModule->gateSize(appIn)  =  " << tcpSrcModule->gateSize("appIn") << std::endl;

    unsigned int newNumTcpSessionAppsSrc = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") + 1;
    unsigned int newNumTcpSinkAppsDest = findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") + 1;

//    std::cout << "wwwwww 1111111  =  " << findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") << std::endl;
//    std::cout << "wwwwww 22222222 =  " << findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") << std::endl;
    std::cout << "Src  numTCPSessionApp =  " << newNumTcpSessionAppsSrc << "\n";
    std::cout << "Dest  NumTCPSinkApp   =  " << newNumTcpSinkAppsDest << "\n";

    // find factory object
    cModuleType *moduleTypeSrc = cModuleType::get("inet.applications.tcpapp.TCPSessionApp");
    cModuleType *moduleTypeDest = cModuleType::get("inet.applications.tcpapp.TCPSinkApp");

    std::string nameTcpAppSrc = "tcpApp[" + std::to_string(newNumTcpSessionAppsSrc - 1) + "]";
    std::string nameTcpAppDest = "tcpApp[" + std::to_string(newNumTcpSinkAppsDest - 1) + "]";

    // DESTttttttt
    // create (possibly compound) module and build its submodules (if any)
    cModule *newDestAppModule = moduleTypeDest->create(nameTcpAppDest.c_str(), destModule);
    newDestAppModule->par("localPort").setDoubleValue(80 +newNumTcpSinkAppsDest);

    //   --------<tcpIn         appOut[]<----------
    //     tcpApp                          tcp
    //   -------->tcpOut        appIn[] >----------
    cGate *gateTcpInDest = tcpDestModule->gate("appIn", newTCPGateOutSizeDest - 1);
    cGate *gateTcpOutDest = tcpDestModule->gate("appOut", newTCPGateOutSizeDest - 1);

    cGate *gateInDest = newDestAppModule->gate("tcpIn");
    cGate *gateOutDest = newDestAppModule->gate("tcpOut");

    gateTcpOutDest->connectTo(gateInDest);
    gateOutDest->connectTo(gateTcpInDest);

    newDestAppModule->finalizeParameters();
    newDestAppModule->buildInside();
    newDestAppModule->scheduleStart(simTime());
    newDestAppModule->callInitialize();

//    newDestAppModule->par("localPort").setDoubleValue(80 + newNumTcpSessionAppsSrc+newNumTcpSinkAppsDest); //??? to be checked

    // SOURCeeeeee

    //  Can we change the numTcpApps in the standardHost compound module ? ( ans: no, To be confimed)
    //        int currentNumTcpApp = srcModule->par("numTcpApps").doubleValue();
    //        srcModule->par("numTcpApps").setDoubleValue(3);
    cModule *newSrcAppModule = moduleTypeSrc->create(nameTcpAppSrc.c_str(), srcModule);

    newSrcAppModule->par("connectAddress").setStringValue(newDest);
    newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumTcpSinkAppsDest);  //??? to be checked
    newSrcAppModule->par("sendBytes").setDoubleValue(flowSize);
    newSrcAppModule->par("tOpen").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);

    //   --------<tcpIn         appOut[]<----------
    //     tcpApp                          tcp
    //   -------->tcpOut        appIn[] >----------
    cGate *gateTcpIn = tcpSrcModule->gate("appIn", newTCPGateInSizeSrc - 1);
    cGate *gateTcpOut = tcpSrcModule->gate("appOut", newTCPGateOutSizeSrc - 1);

    cGate *gateIn = newSrcAppModule->gate("tcpIn");
    cGate *gateOut = newSrcAppModule->gate("tcpOut");

    gateTcpOut->connectTo(gateIn);
    gateOut->connectTo(gateTcpIn);

    newSrcAppModule->finalizeParameters();
    newSrcAppModule->buildInside();
    newSrcAppModule->scheduleStart(simTime());
    newSrcAppModule->callInitialize();

    //        std::cout << "wwwwww 22222222  =  " << findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") << std::endl;

    newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl()+ sumArrivalTimes);

}

int CentralScheduler::findNumSumbodules(cModule* nodeModule, const char *subModuleType)
{
    unsigned int rep = 0;
    for (cModule::SubmoduleIterator iter(nodeModule); !iter.end(); iter++) {
        cModule *subModule = *iter;
        if (strcmp(subModule->getModuleType()->getFullName(), subModuleType) == 0) {
            rep++;
            //             std::cout << "subModule->getModuleType()->getFullName()  hhhh " << subModule->getModuleType()->getFullName() << std::endl;
        }
    }
    return rep;
}

void CentralScheduler::deleteAllSubModuleApp(const char *subModuleToBeRemoved)
{
    std::cout << "\n\n ******************** deleteAll temp SubModuleApp  .. ********************  \n";
    std::string node;

    for (int i = 0; i < numServers; i++) {

        CentralScheduler::findLocation(i, node);
        cModule* nodeModule = getModuleByPath(node.c_str());
        // delete tcpApp[0]

        cModule* tempTcpAppModule = nullptr;
        for (cModule::SubmoduleIterator iter(nodeModule); !iter.end(); iter++) {
            cModule *subModule = *iter;
            if (strcmp(subModule->getFullName(), subModuleToBeRemoved) == 0) {
                tempTcpAppModule = subModule;
//                std::cout << "tempTcpAppModule  " << tempTcpAppModule->getFullPath() << std::endl;
            }
        }
        tempTcpAppModule->deleteModule();

        cModule* tcpSrcModule = nodeModule->getSubmodule("tcp");
        tcpSrcModule->setGateSize("appOut", 0);
        tcpSrcModule->setGateSize("appIn", 0);

    }
    std::cout << " Done.. \n";

}

// permutation Traffic Matrix
void CentralScheduler::permTM(const char *longOrShortFlows)
{

//    std::random_device rd; // uniformly-distributed integer random number generator-- seed
//    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation
//
//    //  arrivalRate = 2560; //lamda
//    //  double averageArrivalTime = 1/arrivalRate;
//    std::exponential_distribution<double> exp(arrivalRate);
//
//    int selectTxNode = 0;
//    int selectRxNode = 0;
//    int startIndex = 0;
//    int lastIndex = 0;
//    int next = 0;
//    int firstLongflowsNodeIndex = 0;
//    int lastLongflowsNodeIndex = numlongflowsRunningServers - 1;
//    int firstShortflowsNodeIndex = numlongflowsRunningServers;
//    int lastShortflowsNodeIndex = numlongflowsRunningServers + numshortflowRunningServers - 1;
//
//    if (strcmp(longOrShortFlows, "longFlows") == 0) {
//        selectTxNode = firstLongflowsNodeIndex - 1;
//        selectRxNode = firstLongflowsNodeIndex;
//        startIndex = firstLongflowsNodeIndex;
//        lastIndex = lastLongflowsNodeIndex;
//    }
//    else if (strcmp(longOrShortFlows, "shortFlows") == 0) {
//        selectTxNode = firstShortflowsNodeIndex - 1;
//        selectRxNode = firstShortflowsNodeIndex;
//        startIndex = firstShortflowsNodeIndex;
//        lastIndex = lastShortflowsNodeIndex;
//    }
//
//    std::cout << "startIndex  startIndex  startIndex  startIndex  " << startIndex << std::endl;
//    std::cout << "lastIndex  lastIndex  lastIndex  lastIndex  " << lastIndex << std::endl;
//
//    for (int i = startIndex; i <= lastIndex; i++) {
//        selectTxNode++;
//        selectRxNode++;
//        next = i + 1;
//
//        if (i == lastIndex) {
//            selectTxNode = i;
//            selectRxNode = startIndex;
//            next = startIndex;
//        }
//
//        std::string conn = "host " + std::to_string(permServers.at(selectTxNode)) + " ==> " + "host " + std::to_string(permServers.at(selectRxNode));
//        std::cout << "conn:  " << conn << std::endl;
//
//        std::string src = "FatTree.Pod[" + std::to_string(podLocationForEachServer.at(i)) + "].racks[" + std::to_string(rackLocationForEachServer.at(i)) + "].servers["
//                + std::to_string(LocationForEachServerInTheRack.at(i)) + "]";
//
//        std::string dest = "FatTree.Pod[" + std::to_string(podLocationForEachServer.at(next)) + "].racks[" + std::to_string(rackLocationForEachServer.at(next)) + "].servers["
//                + std::to_string(LocationForEachServerInTheRack.at(next)) + "]";
//
//        //    FatTree.Pod[].racks[].servers[]
//        cModule* srcModule = getModuleByPath(src.c_str());
//        cModule* destModule = getModuleByPath(dest.c_str());
//
////        std::cout << "src:        " << src << std::endl;
//        std::cout << "srcModule:  " << srcModule->getFullPath() << std::endl << std::endl;
//
////        std::cout << "dest:        " << dest << std::endl;
//        std::cout << "destModule:  " << destModule->getFullPath() << std::endl;
//
//        cModule* appModule = nullptr;
//        for (cModule::SubmoduleIterator iter(srcModule); !iter.end(); iter++) {
//            cModule *subModule = *iter;
//            if (strcmp(subModule->getFullName(), "tcpApp[1]") == 0) {
//                //   std::cout << "get the modulde " << subModule->getFullPath() << std::endl;
//                appModule = subModule;
//                break;
//            }
//        }
//
//        //moh note: whenever a parameter changes, the TCPSessionApp::handleParameterChange  is called
//        //if we change three parameters, then handleParameterChange will be called three times
//        //so we need to add an if condition in this method to take actions whenever all the parameters are changed not just one
//        appModule->par("connectAddress").setStringValue(dest);
//
//        if (strcmp(longOrShortFlows, "longFlows") == 0) {
//            appModule->par("sendBytes").setDoubleValue(1000); // lllllllllllllllllllllllllll
//            appModule->par("tSend").setDoubleValue(simTime().dbl());
//        }
//        else if (strcmp(longOrShortFlows, "shortFlows") == 0) {
//
//            permMap.insert(std::pair<int, int>(permServers.at(selectRxNode), permServers.at(selectTxNode)));  // < dest, src >
////            std::cout << "selectRxNode  " <<selectRxNode <<  "  selectTxNode  " << selectTxNode  << std::endl;
//
//            newArrivalTime = exp.operator()(rng);
//            sumArrivalTimes = sumArrivalTimes + newArrivalTime;
//            appModule->par("sendBytes").setDoubleValue(flowSize);
//            appModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
//        }
//
//        //            appModule->par("tClose").setDoubleValue(1000000000);
//        std::cout << "simTime().dbl()  " << simTime().dbl() << std::endl;
//        // std::cout << "tClose  " <<  appModule->par("tClose").doubleValue() << std::endl;
//        std::cout << "long flows: tSend  " << appModule->par("tSend").doubleValue() << std::endl;
//        std::cout << "************\n\n\n\n ";
//    }
}

void CentralScheduler::finish()
{

    for (std::vector<unsigned int>::iterator iter = permServers.begin(); iter != permServers.end(); ++iter) {

        cout << "  NODE= " << *iter << "  ";
        nodes.record(*iter);

        std::string source;
        CentralScheduler::findLocation(*iter, source); // get dest value
        //
//        cout << "  nodePodRackLoc:  " << iter->second << " == " << source << " ==> " << iter->first << " == " << dest << "\n";
//
        cModule* srcModule = getModuleByPath(source.c_str());

        int finalNumTcpSessionApps = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp");
        int finalNumTcpSinkApps = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSinkApp");

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
    if (strcmp(trafficMatrixType, "permTM") == 0)  recordScalar("permTM", 0);
    if (strcmp(trafficMatrixType, "randTM") == 0)  recordScalar("randTM", 1);
    recordScalar("wallClockTime=", duration);



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

void CentralScheduler::handleParameterChange(const char *parname)
{
    if (parname && strcmp(parname, "numCompletedShortFlows") == 0) {
//        numCompletedShortFlows = par("numCompletedShortFlows");
        ++numCompletedShortFlows;
        std::cout << " num completed shortflows = " << numCompletedShortFlows << std::endl;

        if (numCompletedShortFlows == numShortFlows) {
//            getSimulation()->callFinish();
            scheduleAt(simTime(), stopSimulation);
        }
    }
}

} //namespace inet

//    int matrix[4][numServers];
//    for (int n = 0; n < 4; n++) {
//        for (int m = 0; m < numServers; m++) {
//            if (n == 0)
//                matrix[n][m] = permServers.at(m);
//            if (n == 1)
//                matrix[n][m] = podLocationForEachServer.at(m);
//            if (n == 2)
//                matrix[n][m] = rackLocationForEachServer.at(m);
//            if (n == 3)
//                matrix[n][m] = LocationForEachServerInTheRack.at(m);
//        }
//    }
//    //    Matrix= [permutationServers ;  podLocationForEachServer ; rackLocationForEachServer; LocationForEachServerInTheRack];

//        cModule* tcpSrcModule = nullptr;
//        for (cModule::SubmoduleIterator iter(srcModule); !iter.end(); iter++) {
//            cModule *subModule = *iter;
//            if (strcmp(subModule->getFullName(), "tcp") == 0) {
//                std::cout << "get the modulde 'tcp'  " << subModule->getFullPath() << std::endl;
//                tcpSrcModule = subModule;
//                break;
//            }
//        }

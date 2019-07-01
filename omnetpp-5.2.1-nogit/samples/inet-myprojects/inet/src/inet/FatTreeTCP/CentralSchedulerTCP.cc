// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

#include "CentralSchedulerTCP.h"
//#include "/Volumes/LocalDataHD/m/ma/ma777/Desktop/omnetpp-5.2/src/envir/stopwatch.h"

using namespace std;
using namespace std::chrono;

namespace inet {

Define_Module(CentralSchedulerTCP);

CentralSchedulerTCP::~CentralSchedulerTCP()
{
    cancelAndDelete(startManagerNode);
    cancelAndDelete(stopSimulation);

}

void CentralSchedulerTCP::initialize(int stage)
{
    srand(time(NULL)); // random seeds
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


    numIncastSenders = par("numIncastSenders");

    oneToOne = par("oneToOne");

    numReplicas = par("numReplicas");
    multiUnicasting = par("multiUnicasting");
    numMulticastSessions = par("numMulticastSessions");

    multiUniSourcing = par("multiUniSourcing");
    numMultisourceSessions = par("numMultisourceSessions");


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

void CentralSchedulerTCP::handleMessage(cMessage *msg)
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
//    srand(time(NULL));
    std::string itsSrc;
    std::string newDest;

    deleteAllSubModuleApp("tcpApp[0]");

//  int senders = 1;
//   scheduleIncast(numIncastSenders);


    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    //     std::cout << "\n\n ******************** schedule Incast  .. ********************  \n";
    //    scheduleIncast(numIncastSenders);

    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//        std::cout << "\n\n ******************** schedule Long flows .. ********************  \n";
//        scheduleLongFlows();


    std::cout << "\n\n ******************** start .. ********************  \n";
    std::cout << "oneToOne " << oneToOne <<"  \n";


   // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   if (multiUnicasting  == true && multiUniSourcing == false && oneToOne == false) {
        std::cout << "\n\n @@@@@@@@@@ uni-multicasting ..@@@@@@@@@@@  \n";
        for (unsigned int i = 1; i <= numMulticastSessions ; i++) {
             std::cout << "\n\n\n multicast Group ID: " << i << std::endl;
             std::vector<std::string> replicasNodes;
             getNewThreeDestRandTMForMultiUnicasting(itsSrc, replicasNodes); // tcp multicasting (3 replicas) based on multi Unicasting
             scheduleNewMultiCastSession(itsSrc , replicasNodes , i);
        }
    }


   if  (multiUnicasting  == false && multiUniSourcing == true && oneToOne == false) {
        std::cout << "\n\n @@@@@@@@@@ uni-multiSourcing ..@@@@@@@@@@@  \n";
        for (unsigned int i = 1; i <= numMultisourceSessions ; i++) {
            std::cout << "\n\n\n multi-sourcing Group ID: " << i << std::endl;
            std::vector<std::string> senders;
            getNewThreeSrcRandTMForMultiSourcing(newDest , senders); // tcp multisourcing (3 replicas) based on multi Unicasting
            scheduleNewMultiSourcingSession(newDest , senders , i);
        }
    }

   int sourceOutcast = 2;
   if (multiUnicasting  == false && multiUniSourcing == false && oneToOne == true) {
        std::cout << "\n\n @@@@@@@@@@ one-to-one ..@@@@@@@@@@@ " <<  numShortFlows << "\n";
        for (unsigned int i = 1; i <= numShortFlows; i++) {
            std::cout << "\n\n\n Shortflow ID: " << i << std::endl;
            if (strcmp(trafficMatrixType, "randTM") == 0)  getNewDestRandTM(itsSrc, newDest);
            if (strcmp(trafficMatrixType, "permTM") == 0)  getNewDestPremTM(itsSrc, newDest);

            // use the following lines only for Outcast exp and comment the Rand and Perm above
//            if (sourceOutcast<=3){
//                        getNewOutcast(itsSrc, newDest, sourceOutcast , 1);
//             } else if (sourceOutcast>3){
//                        getNewOutcast(itsSrc, newDest, sourceOutcast , 0);
//             }
//            sourceOutcast++;


            scheduleNewShortFlow(itsSrc, newDest);
        }
    }
    std::cout << "\n\n\n";
}


void CentralSchedulerTCP::getNewOutcast(std::string& itsSrc, std::string& newDest, unsigned int newSrc, unsigned int destNode)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination PremTM .. ********************  \n";

    int newDestination =  destNode;
    int srcNewDestination = newSrc;
    std::cout << "@@@ newDestination " << newDestination << " , its src   " << srcNewDestination << "\n";

    CentralSchedulerTCP::findLocation(newDestination, newDest);
    CentralSchedulerTCP::findLocation(srcNewDestination, itsSrc);

//    std::cout << " newDest " << newDest << "\n";
//    std::cout << " itsSrc " << itsSrc << "\n";

    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);

    permMapShortFlowsVector.record(srcNewDestination);
    permMapShortFlowsVector.record(newDestination);
}

void CentralSchedulerTCP::serversLocations()
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
void CentralSchedulerTCP::getNewDestRandTM(std::string& itsSrc, std::string& newDest) {
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

    CentralSchedulerTCP::findLocation(newDestination, newDest);
    CentralSchedulerTCP::findLocation(srcNewDestination, itsSrc);
    
    
    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    

    
    // can be replaced by recordMatList ( see Finish())
    randMapShortFlowsVec.record(srcNewDestination);
    randMapShortFlowsVec.record(newDestination);
}




// permutation TM
void CentralSchedulerTCP::generateTM()
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

void CentralSchedulerTCP::getNewDestPremTM(std::string& itsSrc, std::string& newDest)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewDestination PremTM .. ********************  \n";
//    int newDestination = test;
    int newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    int srcNewDestination = permMapShortFlows.find(newDestination)->second;
    std::cout << "@@@ newDestination " << newDestination << " , its src   " << srcNewDestination << "\n";

    CentralSchedulerTCP::findLocation(newDestination, newDest);
    CentralSchedulerTCP::findLocation(srcNewDestination, itsSrc);

//    std::cout << " newDest " << newDest << "\n";
//    std::cout << " itsSrc " << itsSrc << "\n";

    RecordMat recordMat;
    recordMat.recordSrc = srcNewDestination;
    recordMat.recordDest = newDestination;
    recordMatList.push_back(recordMat);
    
    permMapShortFlowsVector.record(srcNewDestination);
    permMapShortFlowsVector.record(newDestination);
}

void CentralSchedulerTCP::findLocation(unsigned int nodeIndex, std::string& nodePodRackLoc)
{
    std::list<NodeLocation>::iterator itt;
    itt = nodeLocationList.begin();
    while (itt != nodeLocationList.end()) {
        if (itt->index == nodeIndex) {
            nodePodRackLoc = "FatTreeTopology.Pod[" + std::to_string(itt->pod) + "].racks[" + std::to_string(itt->rack) + "].servers[" + std::to_string(itt->node) + "]";
        }
        itt++;
    }
}

void CentralSchedulerTCP::scheduleLongFlows()
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

        
        CentralSchedulerTCP::findLocation(iter->first, dest); // get dest value
        CentralSchedulerTCP::findLocation(iter->second, source);

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

void CentralSchedulerTCP::scheduleNewShortFlow(std::string itsSrc, std::string newDest)
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


    // DESTttttttt TCPSinkApp
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



void CentralSchedulerTCP::scheduleIncast(unsigned int senders)
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewShortFlow .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::random_device rd; // uniformly-distributed integer random number generator-- seed
    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation

    std::string itsSrc;
    std::string newDest;
    unsigned int newDestination = 0;
    CentralSchedulerTCP::findLocation(newDestination, newDest);



    for (int i = 0; i < senders; ++i) {




        cModule* destModule = getModuleByPath(newDest.c_str());
        cModule* tcpDestModule = destModule->getSubmodule("tcp");
        unsigned int newTCPGateOutSizeDest = tcpDestModule->gateSize("appOut") + 1;
        unsigned int newTCPGateInSizeDest = tcpDestModule->gateSize("appIn") + 1;
        tcpDestModule->setGateSize("appOut", newTCPGateOutSizeDest);
        tcpDestModule->setGateSize("appIn", newTCPGateInSizeDest);
        unsigned int newNumTcpSinkAppsDest = findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") + 1;
        cModuleType *moduleTypeDest = cModuleType::get("inet.applications.tcpapp.TCPSinkApp");
        std::string nameTcpAppDest = "tcpApp[" + std::to_string(newNumTcpSinkAppsDest - 1) + "]";
        cModule *newDestAppModule = moduleTypeDest->create(nameTcpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue(80 + newNumTcpSinkAppsDest);
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



        unsigned int srcNewDestination = 0;
        while (newDestination == srcNewDestination) {
            srcNewDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
        }

        CentralSchedulerTCP::findLocation(srcNewDestination, itsSrc);

        sumArrivalTimes = 0;

        cModule* srcModule = getModuleByPath(itsSrc.c_str());  // const char* c_str Return pointer to the string.
        cModule* tcpSrcModule = srcModule->getSubmodule("tcp");
        unsigned int newTCPGateOutSizeSrc = tcpSrcModule->gateSize("appOut") + 1;
        unsigned int newTCPGateInSizeSrc = tcpSrcModule->gateSize("appIn") + 1;
        tcpSrcModule->setGateSize("appOut", newTCPGateOutSizeSrc);
        tcpSrcModule->setGateSize("appIn", newTCPGateInSizeSrc);
        unsigned int newNumTcpSessionAppsSrc = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") + 1;
        cModuleType *moduleTypeSrc = cModuleType::get("inet.applications.tcpapp.TCPSessionApp");
        std::string nameTcpAppSrc = "tcpApp[" + std::to_string(newNumTcpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameTcpAppSrc.c_str(), srcModule);
        newSrcAppModule->par("connectAddress").setStringValue(newDest);
        newSrcAppModule->par("connectPort").setDoubleValue(80 + newNumTcpSinkAppsDest);  //??? to be checked
        newSrcAppModule->par("sendBytes").setDoubleValue(flowSize);
        newSrcAppModule->par("tOpen").setDoubleValue(simTime().dbl() + sumArrivalTimes);
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
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
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    }

}




int CentralSchedulerTCP::findNumSumbodules(cModule* nodeModule, const char *subModuleType)
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

void CentralSchedulerTCP::deleteAllSubModuleApp(const char *subModuleToBeRemoved)
{
    std::cout << "\n\n ******************** deleteAll temp SubModuleApp  .. ********************  \n";
    std::string node;

    for (int i = 0; i < numServers; i++) {
        CentralSchedulerTCP::findLocation(i, node);
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


// multicasting
// ===================================== ONE SESSION ============================================
//            Sender                                                                          ===
//       --------------------------------                           -------------------       ===
//       |      TCPSessionApp --> conn1 -|-------------------->    | Receiver 1 Sink  |       ===
//       |                               |                           ------------------       ===
//       |                               |                           ------------------       ===
//       |      TCPSessionApp --> conn2 -|-------------------->    | Receiver 2 Sink  |       ===
//       |                               |                           ------------------       ===
//       |                               |                           ------------------       ===
//       |      TCPSessionApp --> conn3 -|-------------------->    | Receiver 3 Sink  |       ===
//       --------------------------------                           -------------------       ===
//      goodput = ave(goodputs: sink1,sink2,sink3)                                            ===
// ==============================================================================================
void CentralSchedulerTCP::scheduleNewMultiCastSession(std::string  itsSrc, std::vector<std::string>  newDest , unsigned int multicastGrpId) // three replicas
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewMultiCastSession three replicas .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " itsSrc " << itsSrc << "\n";
    std::random_device rd; // uniformly-distributed integer random number generator-- seed
    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation
    std::exponential_distribution<double> exp(arrivalRate);
    newArrivalTime = exp.operator()(rng);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;

//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;
    for (auto iter = newDest.begin(); iter!= newDest.end() ; ++iter) {
        std::string  thisDest = *iter;
        std::cout << " newDest " << thisDest << "\n";
        cModule* destModule = getModuleByPath(thisDest.c_str());
        cModule* tcpDestModule = destModule->getSubmodule("tcp");
        unsigned int newTCPGateOutSizeDest = tcpDestModule->gateSize("appOut") + 1;
        unsigned int newTCPGateInSizeDest = tcpDestModule->gateSize("appIn")    + 1;
        tcpDestModule->setGateSize("appOut", newTCPGateOutSizeDest);
        tcpDestModule->setGateSize("appIn", newTCPGateInSizeDest);
        unsigned int newNumTcpSinkAppsDest = findNumSumbodules(destModule,  "inet.applications.tcpapp.TCPSinkApp") + 1;
        std::cout << "Dest  NumTCPSinkApp   =  " << newNumTcpSinkAppsDest  << "\n";
        cModuleType *moduleTypeDest = cModuleType::get( "inet.applications.tcpapp.TCPSinkApp"); // find factory object
        std::string nameTcpAppDest = "tcpApp[" + std::to_string(newNumTcpSinkAppsDest - 1) + "]";
        cModule *newDestAppModule = moduleTypeDest->create( nameTcpAppDest.c_str(), destModule);
        newDestAppModule->par("localPort").setDoubleValue( 80 + newNumTcpSinkAppsDest);
        newDestAppModule->par("multiCastGroupId").setDoubleValue(multicastGrpId); // new added
        newDestAppModule->par("isLongFlow").setBoolValue(false);


        cGate *gateTcpInDest = tcpDestModule->gate("appIn",  newTCPGateOutSizeDest - 1);
        cGate *gateTcpOutDest = tcpDestModule->gate("appOut", newTCPGateOutSizeDest - 1);
        cGate *gateInDest = newDestAppModule->gate("tcpIn");
        cGate *gateOutDest = newDestAppModule->gate("tcpOut");
        gateTcpOutDest->connectTo(gateInDest);
        gateOutDest->connectTo(gateTcpInDest);
        newDestAppModule->finalizeParameters();
        newDestAppModule->buildInside();
        newDestAppModule->scheduleStart(simTime());
        newDestAppModule->callInitialize();

        // get the src tcp module
        cModule* srcModule = getModuleByPath(itsSrc.c_str()); // const char* c_str Return pointer to the string.
        cModule* tcpSrcModule = srcModule->getSubmodule("tcp");
        unsigned int newTCPGateOutSizeSrc = tcpSrcModule->gateSize("appOut") + 1;
        unsigned int newTCPGateInSizeSrc = tcpSrcModule->gateSize("appIn") + 1;
        tcpSrcModule->setGateSize("appOut", newTCPGateOutSizeSrc);
        tcpSrcModule->setGateSize("appIn", newTCPGateInSizeSrc);
        unsigned int newNumTcpSessionAppsSrc = findNumSumbodules(srcModule,  "inet.applications.tcpapp.TCPSessionApp") + 1;
        std::cout << "Src  numTCPSessionApp =  " << newNumTcpSessionAppsSrc   << "\n";
        cModuleType *moduleTypeSrc = cModuleType::get(  "inet.applications.tcpapp.TCPSessionApp"); // find factory object
        std::string nameTcpAppSrc = "tcpApp["  + std::to_string(newNumTcpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameTcpAppSrc.c_str(),    srcModule);
        newSrcAppModule->par("connectAddress").setStringValue(thisDest);
        newSrcAppModule->par("connectPort").setDoubleValue(   80 + newNumTcpSinkAppsDest);  //??? to be checked
        newSrcAppModule->par("sendBytes").setDoubleValue(flowSize);
        newSrcAppModule->par("tOpen").setDoubleValue( simTime().dbl() + sumArrivalTimes);
        newSrcAppModule->par("tSend").setDoubleValue( simTime().dbl() + sumArrivalTimes);
        cGate *gateTcpIn = tcpSrcModule->gate("appIn", newTCPGateInSizeSrc - 1);
        cGate *gateTcpOut = tcpSrcModule->gate("appOut",   newTCPGateOutSizeSrc - 1);
        cGate *gateIn = newSrcAppModule->gate("tcpIn");
        cGate *gateOut = newSrcAppModule->gate("tcpOut");
        gateTcpOut->connectTo(gateIn);
        gateOut->connectTo(gateTcpIn);
        newSrcAppModule->finalizeParameters();
        newSrcAppModule->buildInside();
        newSrcAppModule->scheduleStart(simTime());
        newSrcAppModule->callInitialize();
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    }
}


// multi-sourcing (not used) ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ===================================== ONE SESSION ============================================
//          Receiver
//   --------        ------------
//   |      |        |   conn1  |   <------------------    Sender 1 (TCPSessionApp)
//   | SINK |  <---- |   conn2  |   <------------------    Sender 2 (TCPSessionApp)
//   |      |        |   conn3  |   <------------------    Sender 3 (TCPSessionApp)
//   --------        ------------
//      goodput = SINK ? but this gives high goodput as three connections serve the sink
// ==============================================================================================
// to use this way take  WAY-I block outside the for loop



//
// multi-sourcing (used) ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// ===================================== ONE SESSION ============================================
//            Receiver
//       --------------------
//       |  sink1 <-- conn1  |   <------------------    Sender 1 (TCPSessionApp)
//       |  sink2 <-- conn2  |   <------------------    Sender 2 (TCPSessionApp)
//       |  sink3 <-- conn3  |   <------------------    Sender 3 (TCPSessionApp)
//       ---------------------
//      goodput = ave(goodputs: sink1,sink2,sink3)
// ==============================================================================================


void CentralSchedulerTCP::scheduleNewMultiSourcingSession(std::string  dest, std::vector<std::string>  senders , int multiSrcGroupId) // three replicas
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@ scheduleNewMultiSourcingSession fetch three replicas  multi sourcing .. @@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << " dest nodes: " << dest << "\n";
    std::random_device rd; // uniformly-distributed integer random number generator-- seed
    std::mt19937 rng(rd()); // mt19937: Pseudo-random number generation
    std::exponential_distribution<double> exp(arrivalRate);
    newArrivalTime = exp.operator()(rng);
    sumArrivalTimes = sumArrivalTimes + newArrivalTime;

//    std::cout << "srcModule:  " << srcModule->getFullPath() << "  , destModule:  " << destModule->getFullPath() << std::endl << std::endl;







    for (auto iter = senders.begin(); iter != senders.end(); ++iter) {


        ////////////////////////////  WAY-I  /////////////////////////////////////
          std::cout << " dest: " << dest << "\n";
          cModule* destModule = getModuleByPath(dest.c_str());
          cModule* tcpDestModule = destModule->getSubmodule("tcp");
          unsigned int newTCPGateOutSizeDest = tcpDestModule->gateSize("appOut") + 1;
          unsigned int newTCPGateInSizeDest = tcpDestModule->gateSize("appIn") + 1;
          tcpDestModule->setGateSize("appOut", newTCPGateOutSizeDest);
          tcpDestModule->setGateSize("appIn", newTCPGateInSizeDest);
          unsigned int newNumTcpSinkAppsDest = findNumSumbodules(destModule, "inet.applications.tcpapp.TCPSinkApp") + 1;
          std::cout << "Dest  NumTCPSinkApp   =  " << newNumTcpSinkAppsDest << "\n";
          cModuleType *moduleTypeDest = cModuleType::get("inet.applications.tcpapp.TCPSinkApp"); // find factory object
          std::string nameTcpAppDest = "tcpApp[" + std::to_string(newNumTcpSinkAppsDest - 1) + "]";
          cModule *newDestAppModule = moduleTypeDest->create(nameTcpAppDest.c_str(), destModule);
          newDestAppModule->par("localPort").setDoubleValue(80 + newNumTcpSinkAppsDest);
          newDestAppModule->par("multiSrcGroupId").setDoubleValue(multiSrcGroupId); // added new
          newDestAppModule->par("isLongFlow").setBoolValue(false);


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
          ////////////////////////////  WAY-I  /////////////////////////////////////




        // get the src tcp module
        std::string itsSender = *iter;
        cModule* srcModule = getModuleByPath(itsSender.c_str()); // const char* c_str Return pointer to the string.
        cModule* tcpSrcModule = srcModule->getSubmodule("tcp");
        unsigned int newTCPGateOutSizeSrc = tcpSrcModule->gateSize("appOut") + 1;
        unsigned int newTCPGateInSizeSrc = tcpSrcModule->gateSize("appIn") + 1;
        tcpSrcModule->setGateSize("appOut", newTCPGateOutSizeSrc);
        tcpSrcModule->setGateSize("appIn", newTCPGateInSizeSrc);
        unsigned int newNumTcpSessionAppsSrc = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp") + 1;
        std::cout << "Src  numTCPSessionApp =  " << newNumTcpSessionAppsSrc << "\n";
        cModuleType *moduleTypeSrc = cModuleType::get("inet.applications.tcpapp.TCPSessionApp"); // find factory object
        std::string nameTcpAppSrc = "tcpApp[" + std::to_string(newNumTcpSessionAppsSrc - 1) + "]";
        cModule *newSrcAppModule = moduleTypeSrc->create(nameTcpAppSrc.c_str(),  srcModule);
        newSrcAppModule->par("connectAddress").setStringValue(dest);
        newSrcAppModule->par("connectPort").setDoubleValue( 80 + newNumTcpSinkAppsDest);  //??? to be checked
        newSrcAppModule->par("sendBytes").setDoubleValue(flowSize);
        newSrcAppModule->par("tOpen").setDoubleValue(simTime().dbl() + sumArrivalTimes);
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
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
        newSrcAppModule->par("tSend").setDoubleValue(simTime().dbl() + sumArrivalTimes);
    }
}

// random TM for multicasting (multicast 3 replicas)
void CentralSchedulerTCP::getNewThreeDestRandTMForMultiUnicasting(std::string& itsSrc, std::vector<std::string>& newDest) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNewThreeDestRandTMForMultiUnicasting    3 replicas multicast .. ********************  \n";
//    int newDestination = test;
    unsigned int newDestination = 0;
    unsigned int srcNewDestination = 0;
    unsigned int oldDest ;

    srcNewDestination = permServers.at( numlongflowsRunningServers  + (std::rand() % (numshortflowRunningServers)));
    newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
    std::string  selectedDest;
    for (int i = 0; i < numReplicas; ++i) {
        while (newDestination == srcNewDestination) {
            newDestination = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
            if (newDestination == oldDest ) newDestination=srcNewDestination; // to get unique destinations for this multicast group
            //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
//            std::cout << "wwwwwwww " << newDestination << " , multicast source node   " << srcNewDestination << "\n";

        }
        std::cout << "@@@ newDestination " << newDestination << " , multicast source node   " << srcNewDestination << "\n";
         oldDest = newDestination;

         // identifying the servers locations: FatTreeTopology.Pod[].racks[].servers[]
        CentralSchedulerTCP::findLocation(newDestination, selectedDest);
        newDest.push_back(selectedDest);
        newDestination=srcNewDestination;
    }
    CentralSchedulerTCP::findLocation(srcNewDestination, itsSrc);
}


//std::vector<std::string>& itsSrc,  std::string& newDest
// random TM for multiUnisourcing (fetch 3 replicas) multisourcing
void CentralSchedulerTCP::getNewThreeSrcRandTMForMultiSourcing(std::string& destNode, std::vector<std::string>& senders ) {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  \n";
    std::cout << "******************** getNew  Three  Src RandTM  For   MultiSourcing   fetch 3 replicas   .. ********************  \n";
    //    int newDestination = test;
        unsigned int src = 0;
        unsigned int destination = 0;
        unsigned int oldDest ;

        destination = permServers.at( numlongflowsRunningServers  + (std::rand() % (numshortflowRunningServers)));
        src = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
        std::string  selectedSrc;
        for (int i = 0; i < numReplicas; ++i) {
            while (src == destination) {
                src = permServers.at(numlongflowsRunningServers + (std::rand() % (numshortflowRunningServers)));
                if (src == oldDest ) src=destination; // to get unique destinations for this multicast group
                //    int srcNewDestination = permMapShortFlows.find(newDestination)->second; // this line is used wit premTM not randTM
    //            std::cout << "wwwwwwww " << newDestination << " , multicast source node   " << srcNewDestination << "\n";

            }
            std::cout << "@@@ MultiSourcing src " << src << " ,  dest   " <<destination << "\n";
             oldDest = src;

             // identifying the servers locations: FatTreeTopology.Pod[].racks[].servers[]
            CentralSchedulerTCP::findLocation(src, selectedSrc);
            senders.push_back(selectedSrc);
            src = destination;
        }
        CentralSchedulerTCP::findLocation(destination, destNode);
}




void CentralSchedulerTCP::finish()
{

    for (std::vector<unsigned int>::iterator iter = permServers.begin(); iter != permServers.end(); ++iter) {
        cout << "  NODE= " << *iter << "  ";
        nodes.record(*iter);

        std::string source;
        CentralSchedulerTCP::findLocation(*iter, source); // get dest value

//      cout << "  nodePodRackLoc:  " << iter->second << " == " << source << " ==> " << iter->first << " == " << dest << "\n";

        cModule* srcModule = getModuleByPath(source.c_str());

        int finalNumTcpSessionApps = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSessionApp");
        int finalNumTcpSinkApps = findNumSumbodules(srcModule, "inet.applications.tcpapp.TCPSinkApp");

        std::cout << "  finalNumTcpSessionApps:  " << finalNumTcpSessionApps << ",  finalNumTcpSinkApps: " << finalNumTcpSinkApps << "\n";
        numTcpSessionAppsVec.record(finalNumTcpSessionApps);
        numTcpSinkAppsVec.record(finalNumTcpSinkApps);
    }


    std::cout << "numshortflowRunningServers:  " << numshortflowRunningServers << std::endl;
    std::cout << "numlongflowsRunningServers:  " << numlongflowsRunningServers << std::endl;

    std::cout << "permLongFlowsServers:   ";
    for (std::vector<unsigned int>::iterator it = permLongFlowsServers.begin(); it != permLongFlowsServers.end(); ++it)
        std::cout << ' ' << *it <<'\n';

    // Record end time
    t2 = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(t2 - t1).count();
    std::cout << "=================================================== "  << std::endl;
    std::cout << " total Wall Clock Time (Real Time) = " << duration <<  " minutes" << std::endl;
    std::cout << " total Simulation Time      = " << totalSimTime <<  " sec" << std::endl;
    std::cout << "=================================================== "  << std::endl;
    std::cout << " num completed shortflows = " << numCompletedShortFlows << std::endl;

    std::cout << "FatTreeTopology.centralSchedulerTCP = " << this->getFullPath() << std::endl;

    recordScalar("simTimeTotal=", totalSimTime);
    recordScalar("numShortFlows=", numShortFlows);
    recordScalar("flowSize=", flowSize);
    recordScalar("percentLongFlowNodes=", percentLongFlowNodes);
    recordScalar("arrivalRate=", arrivalRate);
    if (strcmp(trafficMatrixType, "permTM") == 0)  recordScalar("permTM", 0);
    if (strcmp(trafficMatrixType, "randTM") == 0)  recordScalar("randTM", 1);
    recordScalar("wallClockTime=", duration);

    recordScalar("numReplicas=", numReplicas);
    recordScalar("numMulticastSessions=", numMulticastSessions);
    recordScalar("numMultisourceSessions=", numMultisourceSessions);

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

void CentralSchedulerTCP::handleParameterChange(const char *parname)
{
    if (parname && strcmp(parname, "numCompletedShortFlows") == 0) {
//        numCompletedShortFlows = par("numCompletedShortFlows");
        ++numCompletedShortFlows;
        std::cout << " num completed shortflows NOW = " << numCompletedShortFlows << std::endl;
        if (oneToOne == true && numCompletedShortFlows == numShortFlows && multiUnicasting == false && multiUniSourcing == false) {
            scheduleAt(simTime(), stopSimulation);
        }

        if (multiUnicasting == true && multiUniSourcing == false && oneToOne == false && numCompletedShortFlows == numReplicas*numMulticastSessions) {
            scheduleAt(simTime(), stopSimulation);
        }

        if (multiUnicasting == false && multiUniSourcing == true && oneToOne == false && numCompletedShortFlows == numReplicas*numMultisourceSessions) {
            scheduleAt(simTime(), stopSimulation);
        }



    }
}

} //namespace inet


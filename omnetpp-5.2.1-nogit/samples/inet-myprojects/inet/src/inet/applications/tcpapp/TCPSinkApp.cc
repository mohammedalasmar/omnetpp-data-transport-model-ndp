//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/applications/tcpapp/TCPSinkApp.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/transportlayer/contract/tcp/TCPCommand_m.h"

namespace inet {

Define_Module(TCPSinkApp);

simsignal_t TCPSinkApp::rcvdPkSignal = registerSignal("rcvdPk");

simsignal_t multicastGroupIdSignalTcp =  NodeStatus::registerSignal("multicastGroupIdSignalTcp");
simsignal_t multisourceGroupIdSignalTcp =  NodeStatus::registerSignal("multisourceGroupIdSignalTcp");

// MOH ADDED
//simsignal_t throughputRecordv1 = NodeStatus::registerSignal("throughputRecordv1");
simsignal_t fctRecordv1 = NodeStatus::registerSignal("fctRecordv1");

void TCPSinkApp::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    isLongFlow = par("isLongFlow");  // moh
    multiCastGroupId = par("multiCastGroupId");
    multiSrcGroupId = par("multiSrcGroupId");

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        bool isOperational;
        NodeStatus *nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
        isOperational = (!nodeStatus) || nodeStatus->getState() == NodeStatus::UP;
        if (!isOperational)
            throw cRuntimeError("This module doesn't support starting in node DOWN state");

        const char *localAddress = par("localAddress");
        int localPort = par("localPort");
        std::cout << "TCPSinkApp initialize -- localPort =   " << localPort << "\n";
        std::cout << "TCPSinkApp initialize -- isLongFlow =   " << isLongFlow << "\n";

        socket.setOutputGate(gate("tcpOut"));
        socket.readDataTransferModePar(*this);
        socket.bind(localAddress[0] ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
        socket.listen();
    }

}

void TCPSinkApp::handleMessage(cMessage *msg)
{
    if (msg->getKind() == TCP_I_PEER_CLOSED) {

        //Moh: added time stamp when closing the connection
        tEndAdded = simTime();
        std::cout << "NdpSinkApp::handleMessage mohmohmmohmohmohmohmohmohm aaa  PEER CLOSE " << bytesRcvd << " \n";

        //Moh: increment numCompletedShortFlows in the centralScheduler
       // int mm = 1400000;
     //   if (bytesRcvd == mm) { // for multi source   ZZZZZZZZZ  for multi-source  use this in the sink  mm =flowSize*1500*numReplicas

            std::string mod = "FatTreeTopology.centralSchedulerTCP";
            cModule* centralMod = getModuleByPath(mod.c_str());
            if (centralMod) {
                int numFinishedFlows = centralMod->par("numCompletedShortFlows");
                centralMod->par("numCompletedShortFlows").setDoubleValue(numFinishedFlows++);
            }
       // }

        // we close too
        msg->setName("close");
        msg->setKind(TCP_C_CLOSE);
        send(msg, "tcpOut");
    }
    else if (msg->getKind() == TCP_I_DATA || msg->getKind() == TCP_I_URGENT_DATA) {
        cPacket *pk = PK(msg);
        long packetLength = pk->getByteLength();
        bytesRcvd += packetLength;


        emit(rcvdPkSignal, pk);

        // Moh added: time stamp when receiving the first data packet (not the SYN, as the app wouldn't get that packet)
        if (firstDataReceived) tStartAdded = simTime();
        firstDataReceived = false;
        delete msg;
    }
    else {
        // must be data or some kind of indication -- can be dropped
        delete msg;
    }
}

void TCPSinkApp::finish()
{

    // MOH Added
    double throughput = 8 * (double) bytesRcvd / (SIMTIME_DBL(tEndAdded - tStartAdded));
    double FCT = SIMTIME_DBL(tEndAdded - tStartAdded);

    // don't emit the FCT of the longFlows(no need), we just observe the shortFlows
    if (isLongFlow == false) {
//        if (FCT < 0)  throw cRuntimeError("FCT FCT negative ");
//        if (FCT < 0)
//         std::cout << " negative !!! FCT   " << FCT << std::endl;
//        emit(throughputRecordv1, throughput); // we don't use this throughputRecordv1, we use the throughput calculations in ResultFilter.cc
        std::cout << "TCPSinkApp::finish()--- bytesRcvd: " << bytesRcvd << "  "   << this->getFullPath() <<   "\n\n\n";

        emit(fctRecordv1, FCT);
        emit(multicastGroupIdSignalTcp, multiCastGroupId);
        emit(multisourceGroupIdSignalTcp, multiSrcGroupId);
    }
}

void TCPSinkApp::refreshDisplay() const
{
    std::ostringstream os;
    os << TCPSocket::stateName(socket.getState()) << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet


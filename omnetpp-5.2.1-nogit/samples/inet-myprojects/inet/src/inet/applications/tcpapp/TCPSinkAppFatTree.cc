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

#include "inet/applications/tcpapp/TCPSinkAppFatTree.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/transportlayer/contract/tcp/TCPCommand_m.h"

namespace inet {

Define_Module(TCPSinkAppFatTree);

simsignal_t TCPSinkAppFatTree::rcvdPkSignal = registerSignal("rcvdPk");

// MOH ADDED
simsignal_t throughputRecord = NodeStatus::registerSignal("throughputRecord");
simsignal_t fctRecord = NodeStatus::registerSignal("fctRecord");

void TCPSinkAppFatTree::initialize(int stage)
{
    cSimpleModule::initialize(stage);

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
        socket.setOutputGate(gate("tcpOut"));
        socket.readDataTransferModePar(*this);
        socket.bind(localAddress[0] ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
        socket.listen();
    }
}

void TCPSinkAppFatTree::handleMessage(cMessage *msg)
{
    if (msg->getKind() == TCP_I_PEER_CLOSED) {

        //Moh: added time stamp when closing the connection
         tEndAdded=simTime();

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
        firstDataReceived=false;
        delete msg;
    }
    else {
        // must be data or some kind of indication -- can be dropped
        delete msg;
    }
}

void TCPSinkAppFatTree::finish()
{

      // MOH Added
      double throughput= 8*(double)bytesRcvd/ (SIMTIME_DBL(tEndAdded- tStartAdded)) ;
      double FCT= SIMTIME_DBL(tEndAdded- tStartAdded) ;
      emit(throughputRecord, throughput);
      emit(fctRecord, FCT);
}

void TCPSinkAppFatTree::refreshDisplay() const
{
    std::ostringstream os;
    os << TCPSocket::stateName(socket.getState()) << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}


void TCPSinkAppFatTree::handleParameterChange(const char *parname)
{
    std::cout << " ccccccccccccccc" << "  \n\n";

    if (parname && strcmp(parname, "localPort") == 0) {
        std::cout << " SINK NICE TO See YOU YAAAAAAAA " << "  \n\n";

        const char *localAddress = par("localAddress");
        std::cout << "new -- localAddress  " << localAddress << "\n";

        int localPort = par("localPort");
        std::cout << "new -- localPort " << localPort << "\n";
//        TCPSinkAppFatTree::initialize(int stage);
    }


}


} // namespace inet


// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

#include "inet/ndp/application/ndpapp/GenericAppMsgNdp_m.h"
#include "inet/ndp/application/ndpapp/NdpBasicClientApp.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/common/ModuleAccess.h"
#include <iostream>
#include <random>

namespace inet {

#define MSGKIND_CONNECT    0
#define MSGKIND_SEND       1

Define_Module(NdpBasicClientApp);
simsignal_t NdpBasicClientApp::rcvdPacketSignal =  registerSignal("rcvdPacketSignal");

NdpBasicClientApp::~NdpBasicClientApp() {
    cancelAndDelete(timeoutMsg);

    // Added
//    if (requestRexmitTimer)
//        delete cancelEvent(requestRexmitTimer);
}

void NdpBasicClientApp::initialize(int stage) {

    NdpAppBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
         //  WATCH(numRequestsToSend);
        bytesRcvd = 0;
        packetsRcvd=0;
        WATCH(bytesRcvd);
        sendBytes = par("sendBytes");   // commented moh

        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO&& stopTime < startTime)
        throw cRuntimeError("Invalid startTime/stopTime parameters");
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        timeoutMsg = new cMessage("timer");
        nodeStatus = dynamic_cast<NodeStatus *>(findContainingNode(this)->getSubmodule("status"));
        if (isNodeUp()) {
            timeoutMsg->setKind(MSGKIND_CONNECT);
            scheduleAt(startTime, timeoutMsg);
        }
    }
}

bool NdpBasicClientApp::isNodeUp() {
    return !nodeStatus || nodeStatus->getState() == NodeStatus::UP;
}


void NdpBasicClientApp::handleTimer(cMessage *msg) {
    /////// Added MOH send requests based on a timer
    switch (msg->getKind()) {

    case MSGKIND_CONNECT:
        connect();    // active OPEN
        break;

    case MSGKIND_SEND:   // not used now MHO see  NdpBasicClientApp::socketEstablished
//        sendRequest();
        break;

    default:
        throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
    }
}


void NdpBasicClientApp::socketEstablished(int connId, void *ptr) {
    NdpAppBase::socketEstablished(connId, ptr);
//    sendData();
//      if (opcode == 2)  sendWriteRequest();   // 1 read, 2 write
}


void NdpBasicClientApp::sendData() {
//    cPacket *msg = nullptr;
//    msg = new cPacket("APP-DATA");
//    msg->setByteLength(sendBytes);
//    socket.send(msg);
}

void NdpBasicClientApp::sendWriteRequest() {

    long requestLength = par("requestLength");
    long replyLength = par("replyLength");

    if (requestLength < 1)
        requestLength = 1;
    if (replyLength < 1)
        replyLength = 1;

    char msgname[16];
//    sprintf(msgname, "REQUEST-%d",++requestIndex);
    sprintf(msgname, "REQUEST-WRITE-INIT");

    GenericAppMsgNdp *msg = new GenericAppMsgNdp(msgname);
    msg->setByteLength(requestLength);
     msg->setServerClose(false);
    sendPacket(msg);
}


bool NdpBasicClientApp::handleOperationStage(LifecycleOperation *operation, int stage, IDoneCallback *doneCallback) {
    Enter_Method_Silent();
    if (dynamic_cast<NodeStartOperation *>(operation)) {
        if ((NodeStartOperation::Stage)stage == NodeStartOperation::STAGE_APPLICATION_LAYER) {
            simtime_t now = simTime();
            simtime_t start = std::max(startTime, now);
            if (timeoutMsg && ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime))) {
                timeoutMsg->setKind(MSGKIND_CONNECT);
                scheduleAt(start, timeoutMsg);
            }
        }
    }
    else if (dynamic_cast<NodeShutdownOperation *>(operation)) {
        if ((NodeShutdownOperation::Stage)stage == NodeShutdownOperation::STAGE_APPLICATION_LAYER) {
            cancelEvent(timeoutMsg);
            if (socket.getState() == NDPSocket::CONNECTED || socket.getState() == NDPSocket::CONNECTING || socket.getState() == NDPSocket::PEER_CLOSED)
            close();
            // TODO: wait until socket is closed
        }
    }
    else if (dynamic_cast<NodeCrashOperation *>(operation)) {
        if ((NodeCrashOperation::Stage)stage == NodeCrashOperation::STAGE_CRASH)
        cancelEvent(timeoutMsg);
    }
    else
    throw cRuntimeError("Unsupported lifecycle operation '%s'", operation->getClassName());
    return true;
}



void NdpBasicClientApp::rescheduleOrDeleteTimer(simtime_t d,
        short int msgKind) {
    cancelEvent(timeoutMsg);

    if (stopTime < SIMTIME_ZERO|| d < stopTime) {
        timeoutMsg->setKind(msgKind);
        scheduleAt(d, timeoutMsg);
    }
    else {
        delete timeoutMsg;
        timeoutMsg = nullptr;
    }
}

void NdpBasicClientApp::socketDataArrived(int connId, void *ptr, cPacket *msg, bool urgent) {
//    if (msg->getKind() == NDP_I_DATA) {
//        std::cout << "reply arrived to the client  " << std::endl;
//        packetsRcvd++;
//        cPacket *pk = PK(msg);
//        long packetLength = pk->getByteLength();
//        bytesRcvd += packetLength;
//        emit(rcvdSymbolSignal, pk);
//         std::cout << "NdpBasicClientApp::socketDataArrived , packetsRcvd  " << packetsRcvd << std::endl;
////        delete msg;
//    }

 }

void NdpBasicClientApp::socketClosed(int connId, void *ptr) {
    NdpAppBase::socketClosed(connId, ptr);
}

void NdpBasicClientApp::socketFailure(int connId, void *ptr, int code) {
    NdpAppBase::socketFailure(connId, ptr, code);

    // reconnect after a delay
    if (timeoutMsg) {
        simtime_t d = simTime() + (simtime_t) par("reconnectInterval");
        rescheduleOrDeleteTimer(d, MSGKIND_CONNECT);
    }
}


}// namespace inet


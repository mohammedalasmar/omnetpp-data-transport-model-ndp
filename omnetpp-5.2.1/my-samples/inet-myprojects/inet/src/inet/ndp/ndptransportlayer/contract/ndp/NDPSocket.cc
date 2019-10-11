#include "NDPSocket.h"

namespace inet {

NDPSocket::NDPSocket() {
    // don't allow user-specified connIds because they may conflict with
    // automatically assigned ones.
    connId = getEnvir()->getUniqueNumber();
    sockstate = NOT_BOUND;
    localPrt = remotePrt = -1;
    cb = nullptr;
    yourPtr = nullptr;
    gateToNdp = nullptr;
}

NDPSocket::NDPSocket(cMessage *msg) {
    NDPCommand *ind = dynamic_cast<NDPCommand *>(msg->getControlInfo());

    if (!ind)
        throw cRuntimeError(
                "NDPSocket::NDPSocket(cMessage *): no NDPCommand control info in message (not from NDP?)");

    connId = ind->getConnId();
    sockstate = CONNECTED;
    localPrt = remotePrt = -1;
    cb = nullptr;
    yourPtr = nullptr;

    gateToNdp = nullptr;

    if (msg->getKind() == NDP_I_ESTABLISHED) {
        // management of stockstate is left to processMessage() so we always
        // set it to CONNECTED in the ctor, whatever NDP_I_xxx arrives.
        // However, for convenience we extract NDPConnectInfo already here, so that
        // remote address/port can be read already after the ctor call.

        NDPConnectInfo *connectInfo = check_and_cast<NDPConnectInfo *>( msg->getControlInfo());
        localAddr = connectInfo->getLocalAddr();
        remoteAddr = connectInfo->getRemoteAddr();
        localPrt = connectInfo->getLocalPort();
        remotePrt = connectInfo->getRemotePort();
    }
}

NDPSocket::~NDPSocket() {
    if (cb)
        cb->socketDeleted(connId, yourPtr);
}

const char *NDPSocket::stateName(int state) {
#define CASE(x)    case x: \
        s = #x; break
    const char *s = "unknown";
    switch (state) {
    CASE(NOT_BOUND)
;        CASE(BOUND);
        CASE(LISTENING);
        CASE(CONNECTING);
        CASE(CONNECTED);
        CASE(PEER_CLOSED);
        CASE(LOCALLY_CLOSED);
        CASE(CLOSED);
        CASE(SOCKERROR);
    }
    return s;
#undef CASE
}

void NDPSocket::sendToNDP(cMessage *msg) {
    if (!gateToNdp)
        throw cRuntimeError( "NDPSocket: setOutputGate() must be invoked before socket can be used");

    check_and_cast<cSimpleModule *>(gateToNdp->getOwnerModule())->send(msg,  gateToNdp);
}

void NDPSocket::bind(int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NDPSocket::bind(): socket already bound");

    if (lPort < 0 || lPort > 65535)
        throw cRuntimeError("NDPSocket::bind(): invalid port number %d", lPort);

    localPrt = lPort;
    sockstate = BOUND;
}


void NDPSocket::bind(L3Address lAddr, int lPort) {
    if (sockstate != NOT_BOUND)
        throw cRuntimeError("NDPSocket::bind(): socket already bound");

    // allow -1 here, to make it possible to specify address only
    if ((lPort < 0 || lPort > 65535) && lPort != -1)
        throw cRuntimeError("NDPSocket::bind(): invalid port number %d", lPort);
//std::cout << " bind localAddr " << lAddr << "\n";
    localAddr = lAddr;
    localPrt = lPort;
    sockstate = BOUND;
}

 void NDPSocket::listen(bool fork) {

    if (sockstate != BOUND)
        throw cRuntimeError(
                sockstate == NOT_BOUND ?
                        "NDPSocket: must call bind() before listen()" :
                        "NDPSocket::listen(): connect() or listen() already called");

    cMessage *msg = new cMessage("PassiveOPEN", NDP_C_OPEN_PASSIVE);

    NDPOpenCommand *openCmd = new NDPOpenCommand();
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setConnId(connId);

    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());
    openCmd->setIsSender(false);
    openCmd->setIsReceiver(true);

    msg->setControlInfo(openCmd);
    sendToNDP(msg);
    sockstate = LISTENING;
}

// note: moh i added localAddress here, so instead of waiting for the syn/ack to be received to know my loaca add
// this is now should be known from the par("localAddress"); --> so this par should be specified correctly now
// note that the local port will be assigend by the transport layer (ndpmain based on the available number) see
// ushort Ndp::getEphemeralPort() (its -1 now)

void NDPSocket::connect(L3Address  localAddress ,  L3Address remoteAddress, int remotePort, bool isSender , bool isReceiver  , unsigned int numPacketsToSend , bool isLongFlow   , unsigned int priorityValue) {
    if (sockstate != NOT_BOUND && sockstate != BOUND)
        throw cRuntimeError( "NDPSocket::connect(): connect() or listen() already called (need renewSocket()?)");

    if (remotePort < 0 || remotePort > 65535)
        throw cRuntimeError( "NDPSocket::connect(): invalid remote port number %d", remotePort);


    cMessage *msg = new cMessage("ActiveOPEN", NDP_C_OPEN_ACTIVE);
    localAddr = localAddress;
    remoteAddr = remoteAddress;
    remotePrt = remotePort;
    EV_INFO << "\n\n\n wwwwww socket bind-- localAddr: " << localAddr << "  , remoteAddr: " << remoteAddr << "\n";
    EV_INFO << "localPrt: " << localPrt << " , remotePort:" << remotePrt << "\n\n\n";

    NDPOpenCommand *openCmd = new NDPOpenCommand();
    openCmd->setConnId(connId);
    openCmd->setLocalAddr(localAddr);
    openCmd->setLocalPort(localPrt);
    openCmd->setRemoteAddr(remoteAddr);
    openCmd->setRemotePort(remotePrt);

    openCmd->setNdpAlgorithmClass(ndpAlgorithmClass.c_str());


    openCmd->setNumPacketsToSend(numPacketsToSend);
    openCmd->setPriorityValue(priorityValue);
    openCmd->setIsSender(isSender);
    openCmd->setIsReceiver(isReceiver);
    openCmd->setIsLongFlow(isLongFlow);



    msg->setControlInfo(openCmd);
    sendToNDP(msg);


    sockstate = CONNECTING;
}

void NDPSocket::send(cMessage *msg) {
    if (sockstate != CONNECTED && sockstate != CONNECTING && sockstate != PEER_CLOSED)
        throw cRuntimeError(
                "NDPSocket::send(): socket not connected or connecting, state is %s",
                stateName(sockstate));

    msg->setKind(NDP_C_SEND);
    NDPSendCommand *cmd = new NDPSendCommand();
    cmd->setConnId(connId);
    msg->setControlInfo(cmd);
    sendToNDP(msg);
}

void NDPSocket::sendCommand(cMessage *msg) {
    sendToNDP(msg);
}

void NDPSocket::close() {
    std::cout << "NDPSocket::close() " << std::endl;
    if (sockstate != CONNECTED && sockstate != PEER_CLOSED
            && sockstate != CONNECTING && sockstate != LISTENING)
        throw cRuntimeError(
                "NDPSocket::close(): not connected or close() already called (sockstate=%s)",
                stateName(sockstate));

    cMessage *msg = new cMessage("CLOSE", NDP_C_CLOSE);
    NDPCommand *cmd = new NDPCommand();
    cmd->setConnId(connId);
    msg->setControlInfo(cmd);
    sendToNDP(msg);
    sockstate = (sockstate == CONNECTED) ? LOCALLY_CLOSED : CLOSED;
}

void NDPSocket::abort() {
    if (sockstate != NOT_BOUND && sockstate != BOUND && sockstate != CLOSED
            && sockstate != SOCKERROR) {
        cMessage *msg = new cMessage("ABORT", NDP_C_ABORT);
        NDPCommand *cmd = new NDPCommand();
        cmd->setConnId(connId);
        msg->setControlInfo(cmd);
        sendToNDP(msg);
    }
    sockstate = CLOSED;
}

void NDPSocket::requestStatus() {
    cMessage *msg = new cMessage("STATUS", NDP_C_STATUS);
    NDPCommand *cmd = new NDPCommand();
    cmd->setConnId(connId);
    msg->setControlInfo(cmd);
    sendToNDP(msg);
}

void NDPSocket::renewSocket() {
    connId = getEnvir()->getUniqueNumber();
    remoteAddr = localAddr = L3Address();
    remotePrt = localPrt = -1;
    sockstate = NOT_BOUND;
}

bool NDPSocket::belongsToSocket(cMessage *msg) {
    return dynamic_cast<NDPCommand *>(msg->getControlInfo())
            && ((NDPCommand *) (msg->getControlInfo()))->getConnId() == connId;
}

bool NDPSocket::belongsToAnyNDPSocket(cMessage *msg) {
    return dynamic_cast<NDPCommand *>(msg->getControlInfo());
}

void NDPSocket::setCallbackObject(CallbackInterface *callback, void *yourPointer) {
    cb = callback;
    yourPtr = yourPointer;
}

void NDPSocket::processMessage(cMessage *msg) {

     ASSERT(belongsToSocket(msg));

    NDPStatusInfo *status;
    NDPConnectInfo *connectInfo;

    switch (msg->getKind()) {
    case NDP_I_DATA:
        if (cb)
            cb->socketDataArrived(connId, yourPtr, PK(msg), false); // see NdpBasicClientApp::socketDataArrived
        else
            delete msg;

        break;

    case NDP_I_URGENT_DATA:
        if (cb)
            cb->socketDataArrived(connId, yourPtr, PK(msg), true);
        else
            delete msg;

        break;

    case NDP_I_ESTABLISHED:
        // Note: this code is only for sockets doing active open, and nonforking
        // listening sockets. For a forking listening sockets, NDP_I_ESTABLISHED
        // carries a new connId which won't match the connId of this NDPSocket,
        // so you won't get here. Rather, when you see NDP_I_ESTABLISHED, you'll
        // want to create a new NDPSocket object via new NDPSocket(msg).
        sockstate = CONNECTED;
        connectInfo = check_and_cast<NDPConnectInfo *>(msg->getControlInfo());
        localAddr = connectInfo->getLocalAddr();
        remoteAddr = connectInfo->getRemoteAddr();
        localPrt = connectInfo->getLocalPort();
        remotePrt = connectInfo->getRemotePort();
        delete msg;

        if (cb)
            cb->socketEstablished(connId, yourPtr); // MOH: this calls  NdpBasicClientApp::socketEstablished(int connId, void *ptr) to send the first request

        break;

    case NDP_I_PEER_CLOSED:
        sockstate = PEER_CLOSED;

        delete msg;

        if (cb)
            cb->socketPeerClosed(connId, yourPtr);

        break;

    case NDP_I_CLOSED:
        std::cout << " socket closed \n";

        sockstate = CLOSED;
        delete msg;

        if (cb) {
            cb->socketClosed(connId, yourPtr);
        }

        break;

    case NDP_I_CONNECTION_REFUSED:
    case NDP_I_CONNECTION_RESET:
    case NDP_I_TIMED_OUT:
        sockstate = SOCKERROR;

        if (cb)
            cb->socketFailure(connId, yourPtr, msg->getKind());

        delete msg;
        break;

    case NDP_I_STATUS:
        status = check_and_cast<NDPStatusInfo *>(msg->removeControlInfo());
        delete msg;

        if (cb)
            cb->socketStatusArrived(connId, yourPtr, status);

        break;

    default:
        throw cRuntimeError(
                "NDPSocket: invalid msg kind %d, one of the NDP_I_xxx constants expected",
                msg->getKind());
    }
}


} // namespace inet


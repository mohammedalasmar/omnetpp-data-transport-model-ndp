// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019



#include "inet/ndp/application/ndpapp/NdpAppBase.h"

#include "inet/networklayer/common/L3AddressResolver.h"

namespace inet {

void NdpAppBase::initialize(int stage) {
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numSessions = numBroken = packetsSent = packetsRcvd = bytesSent =
                bytesRcvd = 0;
    } else if (stage == INITSTAGE_APPLICATION_LAYER) {
        // parameters
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");

        socket.bind( *localAddress ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
        socket.setCallbackObject(this);
        socket.setOutputGate(gate("ndpOut"));
        setStatusString("Sender ready ...");
    }
}

void NdpAppBase::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {
        handleTimer(msg);
    }
    else
        socket.processMessage(msg);
}




void NdpAppBase::connect() {
    // we need a new connId if this is not the first connection
    socket.renewSocket();

    unsigned int numPacketsToSend = par("numPacketsToSend").longValue();
    unsigned int priorityValue = par("priorityValue").doubleValue();
    bool isLongFlow = par("isLongFlow").boolValue();
    bool isSender = par("isSender").boolValue();
    bool isReceiver = par("isReceiver").boolValue();


   // connect
    const char *connectAddress = par("connectAddress");
    int connectPort = par("connectPort");

    L3Address destination;
    L3AddressResolver().tryResolve(connectAddress, destination);

    // added by MOH
    const char *srcAddress = par("localAddress");
    L3Address localAddress;
    L3AddressResolver().tryResolve(srcAddress, localAddress);
    EV_INFO << "\n\n\n AAAA localAddress add " << localAddress  <<"\n\n\n" ;

    if (destination.isUnspecified()) {
        EV_ERROR << "Connecting to " << connectAddress << " port=" << connectPort  << ": cannot resolve destination address\n";
//        std::cout << "NdpAppBase::connect() Connecting to " << connectAddress << " port=" << connectPort  << ": cannot resolve destination address\n";

    } else {
        EV_INFO << "Connecting to " << connectAddress << "(" << destination << ") port=" << connectPort << endl;

//        std::string dd= "10.0.0.86";
//        L3Address destination2 =L3Address(dd.c_str());
        setStatusString("connecting");
        socket.connect(localAddress , destination  , connectPort, isSender , isReceiver , numPacketsToSend, isLongFlow, priorityValue);
        EV_INFO << "Connecting to mmmmm" << connectAddress << "(" << destination  << ") port=" << connectPort << endl;

        numSessions++;
    }
}

void NdpAppBase::close() {
    setStatusString("closing");
    EV_INFO << "issuing CLOSE command\n";
    socket.close();
}

void NdpAppBase::sendPacket(cPacket *msg) {
    int numBytes = msg->getByteLength();
    socket.send(msg);

    packetsSent++;
    bytesSent += numBytes;
}

void NdpAppBase::setStatusString(const char *s) {
    if (hasGUI())
        getDisplayString().setTagArg("t", 0, s);
}

void NdpAppBase::socketEstablished(int, void *) {

    // *redefine* to perform or schedule first sending
    EV_INFO << "\n\n\n\n\n\n\n\n connected\n";
    setStatusString("Established");
}


void NdpAppBase::socketDataArrived(int, void *, cPacket *msg, bool) {
    // *redefine* to perform or schedule next sending
    packetsRcvd++;
    bytesRcvd += msg->getByteLength();
    delete msg;
}

void NdpAppBase::socketPeerClosed(int, void *) {
    // close the connection (if not already closed)
    if (socket.getState() == NDPSocket::PEER_CLOSED) {
        EV_INFO << "remote NDP closed, closing here as well\n";
        close();
    }
}

void NdpAppBase::socketClosed(int, void *) {
    // *redefine* to start another session etc.
    EV_INFO << "connection closed\n";
    setStatusString("closed");
}

void NdpAppBase::socketFailure(int, void *, int code) {
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV_WARN << "connection broken\n";
    setStatusString("broken");

    numBroken++;
}

void NdpAppBase::finish() {
    std::string modulePath = getFullPath();

    EV_INFO << modulePath << ": opened " << numSessions << " sessions\n";
    EV_INFO << modulePath << ": sent " << bytesSent << " bytes in " << packetsSent << " packets\n";
    EV_INFO << modulePath << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";

}

} // namespace inet


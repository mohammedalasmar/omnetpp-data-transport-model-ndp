
#ifndef __INET_NDPSocket_H
#define __INET_NDPSocket_H

#include "inet/ndp/ndptransportlayer/contract/ndp/NDPCommand_m.h"
#include "inet/common/INETDefs.h"
#include "inet/networklayer/common/L3Address.h"

namespace inet {

class NDPStatusInfo;

class INET_API NDPSocket
{
  public:
    /**
     * Abstract base class for your callback objects. See setCallbackObject()
     * and processMessage() for more info.
     *
     * Note: this class is not subclassed from cObject, because
     * classes may have both this class and cSimpleModule as base class,
     * and cSimpleModule is already a cObject.
     */
    class CallbackInterface
    {
      public:
        virtual ~CallbackInterface() {}
        virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent) = 0;
        virtual void socketEstablished(int connId, void *yourPtr) {}
        virtual void socketPeerClosed(int connId, void *yourPtr) {}
        virtual void socketClosed(int connId, void *yourPtr) {}
        virtual void socketFailure(int connId, void *yourPtr, int code) {}
        virtual void socketStatusArrived(int connId, void *yourPtr,NDPStatusInfo *status) { delete status; }
        virtual void socketDeleted(int connId, void *yourPtr) {}
    };

    enum State { NOT_BOUND, BOUND, LISTENING, CONNECTING, CONNECTED, PEER_CLOSED, LOCALLY_CLOSED, CLOSED, SOCKERROR };

  protected:
    int connId;
    int sockstate;

    L3Address localAddr;
    int localPrt;
    L3Address remoteAddr;
    int remotePrt;

    CallbackInterface *cb;
    void *yourPtr;

    cGate *gateToNdp;


    std::string ndpAlgorithmClass;

  protected:
    void sendToNDP(cMessage *msg);

    // internal: implementation behind listen() and listenOnce()
    void listen(bool fork);

  public:
    /**
     * Constructor. The getConnectionId() method returns a valid Id right after
     * constructor call.
     */
    NDPSocket();

    /**
     * Constructor, to be used with forked sockets (see listen()).
     * The new connId will be picked up from the message: it should have
     * arrived from NDP and contain NDPCommmand control info.
     */
    NDPSocket(cMessage *msg);

    /**
     * Destructor
     */
    ~NDPSocket();

    /**
     * Returns the internal connection Id. NDP uses the (gate index, connId) pair
     * to identify the connection when it receives a command from the application
     * (or NDPSocket).
     */
    int getConnectionId() const { return connId; }

    /**
     * Returns the socket state, one of NOT_BOUND, CLOSED, LISTENING, CONNECTING,
     * CONNECTED, etc. Messages received from NDP must be routed through
     * processMessage() in order to keep socket state up-to-date.
     */
    int getState() { return sockstate; }

    /**
     * Returns name of socket state code returned by getState().
     */
    static const char *stateName(int state);

    void setState(enum State state) { sockstate = state; };

    /** @name Getter functions */
    //@{
    L3Address getLocalAddress() { return localAddr; }
    int getLocalPort() { return localPrt; }
    L3Address getRemoteAddress() { return remoteAddr; }
    int getRemotePort() { return remotePrt; }
    //@}

    /** @name Opening and closing connections, sending data */
    //@{

    /**
     * Sets the gate on which to send to NDP. Must be invoked before socket
     * can be used. Example: <tt>socket.setOutputGate(gate("raptondpOut"));</tt>
     */
    void setOutputGate(cGate *toNdp) { gateToNdp = toNdp; }

    /**
     * Bind the socket to a local port number.
     */
    void bind(int localPort);

    /**
     * Bind the socket to a local port number and IP address (useful with
     * multi-homing).
     */
    void bind(L3Address localAddr, int localPort);


    /**
     * Returns the current ndpAlgorithmClass parameter.
     */
    const char *getNdpAlgorithmClass() const { return ndpAlgorithmClass.c_str(); }


    /**
     * Sets the ndpAlgorithmClass parameter of the next connect() or listen() call.
     */
    void setNdpAlgorithmClass(const char *ndpAlgorithmClass) { this->ndpAlgorithmClass = ndpAlgorithmClass; }

    /**
     * Initiates passive OPEN, creating a "forking" connection that will listen
     * on the port you bound the socket to. Every incoming connection will
     * get a new connId (and thus, must be handled with a new NDPSocket object),
     * while the original connection (original connId) will keep listening on
     * the port. The new NDPSocket object must be created with the
     * NDPSocket(cMessage *msg) constructor.
     *
     * If you need to handle multiple incoming connections, the NDPSocketMap
     * class can also be useful, and NDPSrvHostApp shows how to put it all
     * together. See also NDPOpenCommand documentation (neddoc) for more info.
     */
    void listen() { listen(true); }

    /**
     * Initiates passive OPEN to create a non-forking listening connection.
     * Non-forking means that NDP will accept the first incoming
     * connection, and refuse subsequent ones.
     *
     * See NDPOpenCommand documentation (neddoc) for more info.
     */
    void listenOnce() { listen(false); }

    /**
     * Active OPEN to the given remote socket.
     */
    void connect(L3Address  localAddress , L3Address remoteAddr, int remotePort, bool isSender , bool isReceiver ,  unsigned int numPacketsToSend, bool isLongFlow    , unsigned int priorityValue);

    /**
     * Sends data packet.
     */
    void send(cMessage *msg);

    /**
     * Sends command.
     */
    void sendCommand(cMessage *msg);

    /**
     * Closes the local end of the connection. With NDP, a CLOSE operation
     * means "I have no more data to send", and thus results in a one-way
     * connection until the remote NDP closes too (or the FIN_WAIT_1 timeout
     * expires)
     */
    void close();

    /**
     * Aborts the connection.
     */
    void abort();

    /**
     * Causes NDP to reply with a fresh NDPStatusInfo, attached to a dummy
     * message as getControlInfo(). The reply message can be recognized by its
     * message kind NDP_I_STATUS, or (if a callback object is used)
     * the socketStatusArrived() method of the callback object will be
     * called.
     */
    void requestStatus();

    /**
     * Required to re-connect with a "used" NDPSocket object.
     * By default, a NDPSocket object is tied to a single NDP connection,
     * via the connectionId. When the connection gets closed or aborted,
     * you cannot use the socket to connect again (by connect() or listen())
     * unless you obtain a new connectionId by calling this method.
     *
     * BEWARE if you use NDPSocketMap! NDPSocketMap uses connectionId
     * to find NDPSockets, so after calling this method you have to remove
     * the socket from your NDPSocketMap, and re-add it. Otherwise NDPSocketMap
     * will get confused.
     *
     * The reason why one must obtain a new connectionId is that NDP still
     * has to maintain the connection data structure (identified by the old
     * connectionId) internally for a while (2 maximum segment lifetimes = 240s)
     * after it reported "connection closed" to us.
     */
    void renewSocket();
    //@}

    /** @name Handling of messages arriving from NDP */
    //@{
    /**
     * Returns true if the message belongs to this socket instance (message
     * has a NDPCommand as getControlInfo(), and the connId in it matches
     * that of the socket.)
     */
    bool belongsToSocket(cMessage *msg);

    /**
     * Returns true if the message belongs to any NDPSocket instance.
     * (This basically checks if the message has a NDPCommand attached to
     * it as getControlInfo().)
     */
    static bool belongsToAnyNDPSocket(cMessage *msg);

    /**
     * Sets a callback object, to be used with processMessage().
     * This callback object may be your simple module itself (if it
     * multiply inherits from CallbackInterface too, that is you
     * declared it as
     * <pre>
     * class MyAppModule : public cSimpleModule, public NDPSocket::CallbackInterface
     * </pre>
     * and redefined the necessary virtual functions; or you may use
     * dedicated class (and objects) for this purpose.
     *
     * NDPSocket doesn't delete the callback object in the destructor
     * or on any other occasion.
     *
     * YourPtr is an optional pointer. It may contain any value you wish --
     * NDPSocket will not look at it or do anything with it except passing
     * it back to you in the CallbackInterface calls. You may find it
     * useful if you maintain additional per-connection information:
     * in that case you don't have to look it up by connId in the callbacks,
     * you can have it passed to you as yourPtr.
     */
    void setCallbackObject(CallbackInterface *cb, void *yourPtr = nullptr);

    /**
     * Examines the message (which should have arrived from NDP),
     * updates socket state, and if there is a callback object installed
     * (see setCallbackObject(), class CallbackInterface), dispatches
     * to the appropriate method of it with the same yourPtr that
     * you gave in the setCallbackObject() call.
     *
     * The method deletes the message, unless (1) there is a callback object
     * installed AND (2) the message is payload (message kind NDP_I_DATA or
     * NDP_I_URGENT_DATA) when the responsibility of destruction is on the
     * socketDataArrived() callback method.
     *
     * IMPORTANT: for performance reasons, this method doesn't check that
     * the message belongs to this socket, i.e. belongsToSocket(msg) would
     * return true!
     */
    void processMessage(cMessage *msg);
    //@}
};

} // namespace inet

#endif // ifndef __INET_NDPSocket_H


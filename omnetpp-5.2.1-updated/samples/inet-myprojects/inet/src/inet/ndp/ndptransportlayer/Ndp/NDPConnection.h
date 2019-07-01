#ifndef __INET_NDPCONNECTION_H
#define __INET_NDPCONNECTION_H

#include "inet/ndp/ndptransportlayer/Ndp/ndp_common/NDPSegment.h"
#include "inet/common/INETDefs.h"

#include "inet/networklayer/common/L3Address.h"
#include "Ndp.h"

namespace inet {

class NDPCommand;
class NDPOpenCommand;

namespace ndp {

class NDPSegment;
class NDPSendQueue;
//class NDPSACKRexmitQueue;
class NDPReceiveQueue;
class NDPAlgorithm;

enum NDPState {
    NDP_S_INIT = 0,
    NDP_S_CLOSED = FSM_Steady(1),
    NDP_S_LISTEN = FSM_Steady(2),
    NDP_S_SYN_SENT = FSM_Steady(3),
    NDP_S_SYN_RCVD = FSM_Steady(4),
    NDP_S_ESTABLISHED = FSM_Steady(5),
    NDP_S_CLOSE_WAIT = FSM_Steady(6),
    NDP_S_LAST_ACK = FSM_Steady(7),
    NDP_S_FIN_WAIT_1 = FSM_Steady(8),
    NDP_S_FIN_WAIT_2 = FSM_Steady(9),
    NDP_S_CLOSING = FSM_Steady(10),
    NDP_S_TIME_WAIT = FSM_Steady(11)
};

//
// Event, strictly for the FSM state transition purposes.
// DO NOT USE outside performStateTransition()!
//
enum NDPEventCode {
    NDP_E_IGNORE,

    // app commands
    // (Note: no RECEIVE command, data are automatically passed up)
    NDP_E_OPEN_ACTIVE,
    NDP_E_OPEN_PASSIVE,
    NDP_E_SEND,
    NDP_E_CLOSE,
    NDP_E_ABORT,
    NDP_E_STATUS,
    NDP_E_QUEUE_BYTES_LIMIT,
    NDP_E_READ,

    // TPDU types
    NDP_E_RCV_DATA,
    NDP_E_RCV_ACK,
    NDP_E_RCV_SYN,
    NDP_E_RCV_SYN_ACK,
    NDP_E_RCV_FIN,
    NDP_E_RCV_FIN_ACK,
    NDP_E_RCV_RST,    // covers RST+ACK too

    NDP_E_RCV_UNEXP_SYN,    // unexpected SYN

    // timers
    NDP_E_TIMEOUT_2MSL,    // RFC 793, a.k.a. TIME-WAIT timer
    NDP_E_TIMEOUT_CONN_ESTAB,
    NDP_E_TIMEOUT_FIN_WAIT_2,

// All other timers (REXMT, PERSIST, DELAYED-ACK, KEEP-ALIVE, etc.),
// are handled in NDPAlgorithm.
};

/** @name Timeout values */
//@{
#define NDP_TIMEOUT_CONN_ESTAB        75  // 75 seconds
#define NDP_TIMEOUT_FIN_WAIT_2        600  // 10 minutes
#define NDP_TIMEOUT_2MSL              240  // 2 * 2 minutes
#define NDP_TIMEOUT_SYN_REXMIT        3  // initially 3 seconds

#define NDP_TIMEOUT_PULL_REXMIT        0.5  // initially 500 msec  MOH

#define NDP_TIMEOUT_SYN_REXMIT_MAX    240  // 4 mins (will only be used with SYN+ACK: with SYN CONN_ESTAB occurs sooner)
//@}

#define MAX_SYN_REXMIT_COUNT          12  // will only be used with SYN+ACK: with SYN CONN_ESTAB occurs sooner
#define NDP_MAX_WIN                   65535  // 65535 bytes, largest value (16 bit) for (unscaled) window size
 #define DUPTHRESH                     3  // used for NDPTahoe, NDPReno and SACK (RFC 3517)
//#define MAX_SACK_BLOCKS               60  // will only be used with SACK
#define NDP_OPTIONS_MAX_SIZE          40  // 40 bytes, 15 * 4 bytes (15 is the largest number in 4 bits length data offset field), NDP_MAX_HEADER_OCTETS - NDP_HEADER_OCTETS = 40
//#define NDP_OPTION_SACK_MIN_SIZE      10  // 10 bytes, option length = 8 * n + 2 bytes (NOP)
#define NDP_OPTION_TS_SIZE            12  // 12 bytes, option length = 10 bytes + 2 bytes (NOP)
#define PAWS_IDLE_TIME_THRESH         (24 * 24 * 3600)  // 24 days in seconds (RFC 1323)

//typedef std::list<Sack> SackList;

/**
 * Contains state variables ("TCB") for NDP.
 *
 * NDPStateVariables is effectively a "struct" -- it only contains
 * public data members. (Only declared as a class so that we can use
 * cObject as base class and make it possible to inspect
 * it in Tkenv.)
 *
 * NDPStateVariables only contains variables needed to implement
 * the "base" (RFC 793) NDP. More advanced NDP variants are encapsulated
 * into NDPAlgorithm subclasses which can have their own state blocks,
 * subclassed from NDPStateVariables. See NDPAlgorithm::createStateVariables().
 */
class INET_API NDPStateVariables: public cObject {
public:
    NDPStateVariables();
    virtual std::string info() const override;
    virtual std::string detailedInfo() const override;

public:
    bool active;    // set if the connection was initiated by an active open

    unsigned int request_id;
    unsigned int internal_request_id;
    bool isLongFlow;
    bool isHeader;

    uint32 IW;  //initial window size
    bool connFinished;
//    unsigned int  sequenceNumber;

    uint32 numPacketsToGet;
    uint32 numPacketsToSend;
     bool isSender;
     bool isReceiver;
    unsigned int  priorityValue;


    unsigned int numRcvdPkt;
    unsigned int numRcvTrimmedHeader;


    uint32 numberReceivedPackets;
    uint32 numberSentPackets;

    int request_rexmit_count; // number of SYN/SYN+ACK retransmissions (=1 after first rexmit)

    simtime_t request_rexmit_timeout;  // current request retransmission timeout
    uint32 numPullsTimeOuts;
    bool connNotAddedYet;
    bool isfinalReceivedPrintedOut;

    uint32 snd_mss; // sender maximum segment size (without headers, i.e. only segment text); see RFC 2581, page 1.
                    // This will be set to the minimum of the local smss parameter and the value specified in the
                    // MSS option received during connection setup.

                    // send sequence number variables (see RFC 793, "3.2. Terminology")


    uint32 iss;    // initial sequence number (ISS)
    uint32 irs;        // initial receive sequence number


    // SYN, SYN+ACK retransmission variables (handled separately
    // because normal rexmit belongs to NDPAlgorithm)
    int syn_rexmit_count; // number of SYN/SYN+ACK retransmissions (=1 after first rexmit)
    simtime_t syn_rexmit_timeout;  // current SYN/SYN+ACK retransmission timeout
};


class INET_API NDPConnection {
public:

    struct PakcetsToSend {
        unsigned int pktId;
        cPacket *msg;
    };
    typedef std::list<PakcetsToSend> PakcetsList;
//    PakcetsList sentPakcetsList;
    PakcetsList receivedPacketsList;
    PakcetsList retransmitQueue; // TODO for nack


    // connection identification by apps: appgateIndex+connId
    int appGateIndex = -1;    // application gate index
    int connId = -1;    // identifies connection within the app

    // socket pair
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort = -1;
    int remotePort = -1;
//    int ClientOrServerSel=10;
protected:
    Ndp *ndpMain = nullptr;    // NDP module

    // NDP state machine
    cFSM fsm;

    // variables associated with NDP state
    NDPStateVariables *state = nullptr;

    // NDP queues
    NDPSendQueue *sendQueue = nullptr;
    NDPReceiveQueue *receiveQueue = nullptr;


public:
    // NDPSACKRexmitQueue *rexmitQueue = nullptr;
    virtual int getNumRcvdPackets();
    virtual bool  isConnFinished();
    virtual void  setConnFinished() ;

protected:
     cQueue pullQueue;
    // NDP behavior in data transfer state
     NDPAlgorithm *ndpAlgorithm = nullptr;

    // timers
    cMessage *requestInternalTimer = nullptr;

    cMessage *the2MSLTimer = nullptr;
    cMessage *connEstabTimer = nullptr;
    cMessage *finWait2Timer = nullptr;
    cMessage *synRexmitTimer = nullptr;    // for retransmitting SYN and SYN+ACK

    // statistics


protected:
    /** @name FSM transitions: analysing events and executing state transitions */
    //@{
    /** Maps app command codes (msg kind of app command msgs) to NDP_E_xxx event codes */
    virtual NDPEventCode preanalyseAppCommandEvent(int commandCode);
    /** Implemements the pure NDP state machine */
    virtual bool performStateTransition(const NDPEventCode& event);
    /** Perform cleanup necessary when entering a new state, e.g. cancelling timers */
    virtual void stateEntered(int state, int oldState, NDPEventCode event);
    //@}

    /** @name Processing app commands. Invoked from processAppCommand(). */
    //@{
    virtual void process_OPEN_ACTIVE(NDPEventCode& event, NDPCommand *NDPCommand, cMessage *msg);
    virtual void process_OPEN_PASSIVE(NDPEventCode& event, NDPCommand *NDPCommand,  cMessage *msg);


    /**
     * Process incoming NDP segment. Returns a specific event code (e.g. NDP_E_RCV_SYN)
     * which will drive the state machine.
     */
    virtual NDPEventCode process_RCV_SEGMENT(NDPSegment *NDPseg, L3Address src,
            L3Address dest);
    virtual NDPEventCode processSegmentInListen(NDPSegment *NDPseg, L3Address src,
            L3Address dest);



    virtual NDPEventCode processSegment1stThru8th(NDPSegment *NDPseg);

    //@}

    /** @name Processing of NDP options. Invoked from readHeaderOptions(). Return value indicates whether the option was valid. */
    //@{
    virtual bool processMSSOption(NDPSegment *NDPseg,
            const NDPOptionMaxSegmentSize& option);


    //@}

    /** @name Processing timeouts. Invoked from processTimer(). */
    //@{
    virtual void process_TIMEOUT_2MSL();
    virtual void process_TIMEOUT_CONN_ESTAB();
    virtual void process_TIMEOUT_FIN_WAIT_2();
     //@}

   // MOH
    virtual void process_TIMEOUT_REQUEST_REXMIT();

    /** Utility: creates send/receive queues and NDPAlgorithm */
    virtual void initConnection(NDPOpenCommand *openCmd);

    /** Utility: set snd_mss, rcv_wnd and sack in newly created state variables block */
    virtual void configureStateVariables();

    /** Utility: generates ISS and initializes corresponding state variables */
    virtual void selectInitialSeqNum();



    /** Utility: readHeaderOptions (Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented) */
    virtual void readHeaderOptions(NDPSegment *NDPseg);
    /** Utility: writeHeaderOptions (Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented) */
    virtual NDPSegment writeHeaderOptions(NDPSegment *NDPseg);

    virtual uint32 getTSval(NDPSegment *NDPseg) const;

    /** Utility: get TSecr from segments TS header option */
    virtual uint32 getTSecr(NDPSegment *NDPseg) const;

public:


    virtual void sendRequest();// MOH: HAS BEEN ADDED
    virtual void sendRequestSegment();// MOH: HAS BEEN ADDED
    virtual void sendAckNdp(unsigned int AckNum); // MOH: HAS BEEN ADDED

    virtual void sendNackNdp(unsigned int nackNum); // MOH: HAS BEEN ADDED


    virtual void ackArrivedFreeBuffer(unsigned int ackNum); // MOH: HAS BEEN ADDED
    virtual void   getBufferedPkt(unsigned int seqNum , std::list<PakcetsToSend>::iterator& iter );
    virtual void   getFirstBufferedPkt(std::list<PakcetsToSend>::iterator& iter );


    virtual void generatePacketsList();
    virtual void sendInitialWindow();

    virtual void addNewPacketToSend();
     /**
     * Utility: Send data from sendQueue, at most congestionWindow.
     * If fullSegmentsOnly is set, don't send segments smaller than SMSS (needed for Nagle).
     * Returns true if some data was actually sent.
     */
    virtual bool sendData(bool fullSegmentsOnly, uint32 congestionWindow,  bool isReader ,bool isWriter   , unsigned int opcode );




    /** Utility: sends RST; does not use connection state */
    virtual void sendRst(uint32 seq, L3Address src, L3Address dest, int srcPort,
            int destPort);
    /** Utility: sends RST+ACK; does not use connection state */
    virtual void sendRstAck(uint32 seq, uint32 ack, L3Address src,
            L3Address dest, int srcPort, int destPort);




    /** Utility: adds control info to segment and sends it to IP */
    virtual void sendToIP(NDPSegment *NDPseg);

    /**
     * Utility: This factory method gets invoked throughout the NDP model to
     * create a NDPSegment. Override it if you need to subclass NDPSegment.
     */
    virtual NDPSegment *createNDPSegment(const char *name);

    virtual void startRequestRexmitTimer(); // MOH
    virtual void  addRequestToPullsQueue();
    virtual void  sendRequestFromPullsQueue();

    virtual int  getPullsQueueLength();

    /** Utility: signal to user that connection timed out */
    virtual void signalConnectionTimeout();

    /** Utility: start a timer */
    void scheduleTimeout(cMessage *msg, simtime_t timeout) {
        ndpMain->scheduleAt(simTime() + timeout, msg);
    }

protected:
    /** Utility: cancel a timer */
    cMessage *cancelEvent(cMessage *msg) {
        return ndpMain->cancelEvent(msg);
    }

    /** Utility: send IP packet */
    static void sendToIP(NDPSegment *NDPseg, L3Address src, L3Address dest);

    /** Utility: sends packet to application */
    virtual void sendToApp(cMessage *msg);

    /** Utility: sends status indication (NDP_I_xxx) to application */
    virtual void sendIndicationToApp(int code, const int id = 0);

    /** Utility: sends NDP_I_ESTABLISHED indication with NDPConnectInfo to application */
    virtual void sendEstabIndicationToApp();

public:
    /** Utility: prints local/remote addr/port and app gate index/connId */
    virtual void printConnBrief() const;
    /** Utility: prints important header fields */
    static void printSegmentBrief(NDPSegment *NDPseg);
    /** Utility: returns name of NDP_S_xxx constants */
    static const char *stateName(int state);
    /** Utility: returns name of NDP_E_xxx constants */
    static const char *eventName(int event);
    /** Utility: returns name of NDP_I_xxx constants */
    static const char *indicationName(int code);
    /** Utility: returns name of NDPOPTION_xxx constants */
    static const char *optionName(int option);



public:
    /**
     * The "normal" constructor.
     */
    NDPConnection(Ndp *mod, int appGateIndex, int connId);

    /**
     * Note: this default ctor is NOT used to create live connections, only
     * temporary ones so that NDPMain can invoke their segmentArrivalWhileClosed().
     */
    NDPConnection();

    /**
     * Destructor.
     */
    virtual ~NDPConnection();

    virtual void segmentArrivalWhileClosed(NDPSegment *NDPseg, L3Address src,
            L3Address dest);

    /** @name Various getters **/
    //@{
    int getFsmState() const {
        return fsm.getState();
    }
    NDPStateVariables *getState() {
        return state;
    }
    NDPSendQueue *getSendQueue() {
        return sendQueue;
    }
    // NDPSACKRexmitQueue *getRexmitQueue() { return rexmitQueue; }
    NDPReceiveQueue *getReceiveQueue() {
        return receiveQueue;
    }
    NDPAlgorithm *getNDPAlgorithm() {
        return ndpAlgorithm;
    }
    Ndp *getNDPMain() {
        return ndpMain;
    }

    virtual bool processTimer(cMessage *msg);

    virtual bool processNDPSegment(NDPSegment *NDPSeg, L3Address srcAddr,
            L3Address destAddr);

    virtual bool processAppCommand(cMessage *msg);



    /**
     * Utility: converts a given simtime to a timestamp (TS).
     */
    static uint32 convertSimtimeToTS(simtime_t simtime);

    /**
     * Utility: converts a given timestamp (TS) to a simtime.
     */
    static simtime_t convertTSToSimtime(uint32 timestamp);

};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_NDPCONNECTION_H


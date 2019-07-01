// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019



cplusplus {{
#include "inet/networklayer/common/L3Address.h"
}}

namespace inet;

class noncobject L3Address;

//
// NDPR command codes, sent by the application to NDPR. These constants
// should be set as message kind on a message sent to the NDPR entity.
//
// @see ~NDPRCommand, ~NDPROpenCommand, ~IRaptoNDP
//
enum NDPCommandCode
{
    NDP_C_OPEN_ACTIVE = 1;   // active open (must carry ~NDPOpenCommand)
    NDP_C_OPEN_PASSIVE = 2;  // passive open (must carry ~NDPOpenCommand)
    NDP_C_SEND = 3;          // send data (set on data packet)
    NDP_C_CLOSE = 5;         // "I have no more data to send"
    NDP_C_ABORT = 6;         // abort connection
    NDP_C_STATUS = 7;        // request status info (NDP_I_STATUS) from NDP
    NDP_C_QUEUE_BYTES_LIMIT = 8; // set send queue limit (in bytes)
    NDP_C_READ = 9;       // send request to NDP to deliver data
}


//
// NDP indications, sent by NDP to the application. NDP will set these
// constants as message kind on messages it sends to the application.
//
// @see ~NDPCommand, ~NDPStatusInfo, ~INDP
//
enum NDPStatusInd
{
    NDP_I_DATA = 1;              // data packet (set on data packet)
    NDP_I_URGENT_DATA = 2;       // urgent data (set on data packet)
    NDP_I_ESTABLISHED = 3;       // connection established
    NDP_I_PEER_CLOSED = 4;       // FIN received from remote NDP
    NDP_I_CLOSED = 5;            // connection closed normally (via FIN exchange)
    NDP_I_CONNECTION_REFUSED = 6; // connection refused
    NDP_I_CONNECTION_RESET = 7;  // connection reset
    NDP_I_TIMED_OUT = 8;         // conn-estab timer went off, or max retransm. count reached
    NDP_I_STATUS = 9;            // status info (will carry ~NDPStatusInfo)
    NDP_I_SEND_MSG = 10;         // send queue abated, send more messages
    NDP_I_DATA_NOTIFICATION = 11; // notify the upper layer that data has arrived
}


//
// Currently not in use.
//
enum NDPErrorCode
{
}


class NDPCommand
{
    int connId = -1;   // identifies the socket within the application
    int userId = -1;   // id than can be freely used by the app
 
   unsigned int  numRcvTrimmedHeader = 0;   
}


class NDPErrorInfo extends NDPCommand
{
    int errorCode @enum(NDPErrorCode);
    string messageText;
}


class NDPOpenCommand extends NDPCommand
{
    L3Address localAddr; 
    L3Address remoteAddr;
    int localPort = -1;      
    int remotePort = -1;      

    string ndpAlgorithmClass; 
    
    unsigned int priorityValue;
    unsigned int numPacketsToSend;
    bool    isLongFlow;
    bool isSender;
    bool isReceiver;
}



class NDPSendCommand extends NDPCommand
{
}


class NDPConnectInfo extends NDPCommand
{
    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;
}


class NDPStatusInfo extends NDPCommand
{
    int state;
    string stateName;

    L3Address localAddr;
    L3Address remoteAddr;
    int localPort;
    int remotePort;

    unsigned int snd_mss;
  
}


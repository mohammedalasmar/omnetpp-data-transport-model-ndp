 
cplusplus {{
#include <iostream>
#include "inet/common/INETDefs.h"
#include "inet/common/ByteArray.h"

namespace inet {
namespace ndp {
class Sack;
class NDPOption;
typedef NDPOption *NDPOptionPtr;
}
}

}}

namespace inet::ndp;

cplusplus {{
    // default NDP header length: 20 bytes
    #define NDP_HEADER_OCTETS  20    // without options

    // maximum NDP header length (base + options): 60 = 4 * 15 bytes
    const unsigned int NDP_MAX_HEADER_OCTETS = 60;

    // maximum allowed sack entry number, if no other options are used
    const unsigned int MAX_SACK_ENTRIES = 4;

    typedef cPacket *cPacketPtr;

    inline std::ostream& operator<<(std::ostream& os, cPacketPtr msg)
    {
        return os << "(" << msg->getClassName() << ") " << msg->getName() << ": " << msg->info();
    }

    inline void doPacking(cCommBuffer *b, cPacketPtr& msg) {msg->parsimPack(b);}
    inline void doUnpacking(cCommBuffer *b, cPacketPtr& msg) {msg->parsimUnpack(b);}
}}

struct cPacketPtr;

class noncobject ByteArray;

struct NDPPayloadMessage
{
    unsigned int endSequenceNo;
    cPacketPtr msg = nullptr;      // pointer to payload msg
}

//
// NDP Option Numbers
// Reference: http://www.iana.org/assignments/tcp-parameters/
// Date: 2011-07-02
//
// Note: Options not yet implemented should stay commented out
//
enum NDPOptionNumbers
{
    NDPOPTION_END_OF_OPTION_LIST = 0;                   // RFC 793, LENGTH: 1 Byte
    NDPOPTION_NO_OPERATION = 1;                         // RFC 793, LENGTH: 1 Byte
    NDPOPTION_MAXIMUM_SEGMENT_SIZE = 2;                 // RFC 793, LENGTH: 4 Bytes
    NDPOPTION_WINDOW_SCALE = 3;                         // RFC 1323, LENGTH: 3 Bytes
    NDPOPTION_SACK_PERMITTED = 4;                       // RFC 2018, LENGTH: 2 Bytes
    NDPOPTION_SACK = 5;                                 // RFC 2018, LENGTH: N (max. N = 4) 8 * n + 2 Bytes  => 32 + 2 + 2 * NOP = 36 Bytes; If TIMESTAMP option is used with SACK: max. n = 3 => 12 Bytes (for Timestamp) + 28 Bytes (for SACK) = 40 Bytes
    NDPOPTION_TIMESTAMP = 8;                            // RFC 1323, LENGTH: 10 Bytes

};

//
// This structure represents a single SACK (selective acknowledgment):
//
class SackItem
{
    @fieldNameSuffix("_var"); //TODO remove when OMNeT++ 4.x compatibility is no longer required
    unsigned int start;     // start seq no. of sack block
    unsigned int end;       // end seq no. of sack block
}

class Sack extends SackItem
{
    @customize(true);
}

// Header Options (optional):
class noncobject NDPOptionPtr;
class NDPOption
{
    unsigned short kind @enum(NDPOptionNumbers) = -1;  // option kind
    unsigned short length = 1;                    // option length
}

class NDPOptionEnd extends NDPOption
{
    kind = NDPOPTION_END_OF_OPTION_LIST;
    length = 1;
}

class NDPOptionNop extends NDPOption
{
    kind = NDPOPTION_NO_OPERATION;
    length = 1;
}

class NDPOptionMaxSegmentSize extends NDPOption
{
    kind = NDPOPTION_MAXIMUM_SEGMENT_SIZE;
    length = 4;
    uint16_t maxSegmentSize;   // uint16_t
}

class NDPOptionWindowScale extends NDPOption
{
    kind = NDPOPTION_WINDOW_SCALE;
    length = 3;
    unsigned short windowScale;   // uint8_t
}

class NDPOptionSackPermitted extends NDPOption
{
    kind = NDPOPTION_SACK_PERMITTED;
    length = 2;
}

class NDPOptionSack extends NDPOption
{
    kind = NDPOPTION_SACK;
    length = 2;     // 2 + getSackArraySize() * 8
    SackItem sackItem[];
}

class NDPOptionTimestamp extends NDPOption
{
    kind = NDPOPTION_TIMESTAMP;
    length = 10;
    uint32_t   senderTimestamp;
    uint32_t   echoedTimestamp;
}

class NDPOptionUnknown extends NDPOption
{
    kind = -1;
    uint8_t bytes[];
}


packet NDPSegment
{
    @customize(true);
    @fieldNameSuffix("_var"); //TODO remove when OMNeT++ 4.x compatibility is no longer required

    // Source Port
    unsigned short srcPort;

    // Destination Port
    unsigned short destPort;

    // Sequence Number: first sequence number of the first data octet
    // in the respective segment (except if SYN is set; then the the
    // seq. number is the initial seq. number (ISS) and the first data
    // octet is ISS + 1)
//    unsigned int sequenceNo;

    // Acknowledgement Number: if ACK flag is set, this field contains
    // the next sequence number the sender of this segment is expecting
    // to receive
    unsigned int ackNo;

    unsigned int nackNo;

  // Added MOH


   
   bool isHeader;
   bool isPullPacket;
   bool isDataPacket;
   
//   bool isSender;
//   bool isReceiver;
   bool isLongFlow;
   unsigned int priorityValue;
   unsigned int numPacketsToSend;
   
   unsigned int pullSequenceNumber;
   unsigned int dataSequenceNumber;
   bool isLastPktToSend;
   bool ackBit; // ACK: ackNo significant if set
   bool nackBit; // ACK: ackNo significant if set

    // NDP Header Length - default: 20 bytes
    // if header options are used the headerLength is greater than 20 bytes (default)
    unsigned short headerLength = NDP_HEADER_OCTETS; // NDP_HEADER_OCTETS = 20

    bool urgBit; // URG: urgent pointer field significant if set

    
    
    bool pshBit; // PSH: push function
    bool rstBit; // RST: reset the connection
    bool synBit; // SYN: synchronize seq. numbers
    bool finBit; // FIN: finish - no more data from sender

    // Window Size: the number of data octets beginning with the one indicated
    // in the acknowledgement field which the sender of this segment is
    // willing to accept
    unsigned short window;

    // Urgent Pointer: communicates the current value of the urgent pointer
    // as a positive offset from the sequence number in this segment. The
    // urgent pointer points to the sequence number of the octet following
    // the urgent data. This field is only be interpreted in segments with
    // the URG control bit set.
    unsigned short urgentPointer;

    // Header options (optional)
    // Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented
    abstract NDPOptionPtr headerOption[];

    // Payload length in octets (not an actual NDP header field).
    // This may not always be the same as encapsulatedPacket()->getByteLength();
    // e.g. when simulating a virtual data stream there's no encapsulated
    // packet at all.
    unsigned long payloadLength;

    // Message objects (cMessages) that travel in this segment as data.
    // This field is used only when the ~NDPDataTransferMode is NDP_TRANSFER_OBJECT.
    // Every message object is put into the NDPSegment that would (in real life)
    // carry its first octet. That is, if message object 'msg' with length=100 bytes
    // occupies stream offset number range 10000..10099, it will travel in the
    // NDPSegment which carries the octet 10000. This way it is easily achieved
    // that the receiving NDP passes up the message object to its client
    // when the last byte of the message has arrived.
    abstract NDPPayloadMessage payload[];

    // Message bytes that travel in this segment as data.
    // This field is used only when the ~NDPDataTransferMode is NDP_TRANSFER_BYTESTREAM.
    ByteArray byteArray;
}

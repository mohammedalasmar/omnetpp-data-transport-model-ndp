
#ifndef __INET_NDPSegment_H
#define __INET_NDPSegment_H

#include <list>

#include "../../../ndptransportlayer/contract/ITransportPacket.h"
#include "../ndp_common/NDPSegment_m.h"
#include "inet/common/INETDefs.h"

namespace inet {

namespace ndp {

/** @name Comparing sequence numbers */
//@{

// MOH- note
// maximum unsigned long value = 2^31= 2147483648=(1UL << 31)

// if b>a ==> true
inline bool seqLess(uint32 a, uint32 b) { return a != b && (b - a) < (1UL << 31); }
// if b>=a ==> true
inline bool seqLE(uint32 a, uint32 b) { return (b - a) < (1UL << 31); }


// if a>b ==> true
inline bool seqGreater(uint32 a, uint32 b) { return a != b && (a - b) < (1UL << 31); }
// if a>=b ==> true
inline bool seqGE(uint32 a, uint32 b) { return (a - b) < (1UL << 31); }


inline uint32 seqMin(uint32 a, uint32 b) { return ((b - a) < (1UL << 31)) ? a : b; } // returns min(a,b)
inline uint32 seqMax(uint32 a, uint32 b) { return ((a - b) < (1UL << 31)) ? a : b; }// returns max(a,b)
//@}

class INET_API Sack : public Sack_Base
{
  public:
    Sack() : Sack_Base() {}
    Sack(unsigned int start_par, unsigned int end_par) { setSegment(start_par, end_par); }
    Sack(const Sack& other) : Sack_Base(other) {}
    Sack& operator=(const Sack& other) { Sack_Base::operator=(other); return *this; }
    virtual Sack *dup() const override { return new Sack(*this); }
    // ADD CODE HERE to redefine and implement pure virtual functions from Sack_Base
    virtual bool empty() const;
    virtual bool contains(const Sack& other) const;
    virtual void clear();
    virtual void setSegment(unsigned int start_par, unsigned int end_par);
    virtual std::string str() const override;
};

/**
 * Represents a NDP segment. More info in the NDPSegment.msg file
 * (and the documentation generated from it).
 */
class INET_API NDPSegment : public NDPSegment_Base, public ITransportPacket
{
  protected:
    typedef std::list<NDPPayloadMessage> PayloadList;
    PayloadList payloadList;
    typedef std::vector<NDPOption *> OptionList;
    OptionList headerOptionList;

  private:
    void copy(const NDPSegment& other);
    void clean();

  public:
    NDPSegment(const char *name = nullptr, int kind = 0) : NDPSegment_Base(name, kind) {}
    NDPSegment(const NDPSegment& other) : NDPSegment_Base(other) { copy(other); }
    ~NDPSegment();
    NDPSegment& operator=(const NDPSegment& other);
    virtual NDPSegment *dup() const override { return new NDPSegment(*this); }
    virtual void parsimPack(cCommBuffer *b) const override;

    /** Generated but unused method, should not be called. */
    virtual void setPayloadArraySize(unsigned int size) override;

    /** Generated but unused method, should not be called. */
    virtual void setPayload(unsigned int k, const NDPPayloadMessage& payload_var) override;

    /**
     * Returns the number of payload messages in this NDP segment
     */
    virtual unsigned int getPayloadArraySize() const override;

    /**
     * Returns the kth payload message in this NDP segment
     */
    virtual NDPPayloadMessage& getPayload(unsigned int k) override;

    /**
     * Adds a message object to the NDP segment. The sequence number + 1 of the
     * last byte of the message should be passed as 2nd argument
     */
    virtual void addPayloadMessage(cPacket *msg, uint32 endSequenceNo);

    /**
     * Removes and returns the first message object in this NDP segment.
     * It also returns the sequence number + 1 of its last octet in outEndSequenceNo.
     */
    virtual cPacket *removeFirstPayloadMessage(uint32& outEndSequenceNo);

    /**
     * Returns RFC 793 specified SEG.LEN:
     *     SEG.LEN = the number of octets occupied by the data in the segment
     *               (counting SYN and FIN)
     *
     */
    virtual uint32_t getSegLen();


    // manage header options:

    /** Calculate Length of NDP Options Array in bytes */
    virtual unsigned short getHeaderOptionArrayLength();

    /** Generated but unused method, should not be called. */
    virtual void setHeaderOptionArraySize(unsigned int size) override;

    /** Returns the number of NDP options in this NDP segment */
    virtual unsigned int getHeaderOptionArraySize() const override;

    /** Returns the kth NDP options in this NDP segment */
    virtual NDPOptionPtr& getHeaderOption(unsigned int k) override;
    virtual const NDPOptionPtr& getHeaderOption(unsigned int k) const override {return const_cast<NDPSegment*>(this)->getHeaderOption(k);}

    /** Generated but unused method, should not be called. */
    virtual void setHeaderOption(unsigned int k, const NDPOptionPtr& headerOption) override;

    /** Adds a NDP option to the NDP segment */
    virtual void addHeaderOption(NDPOption *headerOption);

    /** Drops all NDP options of the NDP segment */
    virtual void dropHeaderOptions();


    virtual unsigned int getSourcePort() const override { return NDPSegment_Base::getSrcPort(); }
    virtual void setSourcePort(unsigned int port) override { NDPSegment_Base::setSrcPort(port); }
    virtual unsigned int getDestinationPort() const override { return NDPSegment_Base::getDestPort(); }
    virtual void setDestinationPort(unsigned int port) override { NDPSegment_Base::setDestPort(port); }

  protected:

};

} // namespace ndp

} // namespace inet

#endif // ifndef __INET_NDPSegment_H


// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

#include "NDPSegment.h"
namespace inet {
namespace ndp {
Register_Class(Sack);

bool Sack::empty() const
{
    return start_var == 0 && end_var == 0;
}

bool Sack::contains(const Sack& other) const
{
    return seqLE(start_var, other.start_var) && seqLE(other.end_var, end_var);
}

void Sack::clear()
{
    start_var = end_var = 0;
}

void Sack::setSegment(unsigned int start_par, unsigned int end_par)
{
    setStart(start_par);
    setEnd(end_par);
}

std::string Sack::str() const
{
    std::stringstream out;

    out << "[" << start_var << ".." << end_var << ")";
    return out.str();
}

Register_Class(NDPSegment);

uint32_t NDPSegment::getSegLen()
{
    return payloadLength_var + (finBit_var ? 1 : 0) + (synBit_var ? 1 : 0);
}


unsigned short NDPSegment::getHeaderOptionArrayLength()
{
    unsigned short usedLength = 0;

    for (uint i = 0; i < getHeaderOptionArraySize(); i++)
        usedLength += getHeaderOption(i)->getLength();

    return usedLength;
}

NDPSegment& NDPSegment::operator=(const NDPSegment& other)
{
    if (this == &other)
        return *this;
    clean();
    NDPSegment_Base::operator=(other);
    copy(other);
    return *this;
}

void NDPSegment::copy(const NDPSegment& other)
{
    for (const auto & elem : other.payloadList)
        addPayloadMessage(elem.msg->dup(), elem.endSequenceNo);
    for (const auto opt: other.headerOptionList)
        addHeaderOption(opt->dup());
}

NDPSegment::~NDPSegment()
{
    clean();
}

void NDPSegment::clean()
{
//    dropHeaderOptions();

    while (!payloadList.empty()) {
        cPacket *msg = payloadList.front().msg;
        payloadList.pop_front();
        dropAndDelete(msg);
    }
}


void NDPSegment::parsimPack(cCommBuffer *b) const
{
    NDPSegment_Base::parsimPack(b);
    b->pack((int)headerOptionList.size());
    for (const auto opt: headerOptionList) {
        b->packObject(opt);
    }
    b->pack((int)payloadList.size());
    for (PayloadList::const_iterator it = payloadList.begin(); it != payloadList.end(); it++) {
        b->pack(it->endSequenceNo);
        b->packObject(it->msg);
    }
}



void NDPSegment::setPayloadArraySize(unsigned int size)
{
    throw cRuntimeError(this, "setPayloadArraySize() not supported, use addPayloadMessage()");
}

unsigned int NDPSegment::getPayloadArraySize() const
{
    return payloadList.size();
}

NDPPayloadMessage& NDPSegment::getPayload(unsigned int k)
{
    auto i = payloadList.begin();
    while (k > 0 && i != payloadList.end())
        (++i, --k);
    if (i == payloadList.end())
        throw cRuntimeError("Model error at getPayload(): index out of range");
    return *i;
}

void NDPSegment::setPayload(unsigned int k, const NDPPayloadMessage& payload_var)
{
    throw cRuntimeError(this, "setPayload() not supported, use addPayloadMessage()");
}

void NDPSegment::addPayloadMessage(cPacket *msg, uint32 endSequenceNo)
{
    take(msg);
    NDPPayloadMessage payload;
    payload.endSequenceNo = endSequenceNo;
    payload.msg = msg;
    payloadList.push_back(payload);
}

cPacket *NDPSegment::removeFirstPayloadMessage(uint32& endSequenceNo)
{
    if (payloadList.empty())
        return nullptr;

    cPacket *msg = payloadList.front().msg;
    endSequenceNo = payloadList.front().endSequenceNo;
    payloadList.pop_front();
    drop(msg);
    return msg;
}

void NDPSegment::addHeaderOption(NDPOption *option)
{
    headerOptionList.push_back(option);
}

void NDPSegment::setHeaderOptionArraySize(unsigned int size)
{
    throw cRuntimeError(this, "setHeaderOptionArraySize() not supported, use addHeaderOption()");
}

unsigned int NDPSegment::getHeaderOptionArraySize() const
{
    return headerOptionList.size();
}

NDPOptionPtr& NDPSegment::getHeaderOption(unsigned int k)
{
    return headerOptionList.at(k);
}

void NDPSegment::setHeaderOption(unsigned int k, const NDPOptionPtr& headerOption)
{
    throw cRuntimeError(this, "setHeaderOption() not supported, use addHeaderOption()");
}

void NDPSegment::dropHeaderOptions()
{
    for (auto opt : headerOptionList)
        delete opt;
    headerOptionList.clear();
}


} // namespace raptoNDP

} // namespace inet


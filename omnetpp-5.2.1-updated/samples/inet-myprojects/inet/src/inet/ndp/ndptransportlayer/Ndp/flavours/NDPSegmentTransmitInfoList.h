
#ifndef __INET_NDPSEGMENTTRANSMITINFOLIST_H
#define __INET_NDPSEGMENTTRANSMITINFOLIST_H

#include "../../Ndp/flavours/NDPBaseAlg.h"
#include "inet/common/INETDefs.h"


namespace inet {

namespace ndp {

class INET_API NDPSegmentTransmitInfoList
{
  public:
    class Item
    {
      protected:
        uint32_t beg;    // segment [begin, end)
        uint32_t end;
        simtime_t firstSentTime;    // time of first sending
        simtime_t lastSentTime;    // time of last sending
        int transmitCount;    // num of transmissions

      public:
        Item(uint32_t beg, uint32_t end, simtime_t firstTime, simtime_t lastTime, int transmits) : beg(beg), end(end), firstSentTime(firstTime), lastSentTime(lastTime), transmitCount(transmits) {}
        uint32_t getBeg() const { return beg; }
        uint32_t getEnd() const { return end; }
        simtime_t getFirstSentTime() const { return firstSentTime; }
        simtime_t getLastSentTime() const { return lastSentTime; }
        int getTransmitCount() const { return transmitCount; }

        friend class NDPSegmentTransmitInfoList;
    };
    typedef std::list<Item> NDPSegmentTransmitInfoItems;
    NDPSegmentTransmitInfoItems regions;    // region[i].end == region[i+1].beg

  public:
    void set(uint32_t beg, uint32_t end, simtime_t sentTime);    // [beg,end)

    /// returns pointer to Item, or nullptr if not found
    const Item *get(uint32_t seq) const;

    void clearTo(uint32_t endseg);
};

} // namespace NDP

} // namespace inet

#endif // ifndef __INET_NDPSEGMENTTRANSMITINFOLIST_H


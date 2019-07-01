// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

package inet.ndp.ndptransportlayer.Ndp;

import inet.ndp.ndptransportlayer.contract.INdp;

simple Ndp like INdp
{
    parameters:
        int initialWindow = default(0);  // initialWindow size NDP-style (sender pushes IW pacakets)

        bool timestampSupport = default(false); // Timestamps (RFC 1323) support (header option) (TS will be enabled for a connection if both endpoints support it)
        int mss = default(536); // Maximum Segment Size (RFC 793) (header option)
        string ndpAlgorithmClass = default("NDPSimpleAlg"); //   default("RQReno"); // RQSimpleAlg/RQVegas/DumbRQ/ RQReno/RQTahoe/RQNewReno/RQNoCongestionControl/DumbRQ
        bool recordStats = default(true); // recording of seqNum etc. into output vectors enabled/disabled
        string sendQueueClass = default("");    // Obsolete!!!
        string receiveQueueClass = default(""); // Obsolete!!!
        bool useDataNotification = default(false); // turn the notifications for arrived data on or off
        @display("i=block/queue");

        @signal[numRequestsRTOs](type=double);
        @statistic[numRequestsRTOs](title="numRequestsRTOs "; source=numRequestsRTOs; record=vector);


    gates:
        input appIn[] @labels(NDPCommand/down);
        input ipIn @labels(NDPSegment,IPv4ControlInfo/up,IPv6ControlInfo/up);
        output appOut[] @labels(NDPCommand/up);
        output ipOut @labels(NDPSegment,IPv4ControlInfo/down,IPv6ControlInfo/down);
}



package inet.common.queue;
//@namespace(raptorq);
//
// Drop-tail queue, to be used in network interfaces.
// Conforms to the ~IOutputQueue interface.
//
simple NdpPriorityQueue like IOutputQueue
{
    parameters:
        int frameCapacity ; //= default(100);
        string queueNameData = default("L2DataQueue"); // name of the inner cQueue object, used in the 'q' tag of the display string
        string queueNameHeader = default("L2HeadersQueue"); // name of the inner cQueue object, used in the 'q' tag of the display string
        
        
        
        @display("i=block/queue");
        @signal[rcvdPk](type=cPacket);
        @signal[enqueuePk](type=cPacket);
        @signal[dequeuePk](type=cPacket);
        @signal[dropPkByQueue](type=cPacket);
        @signal[queueingTime](type=simtime_t; unit=s);
        @signal[dataQueueLength](type=long);
        @signal[headersQueueLength](type=long);
        @signal[numTrimmedPkt](type=long);
        
        
        
        @statistic[rcvdPk](title="received packets"; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[dropPk](title="dropped packets"; source=dropPkByQueue; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[queueingTime](title="queueing time"; record=histogram,vector; interpolationmode=none);
        @statistic[dataQueueLength](title="queue length"; record=max,timeavg,vector; interpolationmode=sample-hold);
        @statistic[headersQueueLength](title="queue length"; record=max,timeavg,vector; interpolationmode=sample-hold);
        @statistic[numTrimmedPkt](title="num Trimmed Pkt  "; source=numTrimmedPkt; record=last ; interpolationmode=none);
        
    gates:
        input in;
        output out;
}


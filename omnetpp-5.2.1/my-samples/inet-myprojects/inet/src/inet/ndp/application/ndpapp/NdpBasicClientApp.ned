
package inet.ndp.application.ndpapp;

import inet.ndp.application.contract.INdpApp;


simple NdpBasicClientApp like INdpApp
{
    parameters:
        string localAddress = default(""); // may be left empty ("")
        int localPort = default(-1); // port number to listen on
        string connectAddress = default("");  // server address (may be symbolic)
        int connectPort = default(1000); // port number to connect to
//        string dataTransferMode @enum("bytecount","object","bytestream","rqrequests") = default("bytecount");
        double startTime @unit(s) = default(1s); // time first session begins
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, negative values mean forever

       
        double sendBytes @unit(B) =  default(1MiB); 
        int numPacketsToSend;  // if this is a sender
        bool isLongFlow = default(false);  // 
        int priorityValue = default(0);
        bool isSender = default(true); 
        bool isReceiver = default(false);  
        

//         volatile int replyLength @unit(B) = default(1MiB); // length of a reply

        volatile double reconnectInterval @unit(s) = default(30s);  // if connection breaks, waits this much before trying to reconnect
 

        @signal[rcvdPacketSignal](type=cPacket);
        @statistic[rcvdPacketSignal](title="packets received"; source=rcvdPacketSignal; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        //MOH: method2 instantaneous throughputs, see ResultFilter.cc
        @statistic[ndpThroughput](title="ndpThroughput"; source="throughput(rcvdPacketSignal)"; unit=bps; record=mean);

        @display("i=msg/mail;i2=status/down");
    gates:
        input ndpIn @labels(NDPCommand/up);
        output ndpOut @labels(NDPCommand/down);
}


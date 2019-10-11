
package inet.ndp.application.ndpapp;
import inet.ndp.application.contract.INdpApp;

simple NdpSinkApp like INdpApp
{
    parameters:
        volatile string localAddress = default(""); // may be left empty ("")
        volatile int localPort; // port number to listen on
         @display("i=block/sink");


        int multiCastGroupId = default(-1);
        int multiSrcGroupId = default(-1);
 
        // moh
        bool isLongFlow = default(false);
        
       @signal[numRcvTrimmedHeaderSigNdp](type=double);
        @statistic[numRcvTrimmedHeaderSigNdp](title="numRcvTrimmedHeaderNdp"; source=numRcvTrimmedHeaderSigNdp; unit=s; record=last);
           
        @signal[multicastGroupIdSignal](type=double);
        @statistic[multicastGroupIdSignal](title="multicastGroupIdSignal "; source=multicastGroupIdSignal; unit=s; record=last);

        @signal[multisourceGroupIdSignal](type=double);
        @statistic[multisourceGroupIdSignal](title="multisourceGroupIdSignal "; source=multisourceGroupIdSignal; unit=s; record=last);


        @signal[fctRecordv3](type=double);
        @statistic[fctRecordv3](title="TCP Sesssion's flow completion time"; source=fctRecordv3; unit=s; record=last);

        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets (symbols) received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

         // MOH: FCT using ResultFilter.cc (messageAge)
//       @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);

        @statistic[mohThroughputNDP](title="mohThroughputNDP"; source="throughput(rcvdPk)"; unit=bps; record=mean);


    gates:
        input ndpIn @labels(NDPCommand/up);
        output ndpOut @labels(NDPCommand/down);
}


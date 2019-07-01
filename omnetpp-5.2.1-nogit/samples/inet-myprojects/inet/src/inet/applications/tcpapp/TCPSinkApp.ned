//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


package inet.applications.tcpapp;

import inet.applications.contract.ITCPApp;


//
// Accepts any number of incoming TCP connections, and discards whatever
// arrives on them.
// Compatible with both ~IPv4 and ~IPv6.
//
// <b>Configuring App</b>
//
// The module parameter dataTransferMode should be set the transfer mode in TCP layer.
// Currently you have three choices:
//
//   -# set them to "bytecount".
//      This mode manages "virtual bytes", that is, only byte counts are
//      transmitted over the TCP connection and no actual data. cMessage
//      contents, and even message boundaries are not preserved with these
//      classes: for example, if the client sends a single cMessage with
//      length = 1 megabyte over TCP, the receiver-side client will see a
//      sequence of MSS-sized messages.
//
//   -# use "object", which transmits
//      cMessage objects (and subclasses) over a TCP connection. The same
//      message object sequence that was sent by the client to the
//      sender-side TCP entity will be reproduced on the receiver side.
//      If a client sends a cMessage with length = 1 megabyte, the
//      receiver-side client will receive the same message object (or a clone)
//      after the TCP entities have completed simulating the transmission
//      of 1 megabyte over the connection. This is a different behaviour
//      from TCPVirtualDataSendQueue/RcvQueue.
//      This mode is not implemented in ~TCP_NSC yet.
//
//   -# use "bytestream", which transmits real bytes of messages.
//
simple TCPSinkApp like ITCPApp
{
    parameters:
        volatile string localAddress = default(""); // may be left empty ("")
        volatile int localPort = default(1000); // port number to listen on
        string dataTransferMode @enum("bytecount","object","bytestream") = default("bytecount");
        @display("i=block/sink");

        // moh
        bool isLongFlow = default(false);
        
        
        int multiCastGroupId = default(-1);
        int multiSrcGroupId = default(-1);

        @signal[multicastGroupIdSignalTcp](type=double);
        @statistic[multicastGroupIdSignalTcp](title="multicastGroupIdSignal "; source=multicastGroupIdSignalTcp; unit=s; record=last);

        @signal[multisourceGroupIdSignalTcp](type=double);
        @statistic[multisourceGroupIdSignalTcp](title="multisourceGroupIdSignalTcp "; source=multisourceGroupIdSignalTcp; unit=s; record=last);



        // MOH: method1 goodput using my signals 
//        @signal[throughputRecordv1](type=double);
//        @statistic[throughputRecordv1](title="TCP Sesssion's overall throughput"; source=throughputRecordv1;unit=bps; record=last); 

         // MOH: FCT using my signals 
        @signal[fctRecordv1](type=double);
        @statistic[fctRecordv1](title="TCP Sesssion's flow completion time"; source=fctRecordv1; unit=s; record=last);

        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);

         // MOH: FCT using ResultFilter.cc (messageAge)
//        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);

        //MOH: method2 instantaneous throughputs, see ResultFilter.cc
        @statistic[mohThroughput](title="mohThroughput"; source="throughput(rcvdPk)"; unit=bps; record=mean);


    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}


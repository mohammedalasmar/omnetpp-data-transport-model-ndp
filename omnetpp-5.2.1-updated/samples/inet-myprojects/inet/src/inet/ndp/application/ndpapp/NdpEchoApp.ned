// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019



package inet.ndp.application.ndpapp;

import inet.ndp.application.contract.INdpApp;

simple NdpEchoApp like INdpApp
{
    parameters:
        string localAddress = default(""); // local address; may be left empty ("")
        int localPort; // port number to listen on
        double echoFactor = default(1);
        double echoDelay @unit(s) = default(0s);
        string dataTransferMode @enum("bytecount","object","bytestream") = default("bytecount");
        @display("i=block/app");
        @signal[sentPk](type=cPacket);
        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
    gates:
        input ndpIn @labels(NDPCommand/up);
        output ndpOut @labels(NDPCommand/down);
}




package inet.ndp;

import inet.ndp.ndptransportlayer.contract.INdp;
import inet.ndp.application.contract.INdpApp;

import inet.transportlayer.contract.ITCP;

import inet.applications.contract.IPingApp;
import inet.applications.contract.ISCTPApp;
import inet.applications.contract.ITCPApp;
import inet.applications.contract.IUDPApp;
import inet.transportlayer.contract.ISCTP;
import inet.transportlayer.contract.ITCP;
import inet.transportlayer.contract.IUDP;
import inet.applications.contract.ITunApp;


module StandardHostNdp extends NodeBase
{
    parameters:
        @display("i=device/pc2;bgb=939,470");
        int numTcpApps = default(0);  // no of TCP apps. Specify the app types in INI file with tcpApp[0..1].typename="TCPEchoApp" syntax
        int numUdpApps = default(0);  // no of UDP apps. Specify the app types in INI file with udpApp[0..1].typename="UDPVideoStreamCli" syntax
        int numSctpApps = default(0); // no of SCTP apps. Specify the app types in INI file with sctpApp[0..1].typename="SCTPServer" syntax
        int numPingApps = default(0);  // no of PING apps. Specify the app types in INI file with pingApp[0..1].typename="PingApp" syntax
        bool hasTcp = default(numTcpApps > 0);
        bool hasUdp = default(numUdpApps > 0);
        bool hasSctp = default(numSctpApps > 0);
        bool hasTun = default(numTunInterfaces > 0);
        string tcpType = default(firstAvailableOrEmpty("TCP", "TCP_lwIP", "TCP_NSC"));  // tcp implementation (e.g. ~TCP, ~TCP_lwIP, ~TCP_NSC) or ~TCPSpoof
        string udpType = default(firstAvailableOrEmpty("UDP"));
        string sctpType = default(firstAvailableOrEmpty("SCTP"));
        forwarding = default(false);  // disable routing by default
        networkLayer.proxyARP = default(false);

        ///////////// ndp  
        int numNdpApps = default(0);
        bool hasNdp = default(numNdpApps > 0);
        string ndpType = default(firstAvailableOrEmpty("Ndp"));
        /////////////  
 
    submodules:
        tunApp[numTunInterfaces]: <> like ITunApp {
            parameters:
                @display("p=168,42");
        }
        tcpApp[numTcpApps]: <> like ITCPApp {
            parameters:
                @display("p=319,42,row,60");
        }
        tcp: <tcpType> like ITCP if hasTcp {
            parameters:
                @display("p=291,141");
        }
        udpApp[numUdpApps]: <> like IUDPApp {
            parameters:
                @display("p=463,42,row,60");
        }
        udp: <udpType> like IUDP if hasUdp {
            parameters:
                @display("p=393,141");
        }
        sctpApp[numSctpApps]: <> like ISCTPApp {
            parameters:
                @display("p=840,42,row,60");
        }
        sctp: <sctpType> like ISCTP if hasSctp {
            @display("p=738,178");
        }
        pingApp[numPingApps]: <default("PingApp")> like IPingApp {
            parameters:
                @display("p=651,269,row,60");
        }

        ///////////// ndp
        ndp: <ndpType> like INdp if hasNdp {
            @display("p=573,140;i=abstract/penguin");
        }

        ndpApp[numNdpApps]: <> like INdpApp {
            @display("p=651,42,r,30");
        }
        /////////////  

    connections allowunconnected:
        for i=0..numTcpApps-1 {
            tcpApp[i].tcpOut --> tcp.appIn++;
            tcpApp[i].tcpIn <-- tcp.appOut++;
        }

        tcp.ipOut --> networkLayer.transportIn++ if hasTcp;
        tcp.ipIn <-- networkLayer.transportOut++ if hasTcp;

        for i=0..numUdpApps-1 {
            udpApp[i].udpOut --> udp.appIn++;
            udpApp[i].udpIn <-- udp.appOut++;
        }

        udp.ipOut --> networkLayer.transportIn++ if hasUdp;
        udp.ipIn <-- networkLayer.transportOut++ if hasUdp;

        for i=0..numSctpApps-1 {
            sctpApp[i].sctpOut --> sctp.from_appl++;
            sctp.to_appl++ --> sctpApp[i].sctpIn;
        }
        sctp.to_ip --> networkLayer.transportIn++ if hasSctp;
        networkLayer.transportOut++ --> sctp.from_ip if hasSctp;

        for i=0..numPingApps-1 {
            networkLayer.pingOut++ --> pingApp[i].pingIn;
            networkLayer.pingIn++ <-- pingApp[i].pingOut;
        }

        for i=0..numTunInterfaces-1 {
            tunApp[i].tunOut --> tun[i].appIn if hasTun;
            tunApp[i].tunIn <-- tun[i].appOut if hasTun;
        }


        ///////////// 
        for i=0..numNdpApps-1 {
            ndpApp[i].ndpOut --> ndp.appIn++;
            ndpApp[i].ndpIn <-- ndp.appOut++;
        }

        ndp.ipOut --> networkLayer.transportIn++ if hasNdp;
        ndp.ipIn <-- networkLayer.transportOut++ if hasNdp;

}

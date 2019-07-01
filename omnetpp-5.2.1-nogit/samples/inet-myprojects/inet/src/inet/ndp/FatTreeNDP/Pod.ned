
package inet.ndp.FatTreeNDP;

import ned.DatarateChannel;
import ned.IdealChannel;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.EtherLink;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;
import inet.node.ethernet.Eth10M;
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.ndp.StandardHostNdp;


module Pod
{
    parameters:
        @Pod;
        // We get value from FatTree module.
        int k;
        int position;
        int khalf = k/2;

        @display("bgb=260,254");
    gates:
        // As many gates as core routers.
        inout podg[(k/2)^2];

    types:
        channel ethernetline extends DatarateChannel
        {
            delay = 1us;
            //        datarate = 100Mbps;
            datarate = 1Gbps;
        }

    submodules:
        // k/2 racks are in one pod.
        racks[k/2]: Rack {
            // Reach values down.
            k = k;
            position = index;
            @display("p=80,160,r,120");
            @display("i=device/server2");
        }

		// Also k/2 aggregation routers in one pod.
        aggRouters[k/2]: Router {
            @display("p=80,100,m,$k,120,150");
        }
    //          configurator: IPv4NetworkConfigurator;

    connections:
        // Connect a rack with all aggregation routers. Do it for all racks.
        for i=0..sizeof(racks)-1, for j=0..sizeof(aggRouters)-1 {
            racks[i].rackg++ <--> ethernetline <--> aggRouters[j].pppg++;
        }

		// Connect the aggregation routers with the compound ports.
        for i=0..sizeof(aggRouters)-1, for j=0..khalf-1 {
            aggRouters[i].pppg++ <--> IdealChannel { @display("p=100,100,r,deltaX"); } <--> podg++;
        }
}

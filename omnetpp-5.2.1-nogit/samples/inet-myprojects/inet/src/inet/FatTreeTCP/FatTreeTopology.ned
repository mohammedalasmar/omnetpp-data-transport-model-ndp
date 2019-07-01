
package inet.FatTreeTCP;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth100M;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

import ned.DatarateChannel;
import ned.IdealChannel;


network FatTreeTopology
{
    parameters:
        // Only even values are allowed.
        int k = default(4);

        // Value for display string needed.
        int khalf = k/2;
        int kCore = (k/2)^2;

        @display("bgb=2743.2124,1290.1525,white");

    types:
        channel ethernetline extends DatarateChannel
        {
            delay = 20us;
            datarate = 1Gbps;
        }

    submodules:
        // A k-ary fattree consists of k pods.
        Pod[k]: Pod {
            // Reach values down.
            k = k;
            //@display("p=100,160,c,80");
            @display("p=336.50748,425.78497,r,120");
            @display("i=device/server");
            position = index;
        }

		// (k/2)^2 core routers.
        CoreRouter[(k/2)^2]: Router {
            //   k = k;
            //          position = index;
            @display("p=337.736,87.024,m,$kCore,120,150");
         //   @display("p=274.176,103.824005;is=vl");

        }


        visualizer: IntegratedCanvasVisualizer {

            //configurator: FatTreeConfigurator;
            @display("p=1179.675,672.2275");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=1314.495,672.2275");
        }
        centralSchedulerTCP: CentralSchedulerTCP {
            @display("p=724.52124,975.18494;i=abstract/person,#17FF39;b=,,rect;is=vl;t=Central flow scheduler");
        }
    connections:


        for i=0..k-1, for j=0..sizeof(CoreRouter)-1 {
            Pod[i].podg++ <--> ethernetline <--> CoreRouter[j].pppg++;
        }

        // Core routers are connected with the Network Controller.
}



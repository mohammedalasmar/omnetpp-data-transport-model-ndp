// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

package inet.ndp.FatTreeNDP;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.ndp.StandardHostNdp;
import inet.node.inet.Router;
import inet.node.ethernet.Eth100M;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

import ned.DatarateChannel;
import ned.IdealChannel;


network FatTreeNdp
{
    parameters:
        // Only even values are allowed.
        int k = default(4);

        // Value for display string needed.
        int khalf = k/2;
        int kCore = (k/2)^2;

        @display("bgb=808.92,739.6375,white");

    types:
        channel ethernetline extends DatarateChannel
        {
            delay = 1us;
            datarate = 1Gbps; // link speed
        }

    submodules:
        // A k-ary fattree consists of k pods.
        Pod[k]: Pod {
            // Reach values down.
            k = k;
            //@display("p=100,160,c,80");
            @display("p=347.06,324.268,r,120");
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
            @display("p=134.81999,672.2275");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=264.0225,672.2275");
        }
        centralSchedulerNdp: CentralSchedulerNdp {
            @display("p=204.1025,249.0425;i=abstract/person,#17FF39;b=,,rect;is=vl;t=Central flow scheduler");
        }
    //        multicastOrganiser: multicastOrganiser {
    //            @display("p=385.735,601.0725");
    //        }
    connections:


        for i=0..k-1, for j=0..sizeof(CoreRouter)-1 {
            Pod[i].podg++ <--> ethernetline <--> CoreRouter[j].pppg++;
        }

        // Core routers are connected with the Network Controller.
}



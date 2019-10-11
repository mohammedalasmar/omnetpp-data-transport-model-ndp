


package simpletcpexample;

import inet.common.figures.DelegateSignalConfigurator;
import inet.common.misc.SignalSource;


import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth100M;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
//import inet.visualizer.base.RouteVisualizerBase;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

import ned.DatarateChannel;
import ned.IdealChannel;




network FatTreeKFour
{
    parameters:

        @display("bgb=3255.3042,1530.698");
    types:


    submodules:
        // A network controller. Creates messages and gives them
        // out to the network.
        //        Controller: ECMPController {
        //            k = k;
        //            //numtgs = numtgs;
        //            numHttpClients = httpclients;
        //            numFtpClients = ftpclients;
        //            @display("p=250,30");
        //            @display("i=block/control");
        //        }
        visualizer: IntegratedCanvasVisualizer {

            //configurator: FatTreeConfigurator;
            @display("p=349.622,1448.4341");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=114.582,1448.4341");
        }

                 //="server";

        sender1: StandardHost {







            @display("p=91.078,1172.2621");
        }
        Pod0Edge1: Router {
            @display("p=185.09401,819.702");
        }
        sender2: StandardHost {
            @display("p=261.482,1172.2621");
        }
        Pod0Agg2: Router {
            @display("p=487.708,514.15");
        }
        sender3: StandardHost {
            @display("p=461.26602,1172.2621");
        }
        Pod0Edge2: Router {
            @display("p=520.026,819.702");
        }
        sender4: StandardHost {
            @display("p=634.60803,1172.2621");
        }
        Pod0Agg1: Router {
            @display("p=208.598,520.026");
        }
        core2: Router {
            @display("p=1157.572,76.388");
        }
        core1: Router {
            @display("p=652.236,76.388");
        }
        core4: Router {
            @display("p=2077.166,76.388");
        }
        core3: Router {
            @display("p=1657.0321,76.388");
        }
        sender5: StandardHost {
            @display("p=854.958,1172.2621");
        }
        sender7: StandardHost {
            @display("p=1233.9601,1172.2621");
        }
        Pod1Edge1: Router {
            @display("p=951.91205,819.702");
        }
        Pod1Agg2: Router {
            @display("p=1260.4021,528.84");
        }
        Pod1Edge2: Router {
            @display("p=1292.7201,831.45404");
        }
        Pod1Agg1: Router {
            @display("p=969.54004,517.088");
        }
        sender6: StandardHost {
            @display("p=1028.3,1172.2621");
        }
        sender8: StandardHost {
            @display("p=1407.302,1172.2621");
        }
        sender9: StandardHost {
            @display("p=1612.962,1172.2621");
        }
        sender11: StandardHost {
            @display("p=1997.8401,1172.2621");
        }
        Pod2Edge1: Router {
            @display("p=1727.5441,831.45404");
        }
        Pod2Agg2: Router {
            @display("p=1997.8401,528.84");
        }
        Pod2Edge2: Router {
            @display("p=2021.3441,831.45404");
        }
        Pod2Agg1: Router {
            @display("p=1759.862,520.026");
        }
        sender10: StandardHost {
            @display("p=1795.118,1172.2621");
        }
        sender12: StandardHost {
            @display("p=2191.748,1172.2621");
        }
        sender13: StandardHost {
            @display("p=2429.726,1172.2621");
        }
        sender15: StandardHost {
            @display("p=2814.604,1172.2621");
        }
        Pod3Edge1: Router {
            @display("p=2473.7961,819.702");
        }
        Pod3Agg2: Router {
            @display("p=2752.906,520.026");
        }
        Pod3Edge2: Router {
            @display("p=2788.162,819.702;i=,red");
        }
        Pod3Agg1: Router {
            @display("p=2497.3,528.84");
        }
        sender14: StandardHost {
            @display("p=2623.634,1172.2621");
        }
        server: StandardHost {
            @display("p=3020.2642,1172.2621;i=device/mainframe");
        }





    connections:

        sender1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender2.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender4.pppg++;
        sender3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge2.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg2.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core2.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg2.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender6.pppg++;
        sender5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge1.pppg++;
        sender7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge2.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender8.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg2.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender10.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender12.pppg++;
        sender9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Edge1.pppg++;
        sender11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Edge2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg1.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg1.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg2.pppg++;
        sender15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Edge2.pppg++;
        sender13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Edge1.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> sender14.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> server.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Agg2.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Agg1.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Agg1.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod3Agg2.pppg++;
        Pod1Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        Pod1Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core2.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg2.pppg++;
        Pod2Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg1.pppg++;
        Pod2Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod2Agg2.pppg++;
        Pod3Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        Pod3Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core2.pppg++;
        Pod3Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        Pod3Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
}



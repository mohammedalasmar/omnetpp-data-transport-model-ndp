


package fattree;

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


        @display("bgb=2306.1401,1465.0012");
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
            @display("p=1305.8087,1340.2288");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=970.21375,1340.2288");
        }

                 //="server";

        host1: StandardHost {







            @display("p=62.38625,677.64374");
        }
        Pod0Edge1: Router {
            @display("p=122.621254,511.9975");
        }
        host2: StandardHost {
            @display("p=185.0075,677.64374");
        }
        Pod0Agg2: Router {
            @display("p=402.28375,361.41");
        }
        host3: StandardHost {
            @display("p=299.02374,694.85376");
        }
        Pod0Edge2: Router {
            @display("p=402.28375,535.66125");
        }
        host4: StandardHost {
            @display("p=423.79626,694.85376");
        }
        Pod0Agg1: Router {
            @display("p=122.621254,367.86374");
        }
        core2: Router {
            @display("p=770.1475,79.59625");
        }
        core1: Router {
            @display("p=147,81");
        }
        core4: Router {
            @display("p=1688.7313,79.59625");
        }
        core3: Router {
            @display("p=1269.2375,79.59625");
        }
        host5: StandardHost {
            @display("p=565.77875,694.85376");
        }
        host7: StandardHost {
            @display("p=811.02124,677.64374");
        }
        Pod1Edge1: Router {
            @display("p=666.8875,535.66125");
        }
        Pod1Agg2: Router {
            @display("p=978.8188,372.16626");
        }
        Pod1Edge2: Router {
            @display("p=942.2475,535.66125");
        }
        Pod1Agg1: Router {
            @display("p=688.4,361.41");
        }
        host6: StandardHost {
            @display("p=686.2488,677.64374");
        }
        host8: StandardHost {
            @display("p=927.1888,677.64374");
        }
        host9: StandardHost {
            @display("p=1060.5663,677.64374");
        }
        host11: StandardHost {
            @display("p=1396.1613,694.85376");
        }
        Pod2Edge1: Router {
            @display("p=1226.2125,511.9975");
        }
        Pod2Agg2: Router {
            @display("p=1480.06,378.62");
        }
        Pod2Edge2: Router {
            @display("p=1480.06,535.66125");
        }
        Pod2Agg1: Router {
            @display("p=1241.2712,372.16626");
        }
        host10: StandardHost {
            @display("p=1226.2125,677.64374");
        }
        host12: StandardHost {
            @display("p=1514.48,694.85376");
        }
        host13: StandardHost {
            @display("p=1652.16,677.64374");
        }
        server: StandardHost {
            @display("p=1968.3938,677.64374");
        }
        Pod3Edge1: Router {
            @display("p=1781.235,535.66125");
        }
        Pod3Agg2: Router {
            @display("p=2037.2338,361.41");
        }
        Pod3Edge2: Router {
            @display("p=2052.2925,501.24124");
        }
        Pod3Agg1: Router {
            @display("p=1781.235,367.86374");
        }
        host14: StandardHost {
            @display("p=1804.8988,662.585");
        }
        host16: StandardHost {
            @display("p=2099.62,677.64374");
        }





    connections:

        host1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Edge1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host2.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host4.pppg++;
        host3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Edge2.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Agg1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Agg2.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core1.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core2.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core3.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core4.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Agg2.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod0Agg1.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host6.pppg++;
        host5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Edge1.pppg++;
        host7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Edge2.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host8.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Agg2.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Agg2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host10.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host12.pppg++;
        host9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Edge1.pppg++;
        host11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Edge2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg2.pppg++;
        Pod2Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg1.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg1.pppg++;
        Pod2Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg2.pppg++;
        server.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Edge2.pppg++;
        host13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Edge1.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host14.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> host16.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Agg2.pppg++;
        Pod3Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Agg1.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Agg1.pppg++;
        Pod3Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod3Agg2.pppg++;
        Pod1Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core1.pppg++;
        Pod1Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core2.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core4.pppg++;
        core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod1Agg2.pppg++;
        Pod2Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core1.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg1.pppg++;
        Pod2Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core3.pppg++;
        core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> Pod2Agg2.pppg++;
        Pod3Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core1.pppg++;
        Pod3Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core2.pppg++;
        Pod3Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core3.pppg++;
        Pod3Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0ms; } <--> core4.pppg++;
}



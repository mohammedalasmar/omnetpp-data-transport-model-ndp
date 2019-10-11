
package fattree.staticRoutingExamples;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.networklayer.contract.INetworkLayer;
import inet.node.inet.StandardHost;
import inet.node.inet.Router;
import inet.node.ethernet.Eth100M;

import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;

import ned.DatarateChannel;
import ned.IdealChannel;


network StaticRouting2
{
    parameters:


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
            @display("p=710.696,277.648");
        }
        configurator: IPv4NetworkConfigurator;
        client1: StandardHost {
            @display("p=31,457");
        }
        routerAgg2: Router {
            @display("p=558,295");
        }
        routerAgg1: Router {
            @display("p=82.88,277.648");
        }
        routerCore1: Router {
            @display("p=123.284,137.788");
        }
        routerCore2: Router {
            @display("p=270,137");
        }
        server: StandardHost {
            @display("p=597,418");
        }
        routerCore3: Router {
            @display("p=411,137");
        }
        routerCore4: Router {
            @display("p=531,137");
        }
        client2: StandardHost {
            @display("p=138,448");
        }
        client3: StandardHost {
            @display("p=252,442");
        }
    connections:

        routerAgg1.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerCore1.pppg++;
        client1.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerAgg1.pppg++;
        routerAgg1.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerCore2.pppg++;
        routerAgg2.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerCore2.pppg++;
        routerAgg2.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerCore1.pppg++;
        routerCore3.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerAgg1.pppg++;
        routerCore4.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <-->  routerAgg1.pppg++;
        routerAgg2.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerCore4.pppg++;
        routerCore3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <-->  routerAgg2.pppg++;
        client2.pppg++ <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <-->  routerAgg1.pppg++;
        client3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> routerAgg1.pppg++;
        routerAgg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> server.pppg++;
}



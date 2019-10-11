
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


network StaticRouting3
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
            @display("p=970,544");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=982,601");
        }
        client1: StandardHost {
            @display("p=73,552");
        }
        Agg3: Router {
            @display("p=570,308");
        }
        Agg1: Router {
            @display("p=73,308");
        }
        Core1: Router {
            @display("p=123.284,137.788");
        }
        Core2: Router {
            @display("p=270,137");
        }
        server: StandardHost {
            @display("p=792,552");
        }
        Core3: Router {
            @display("p=411,137");
        }
        Core4: Router {
            @display("p=531,137");
        }
        Edge1: Router {
            @display("p=73,418");
        }
        Agg2: Router {
            @display("p=151,308");
        }
        Edge2: Router {
            @display("p=609,430");
        }
        client2: StandardHost {
            @display("p=151,552");
        }
        client3: StandardHost {
            @display("p=231,552");
        }
        client4: StandardHost {
            @display("p=309,552");
        }
        client5: StandardHost {
            @display("p=372,552");
        }
        client6: StandardHost {
            @display("p=435,552");
        }
        client7: StandardHost {
            @display("p=502,552");
        }
        client8: StandardHost {
            @display("p=564,552");
        }
        client9: StandardHost {
            @display("p=609,552");
        }
        client10: StandardHost {
            @display("p=670,552");
        }
        Core5: Router {
            @display("p=655,137");
        }
        Core6: Router {
            @display("p=792,137");
        }
        Agg5: Router {
            @display("p=246,308");
        }
    connections:

        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core1.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core2.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core4.pppg++;
        Core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core4.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core3.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client1.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        server.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        client2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        client3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client4.pppg++;
        client5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client6.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client7.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client8.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client9.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core6.pppg++;
        Core5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Core5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Core6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> Agg3.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> Core1.pppg++;
}




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


network StaticRouting4
{
    parameters:


        @display("bgb=1413,927");
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
            @display("p=907,624");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=988,624");
        }
        client1: StandardHost {
            @display("p=73,552");
        }
        Agg3: Router {
            @display("p=709,308");
        }
        Agg1: Router {
            @display("p=73,308");
        }
        Core1: Router {
            @display("p=285,137");
        }
        server: StandardHost {
            @display("p=792,552");
        }
        Core2: Router {
            @display("p=411,137");
        }
        Core3: Router {
            @display("p=531,137");
        }
        Edge1: Router {
            @display("p=73,418");
        }
        Agg2: Router {
            @display("p=254,304");
        }
        Agg4: Router {
            @display("p=551,308");
        }
        Edge2: Router {
            @display("p=776,442");
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
        Core4: Router {
            @display("p=648,137");
        }
        Core5: Router {
            @display("p=753,137");
        }
        Core6: Router {
            @display("p=838,137");
        }
        Core7: Router {
            @display("p=932,137");
        }
        Core8: Router {
            @display("p=1046,137");
        }
        Core9: Router {
            @display("p=1131,137");
        }
        Core10: Router {
            @display("p=1225,137");
        }
    connections:

        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core3.pppg++;
        Core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core3.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core2.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client1.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
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
        client10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core4.pppg++;
        Core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core5.pppg++;
        Core5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core6.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core7.pppg++;
        Core6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Core7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core8.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core9.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core10.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core8.pppg++;
        Core9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core10.pppg++;
        Core1.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg2.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core1.pppg++;
}




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


network StaticRouting5
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
            @display("p=84,550");
        }
        Agg4: Router {
            @display("p=663,308");
        }
        Agg1: Router {
            @display("p=73,308");
        }
        Core1: Router {
            @display("p=178,113");
        }
        server: StandardHost {
            @display("p=887,541");
        }
        Edge1: Router {
            @display("p=73,442");
        }
        Agg2: Router {
            @display("p=154,308");
        }
        Edge2: Router {
            @display("p=876,435");
        }
        Agg3: Router {
            @display("p=264,308");
        }
        Core2: Router {
            @display("p=234,113");
        }
        Core3: Router {
            @display("p=297,113");
        }
        Core4: Router {
            @display("p=410,113");
        }
        Core5: Router {
            @display("p=466,113");
        }
        Core6: Router {
            @display("p=529,113");
        }
        Core7: Router {
            @display("p=634,113");
        }
        Core8: Router {
            @display("p=690,113");
        }
        Core9: Router {
            @display("p=753,113");
        }
        Agg5: Router {
            @display("p=743,308");
        }
        Agg6: Router {
            @display("p=821,308");
        }
        Edge3: Router {
            @display("p=160,442");
        }
        Edge4: Router {
            @display("p=264,442");
        }
        Edge5: Router {
            @display("p=673,435");
        }
        Edge6: Router {
            @display("p=771,435");
        }
    connections:

        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client1.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        server.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core1.pppg++;
        Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core2.pppg++;
        Core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg1.pppg++;
        Core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core5.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core6.pppg++;
        Core7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Core8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core9.pppg++;
        Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg6.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core1.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core2.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core3.pppg++;
        Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core4.pppg++;
        Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core5.pppg++;
        Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core6.pppg++;
        Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core7.pppg++;
        Core8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg6.pppg++;
        Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core9.pppg++;
        Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg1.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge3.pppg++;
        Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge3.pppg++;
        Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg1.pppg++;
        Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg6.pppg++;
        Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg4.pppg++;
        Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg6.pppg++;
        Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg5.pppg++;
        Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg4.pppg++;
}



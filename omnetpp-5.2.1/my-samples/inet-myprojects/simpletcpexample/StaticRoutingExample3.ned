
package simpletcpexample;
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
            @display("p=710.696,277.648");
        }
        configurator: IPv4NetworkConfigurator;
        client1: StandardHost {
            @display("p=15,636");
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
            @display("p=254,304");
        }
        Agg4: Router {
            @display("p=463,304");
        }
        Edge2: Router {
            @display("p=609,430");
        }
        client2: StandardHost {
            @display("p=93,636");
        }
        client3: StandardHost {
            @display("p=173,636");
        }
        client4: StandardHost {
            @display("p=251,636");
        }
        client5: StandardHost {
            @display("p=314,636");
        }
        client6: StandardHost {
            @display("p=377,636");
        }
        client7: StandardHost {
            @display("p=444,636");
        }
        client8: StandardHost {
            @display("p=506,636");
        }
        client9: StandardHost {
            @display("p=551,636");
        }
        client10: StandardHost {
            @display("p=338,491");
        }
        Edge11: Router {
            @display("p=262,418");
        }
        Edge22: Router {
            @display("p=463,424");
        }
        client11: StandardHost {
            @display("p=424,499");
        }
        client12: StandardHost {
            @display("p=648,552");
        }
        client13: StandardHost {
            @display("p=551,499");
        }
        client14: StandardHost {
            @display("p=483,499");
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
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core2.pppg++;
        Agg4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Core1.pppg++;
        server.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge2.pppg++;
        client2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        client3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client4.pppg++;
        client5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge1.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client6.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client7.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client8.pppg++;
        Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> client9.pppg++;
        Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg1.pppg++;
        Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg2.pppg++;
        Edge22.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg4.pppg++;
        Edge22.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Agg3.pppg++;
        Edge11.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> client10.pppg++;
        client11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; } <--> Edge11.pppg++;
        Edge22.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> client14.pppg++;
        Edge22.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> client13.pppg++;
        Edge2.pppg++  <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 0.001ms; }<--> client12.pppg++;
}




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


network StaticRouting
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
        client: StandardHost {
            @display("p=100.492,409.22");
        }
        router4: Router {
            @display("p=492.1,290.08");
        }
        router1: Router {
            @display("p=82.88,277.648");
        }
        router2: Router {
            @display("p=123.284,137.788");
        }
        router3: Router {
            @display("p=427.868,127.428");
        }
        server: StandardHost {
            @display("p=481.74,409.22");
        }
    connections:

        router1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router2.pppg++;
        client.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router1.pppg++;
        router1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router3.pppg++;
        router2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router3.pppg++;
        router4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router3.pppg++;
        router4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> server.pppg++;
        router4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> router2.pppg++;
}



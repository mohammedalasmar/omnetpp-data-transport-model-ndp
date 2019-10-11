package incast;


import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.ethernet.Eth10G;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import inet.common.misc.ThruputMeteringChannel;

network Incast
{
    parameters:
        int numNodes;

    types:
        channel fiberline extends ThruputMeteringChannel
        {
            per = 0;
            delay = 0;
            datarate = 1000Mbps;
          //  thruputDisplayFormat = "u";
        }
        channel ethernetline extends ThruputMeteringChannel
        {
            per = 0;
            delay = 0;
            datarate = 1000Mbps;
          //  thruputDisplayFormat = "u";
        }

        channel C extends DatarateChannel
        {
            datarate = 100Mbps;
            delay = 0.1us;
        }


    submodules:
        client[numNodes]: StandardHost {
            @display("p=255,71");
        }
        server: StandardHost {
            parameters:
                @display("p=131,247;i=device/server2");
        }
        router: Router {
            parameters:
                @display("p=201,187");
        }
        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=62,119");
        }

    connections:
        server.pppg++ <--> ethernetline <--> router.pppg++;
        for i=0..numNodes-1 {
            client[i].pppg++ <--> fiberline <--> router.pppg++;
        }

}


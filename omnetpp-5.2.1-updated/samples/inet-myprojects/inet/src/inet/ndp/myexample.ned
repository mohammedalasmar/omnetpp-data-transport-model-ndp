

package inet.ndp;

@namespace(inet);
@namespace(ndp);


import inet.ndp.StandardHostNdp;
import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.node.inet.Router;
//import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;


//
// TODO auto-generated type
//
network myexample
{
    @display("bgb=512,395");
    submodules:
        client: StandardHostNdp {
            @display("p=44,213");
        }

        client2: StandardHostNdp {
            @display("p=50,312");
        }
        flatNetworkConfigurator: FlatNetworkConfigurator {
            @display("p=295,91");
        }
        server: StandardHostNdp {
            @display("p=431,190");
        }
        router: Router {
            @display("p=252,256");
        }
    connections:
        router.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> server.pppg++;
        client.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> router.pppg++;


        router.pppg++   <-->  DatarateChannel {  datarate = 1000Mbps; per = 0; delay = 10us; } <--> client2.pppg++;
}

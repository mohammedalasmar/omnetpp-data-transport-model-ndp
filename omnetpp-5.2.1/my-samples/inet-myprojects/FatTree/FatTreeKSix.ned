


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




network FatTreeKSix
{
    parameters:


        @display("bgb=17327.045,8849.436");
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
            @display("p=1332.8688,5108");
        }
        configurator: IPv4NetworkConfigurator {
            @display("p=670.425,5108");
        }

                 //="server";

        host1: StandardHost {







            @display("p=263.38126,3823.0188");
        }
        Pod0Edge1: Router {
            @display("p=359.15625,3296.2563");
        }
        host2: StandardHost {
            @display("p=263.38126,4006.5874");
        }
        Pod0Agg2: Router {
            @display("p=606.575,2713.625");
        }
        host3: StandardHost {
            @display("p=263.38126,4182.175");
        }
        Pod0Edge2: Router {
            @display("p=606.575,3296.2563");
        }
        host4: StandardHost {
            @display("p=518.78125,3799.075");
        }
        Pod0Agg1: Router {
            @display("p=359.15625,2713.625");
        }
        core2: Router {
            @display("p=1755.875,159.625");
        }
        core1: Router {
            @display("p=598.59375,167.60625");
        }
        core4: Router {
            @display("p=4086.4,143.6625");
        }
        core3: Router {
            @display("p=2561.9812,167.60625");
        }
        host5: StandardHost {
            @display("p=518.78125,3990.625");
        }
        host7: StandardHost {
            @display("p=822.0687,3783.1125");
        }
        host6: StandardHost {
            @display("p=518.78125,4166.2124");
        }
        host8: StandardHost {
            @display("p=806.10626,3966.6812");
        }
        host9: StandardHost {
            @display("p=806.10626,4166.2124");
        }
        core5: Router {
            @display("p=4948.375,143.6625");
        }
        core6: Router {
            @display("p=6033.825,159.625");
        }
        core7: Router {
            @display("p=8547.919,159.625");
        }
        core8: Router {
            @display("p=9737.125,159.625");
        }
        core9: Router {
            @display("p=10798.631,167.60625");
        }
        Pod0Agg3: Router {
            @display("p=901.8812,2713.625");
        }
        Pod0Edge3: Router {
            @display("p=901.8812,3296.2563");
        }
        host10: StandardHost {







            @display("p=2609.8687,3878.8875");
        }
        host11: StandardHost {
            @display("p=2609.8687,4062.4563");
        }
        host12: StandardHost {
            @display("p=2609.8687,4238.044");
        }
        host13: StandardHost {
            @display("p=2873.25,3854.9438");
        }
        host14: StandardHost {
            @display("p=2873.25,4046.4937");
        }
        host15: StandardHost {
            @display("p=2873.25,4222.081");
        }
        host16: StandardHost {
            @display("p=3176.5376,3838.9812");
        }
        host17: StandardHost {
            @display("p=3160.575,4022.55");
        }
        host18: StandardHost {
            @display("p=3160.575,4222.081");
        }
        Pod1Agg1: Router {
            @display("p=2713.625,2769.4937");
        }
        Pod1Agg2: Router {
            @display("p=2953.0625,2769.4937");
        }
        Pod1Agg3: Router {
            @display("p=3256.35,2769.4937");
        }
        Pod1Edge1: Router {
            @display("p=2713.625,3352.125");
        }
        Pod1Edge2: Router {
            @display("p=2953.0625,3352.125");
        }
        Pod1Edge3: Router {
            @display("p=3256.35,3352.125");
        }
        host19: StandardHost {







            @display("p=4756.825,3862.925");
        }
        host20: StandardHost {
            @display("p=4756.825,4046.4937");
        }
        host21: StandardHost {
            @display("p=4756.825,4222.081");
        }
        host22: StandardHost {
            @display("p=5020.206,3838.9812");
        }
        host23: StandardHost {
            @display("p=5020.206,4030.5312");
        }
        host24: StandardHost {
            @display("p=5020.206,4206.1187");
        }
        host25: StandardHost {
            @display("p=5323.4937,3823.0188");
        }
        host26: StandardHost {
            @display("p=5307.5312,4006.5874");
        }
        host27: StandardHost {
            @display("p=5307.5312,4206.1187");
        }
        Pod1Agg4: Router {
            @display("p=4860.581,2753.5312");
        }
        Pod1Agg5: Router {
            @display("p=5100.0186,2753.5312");
        }
        Pod1Agg6: Router {
            @display("p=5403.306,2753.5312");
        }
        Pod1Edge4: Router {
            @display("p=4860.581,3336.1626");
        }
        Pod1Edge5: Router {
            @display("p=5100.0186,3336.1626");
        }
        Pod1Edge6: Router {
            @display("p=5403.306,3336.1626");
        }
        host28: StandardHost {







            @display("p=6592.5127,3878.8875");
        }
        host29: StandardHost {
            @display("p=6592.5127,4062.4563");
        }
        host30: StandardHost {
            @display("p=6592.5127,4238.044");
        }
        host31: StandardHost {
            @display("p=6855.8936,3854.9438");
        }
        host32: StandardHost {
            @display("p=6855.8936,4046.4937");
        }
        host33: StandardHost {
            @display("p=6855.8936,4222.081");
        }
        host34: StandardHost {
            @display("p=7159.181,3838.9812");
        }
        host35: StandardHost {
            @display("p=7143.2188,4022.55");
        }
        host36: StandardHost {
            @display("p=7143.2188,4222.081");
        }
        Pod1Agg7: Router {
            @display("p=6696.2686,2769.4937");
        }
        Pod1Agg8: Router {
            @display("p=6935.706,2769.4937");
        }
        Pod1Agg9: Router {
            @display("p=7238.9937,2769.4937");
        }
        Pod1Edge7: Router {
            @display("p=6696.2686,3352.125");
        }
        Pod1Edge8: Router {
            @display("p=6935.706,3352.125");
        }
        Pod1Edge9: Router {
            @display("p=7238.9937,3352.125");
        }
        host37: StandardHost {







            @display("p=9010.831,3958.7");
        }
        host38: StandardHost {
            @display("p=9010.831,4142.2686");
        }
        host39: StandardHost {
            @display("p=9010.831,4317.8564");
        }
        host40: StandardHost {
            @display("p=9274.213,3934.7563");
        }
        host41: StandardHost {
            @display("p=9274.213,4126.306");
        }
        host42: StandardHost {
            @display("p=9274.213,4301.8936");
        }
        host43: StandardHost {
            @display("p=9577.5,3918.7937");
        }
        host44: StandardHost {
            @display("p=9561.537,4102.3623");
        }
        host45: StandardHost {
            @display("p=9561.537,4301.8936");
        }
        host46: StandardHost {







            @display("p=10846.519,3974.6626");
        }
        host47: StandardHost {
            @display("p=10846.519,4158.2314");
        }
        host48: StandardHost {
            @display("p=10846.519,4333.819");
        }
        host49: StandardHost {
            @display("p=11109.9,3950.7188");
        }
        host50: StandardHost {
            @display("p=11109.9,4142.2686");
        }
        host51: StandardHost {
            @display("p=11109.9,4317.8564");
        }
        host52: StandardHost {
            @display("p=11413.1875,3934.7563");
        }
        host53: StandardHost {
            @display("p=11397.225,4118.325");
        }
        server: StandardHost {
            @display("p=11397.225,4317.8564");
        }
        Pod1Agg10: Router {
            @display("p=9114.588,2849.3062");
        }
        Pod1Agg11: Router {
            @display("p=9354.025,2849.3062");
        }
        Pod1Agg12: Router {
            @display("p=9657.3125,2849.3062");
        }
        Pod1Agg13: Router {
            @display("p=10950.275,2865.2688");
        }
        Pod1Agg14: Router {
            @display("p=11189.713,2865.2688");
        }
        Pod1Agg15: Router {
            @display("p=11493,2865.2688");
        }
        Pod1Edge10: Router {
            @display("p=9114.588,3431.9375");
        }
        Pod1Edge11: Router {
            @display("p=9354.025,3431.9375");
        }
        Pod1Edge12: Router {
            @display("p=9657.3125,3431.9375");
        }
        Pod1Edge13: Router {
            @display("p=10950.275,3447.9");
        }
        Pod1Edge14: Router {
            @display("p=11189.713,3447.9");
        }
        Pod1Edge15: Router {
            @display("p=11493,3447.9");
        }
    connections:

        host1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host2.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host3.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod0Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg2.pppg++;
        Pod0Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge1.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg2.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg3.pppg++;
        Pod0Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg3.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge3.pppg++;
        Pod0Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host4.pppg++;
        Pod0Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host5.pppg++;
        host6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge2.pppg++;
        Pod0Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host7.pppg++;
        Pod0Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host8.pppg++;
        host9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Edge3.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg1.pppg++;
        Pod0Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host11.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host12.pppg++;
        host10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge1.pppg++;
        host15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge2.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg2.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge3.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg2.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg3.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host13.pppg++;
        Pod1Edge2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host14.pppg++;
        Pod1Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge1.pppg++;
        Pod1Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg3.pppg++;
        Pod1Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        Pod1Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host16.pppg++;
        Pod1Edge3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host17.pppg++;
        host18.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge3.pppg++;
        Pod1Agg1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg1.pppg++;
        host19.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge4.pppg++;
        Pod1Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge6.pppg++;
        host24.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge5.pppg++;
        Pod1Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg6.pppg++;
        Pod1Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        Pod1Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host25.pppg++;
        Pod1Edge6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host26.pppg++;
        host27.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge6.pppg++;
        Pod1Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg5.pppg++;
        Pod1Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        Pod1Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg6.pppg++;
        Pod1Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host22.pppg++;
        Pod1Edge5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host23.pppg++;
        Pod1Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host20.pppg++;
        Pod1Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host21.pppg++;
        Pod1Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        Pod1Edge4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg5.pppg++;
        Pod1Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge4.pppg++;
        Pod1Agg8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge9.pppg++;
        host33.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge8.pppg++;
        Pod1Edge8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg8.pppg++;
        Pod1Edge8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg7.pppg++;
        Pod1Edge8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg9.pppg++;
        Pod1Edge8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host31.pppg++;
        Pod1Edge8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host32.pppg++;
        Pod1Edge9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg9.pppg++;
        Pod1Edge9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg7.pppg++;
        Pod1Edge9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host34.pppg++;
        Pod1Edge9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host35.pppg++;
        host28.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge7.pppg++;
        Pod1Edge7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host29.pppg++;
        Pod1Edge7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host30.pppg++;
        Pod1Edge7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg7.pppg++;
        Pod1Edge7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg8.pppg++;
        Pod1Agg9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge7.pppg++;
        host36.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge9.pppg++;
        host42.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge11.pppg++;
        Pod1Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg11.pppg++;
        Pod1Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg10.pppg++;
        Pod1Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg12.pppg++;
        Pod1Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host40.pppg++;
        Pod1Edge11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host41.pppg++;
        Pod1Edge12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg12.pppg++;
        Pod1Edge12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg10.pppg++;
        Pod1Edge12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host43.pppg++;
        Pod1Edge12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host44.pppg++;
        host46.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge13.pppg++;
        Pod1Edge13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host47.pppg++;
        Pod1Edge13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host48.pppg++;
        Pod1Edge13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg13.pppg++;
        Pod1Edge13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg14.pppg++;
        Pod1Edge10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host38.pppg++;
        Pod1Edge10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host39.pppg++;
        Pod1Edge10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg10.pppg++;
        Pod1Edge10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg11.pppg++;
        host51.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge14.pppg++;
        Pod1Agg14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge15.pppg++;
        Pod1Agg11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge12.pppg++;
        Pod1Agg15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge13.pppg++;
        host37.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge10.pppg++;
        Pod1Edge15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg15.pppg++;
        Pod1Edge15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg13.pppg++;
        Pod1Edge15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host52.pppg++;
        Pod1Edge15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host53.pppg++;
        Pod1Edge14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg14.pppg++;
        Pod1Edge14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg13.pppg++;
        Pod1Edge14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg15.pppg++;
        Pod1Edge14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host49.pppg++;
        Pod1Edge14.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> host50.pppg++;
        Pod1Agg12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge10.pppg++;
        server.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge15.pppg++;
        host45.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Edge12.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core5.pppg++;
        Pod0Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core6.pppg++;
        core7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg3.pppg++;
        Pod0Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core8.pppg++;
        core9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod0Agg3.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core5.pppg++;
        Pod1Agg2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core6.pppg++;
        Pod1Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core7.pppg++;
        Pod1Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core8.pppg++;
        Pod1Agg3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core9.pppg++;
        core1.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg4.pppg++;
        Pod1Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        Pod1Agg5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core5.pppg++;
        core6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg5.pppg++;
        Pod1Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core7.pppg++;
        Pod1Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core8.pppg++;
        Pod1Agg7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        Pod1Agg7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core2.pppg++;
        Pod1Agg7.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        Pod1Agg8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core4.pppg++;
        Pod1Agg8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core5.pppg++;
        Pod1Agg8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core6.pppg++;
        Pod1Agg9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core7.pppg++;
        core8.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg9.pppg++;
        Pod1Agg9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core9.pppg++;
        Pod1Agg10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        Pod1Agg10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core2.pppg++;
        Pod1Agg10.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core3.pppg++;
        core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg11.pppg++;
        Pod1Agg11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core5.pppg++;
        Pod1Agg11.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core6.pppg++;
        Pod1Agg12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core7.pppg++;
        Pod1Agg12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core8.pppg++;
        Pod1Agg12.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core9.pppg++;
        Pod1Agg13.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core1.pppg++;
        core2.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg13.pppg++;
        core3.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg13.pppg++;
        core4.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg14.pppg++;
        core5.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg14.pppg++;
        core6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg14.pppg++;
        Pod1Agg15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core7.pppg++;
        Pod1Agg15.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core8.pppg++;
        core9.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> Pod1Agg15.pppg++;
        Pod1Agg6.pppg++ <--> DatarateChannel {  datarate = 1000Mbps; per = 0.01; delay = 0.1ms; } <--> core9.pppg++;
}



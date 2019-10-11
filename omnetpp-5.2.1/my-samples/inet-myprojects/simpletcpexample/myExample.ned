package simpletcpexample;

 //
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 



import inet.networklayer.configurator.ipv4.FlatNetworkConfigurator;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import ned.IBidirectionalChannel;


//
// test
//
network myExample
{
    @display("bgb=480,382");
    submodules:
        client: StandardHost {
            @display("p=57,211");
        }
        server: StandardHost {
            @display("p=446,211;i=device/server2");
        }
        flatNetworkConfigurator: FlatNetworkConfigurator {
            @display("p=277,70");
        }
    connections:
        client.pppg++ <--> DatarateChannel {per=0.01;  datarate = 56000bps; } <--> server.pppg++;
}

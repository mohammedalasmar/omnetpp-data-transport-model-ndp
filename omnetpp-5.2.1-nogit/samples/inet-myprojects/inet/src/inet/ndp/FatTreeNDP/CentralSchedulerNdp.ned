// @author Mohammed Alasmar
// email: mohammedzsalasmar@gmail.com
// 2019

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

package inet.ndp.FatTreeNDP;

simple CentralSchedulerNdp
{
    parameters:
       bool isWebSearchWorkLoad; 
       int IW; // initial windows size
       int ndpSwitchQueueLength; // initial windows size
       bool perFlowEcmp;
       bool perPacketEcmp;
       int seedValue;
       
       
        //  @dynamic(true);
        int kValue; // = default(4);  // FatTree size 
        string trafficMatrixType;
        int arrivalRate; //= default(4);
//        int flowSize @unit(B); //= default(4);
//        double longFlowSize @unit(B)=  default(10MiB);

        int flowSize;
        double longFlowSize;

        double numShortFlows;
        double percentLongFlowNodes;
        volatile double numCompletedShortFlows = default(0);
         //  @unit(s) = default(1s);
        bool shuffle;
        
        
        bool oneToOne;
        bool manyToOne;
        bool oneToMany;
        bool daisyChainGFS = default(false);
        // multicast & multisource
        int numRunningMulticastGroups;
        //  string runMulticast = default("false");
        int numRunningMultiSourcingGroups;
        int numReplica ;


         // incast
        int numIncastSenders = default(1);

//        @signal[multicastGroupID](type=double);
//        @statistic[multicastGroupID](title="multicast Group ID"; source=multicastGroupID; unit=s; record=last);


}

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

package fattree.experiment1;

simple CentralScheduler
{
    parameters:
        //  @dynamic(true);
        int kValue; // = default(4);  // FatTree size 
        string trafficMatrixType;
        int arrivalRate; //= default(4);
        int flowSize @unit(B); //= default(4);
        double numShortFlows;
        double longFlowSize @unit(B)=  default(10MiB);
        double percentLongFlowNodes;
        volatile double numCompletedShortFlows = default(0);
         //  @unit(s) = default(1s);
        bool shuffle;
}

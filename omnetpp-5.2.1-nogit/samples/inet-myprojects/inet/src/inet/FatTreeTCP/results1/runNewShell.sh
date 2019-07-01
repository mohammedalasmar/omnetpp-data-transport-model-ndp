
echo " "
echo " "

echo " Running FatTree Traffic Matrix .... "
find . -name "*.vec" -type f -delete|find . -name  "*.sca"  -type f -delete| find . -name "*.vci" -type f -delete | find . -name "*.csv" -type f -delete

#echo $0 $1 ' > echo $0 $1 '
#args=("$@")
#declare -i a=${args[0]}
#declare -i b=${args[1]}


#echo " >>> Enter FatTreeSize: "
#read a
#echo " >>> Enter numShortFlows: "
#read b
#echo " "

#../../FatTree -u Cmdenv  -m  -n ../..:../../../inet/src -l ../../../inet/src/INET -f  ../omnetpp2.ini  -c General -r   "\$FatTreeSize==$(printf '%d' $1)  &&  \$numShortFlows==$(printf '%d' $2)"

opp_run -u Cmdenv -m -n ../../..:../../../../examples   -l ../../../INET -f ../omnetpp1.ini -c General -r "\$FatTreeSize==$(printf '%d' $1)  &&  \$numShortFlows==$(printf '%d' $2)"



echo "Throughput"
scavetool export -T s -f "module(**.tcpApp[*]) AND ("mohThroughput:mean")"   -F CSV-S -o instThroughput.csv *.sca
echo "   "

echo "FCT"
scavetool export -T s -f "module(**.tcpApp[*]) AND ("fctRecordv1:last")"   -F CSV-S -o fct.csv *.sca
echo "   "


echo "RTO"
scavetool export -T v -f 'module(**.tcp) AND ("numRTOsMOH:vector" )'  -F CSV-R -o numRTOs.csv *.vec
echo "   "

echo "FastRetransmissions"
scavetool export -T v -f 'module(**.tcp) AND ( "numFastRetransmissions:vector" )'  -F CSV-R -o numFastRets.csv  *.vec
echo "   "



echo "CoreRouter-rcvdPk:count"
scavetool export -T s -f 'module(*.CoreRouter[*].*) AND name("rcvdPk:count") '   -F CSV-S -o coreRouterRcvdPkt.csv *.sca
echo "CoreRouter-dropPk:count"
scavetool export -T s -f "module(*.CoreRouter[*].*) AND name(dropPk:count)"   -F CSV-S -o coreRouterDropPkt.csv *.sca

echo "   "

echo "aggRouters-rcvdPk:count"
scavetool export -T s -f 'module(*.aggRouters[*].*) AND  name("rcvdPk:count") '   -F CSV-S -o aggRouterRcvdPkt.csv *.sca
echo "aggRouters-dropPk:count"
scavetool export -T s -f "module(*.aggRouters[*].*) AND name(dropPk:count)"   -F CSV-S -o aggRouterDropPkt.csv *.sca

echo "   "

echo "edgeSwitch-rcvdPk:count"
scavetool export -T s -f 'module(*.edgeSwitch.*) AND  name("rcvdPk:count") '   -F CSV-S -o edgeRouterRcvdPkt.csv *.sca
echo "edgeSwitch-dropPk:count"
scavetool export -T s -f "module(*.edgeSwitch.*) AND name(dropPk:count)"   -F CSV-S -o edgeRouterDropPkt.csv *.sca

echo "   "

echo "servers-rcvdPk:sum(packetBytes)"
scavetool export -T s -f 'module(FatTreeTopology.Pod[*].racks[*].servers[*].ppp[*].queue) AND  name("rcvdPk:sum(packetBytes)") '   -F CSV-S -o serversRcvdPktBytes.csv *.sca
echo "servers-dropPk:sum(packetBytes)"
scavetool export -T s -f 'module(FatTreeTopology.Pod[*].racks[*].servers[*].ppp[*].queue) AND  name("dropPk:sum(packetBytes)") '   -F CSV-S -o serversDropPktBytes.csv *.sca
echo "servers-rcvdPk:count"
scavetool export -T s -f 'module(FatTreeTopology.Pod[*].racks[*].servers[*].ppp[*].queue) AND  name("rcvdPk:count") '   -F CSV-S -o serversRcvdPkt.csv *.sca
echo "servers-dropPk:count"
scavetool export -T s -f 'module(FatTreeTopology.Pod[*].racks[*].servers[*].ppp[*].queue) AND  name("dropPk:count") '   -F CSV-S -o serversDropPkt.csv *.sca

echo "   "

echo "config."
scavetool export -T s -f "name(simTimeTotal=)  OR name(numShortFlows=)  OR name(flowSize=) OR name(percentLongFlowNodes=) OR name(arrivalRate=) OR name(randTM)  OR name(permTM)  OR name(wallClockTime=) "   -F CSV-S -o config.csv *.sca

echo "   "

echo "FatTreeTopology.centralSchedulerTCP "

scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(numTcpSessionAppsVec)'  -F CSV-R -o numTcpSessionApps.csv  *.vec
scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(numTcpSinkAppsVec)'  -F CSV-R -o numTcpSinkApps.csv  *.vec
scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(nodes)'  -F CSV-R -o nodes.csv  *.vec

scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(matSrc)'  -F CSV-R -o matrixSrc.csv  *.vec
scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(matDest)'  -F CSV-R -o matrixDest.csv  *.vec

scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(permMapLongFlowsVec)'  -F CSV-R -o longFlowsNodes.csv  *.vec
scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(permMapShortFlowsVec)'  -F CSV-R -o shortFlowsNodes.csv  *.vec

scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(randMapShortFlowsVec)'  -F CSV-R -o randShortFlowsNodes.csv  *.vec
scavetool export -T v -f 'module(FatTreeTopology.centralSchedulerTCP) AND name(permMapShortFlowsVector)'  -F CSV-R -o permMapShortFlowsVector.csv  *.vec




cat numRTOs.csv | cut -d, -f9  | sed "1 d" > MatNumRTOs.csv
cat numFastRets.csv | cut -d, -f9  | sed "1 d" > MatNumFastRets.csv

cat fct.csv | cut -d, -f11  | sed "1 d" > MatFct.csv
cat instThroughput.csv | cut -d, -f11  | sed "1 d" > MatInstThroughput.csv

cat coreRouterRcvdPkt.csv | cut -d, -f11  | sed "1 d" > MatCoreRouterRcvdPkt.csv
cat coreRouterDropPkt.csv | cut -d, -f11  | sed "1 d" > MatCoreRouterDropPkt.csv

cat aggRouterRcvdPkt.csv | cut -d, -f11  | sed "1 d" > MatAggRouterRcvdPkt.csv
cat aggRouterDropPkt.csv | cut -d, -f11  | sed "1 d" > MatAggRouterDropPkt.csv

cat edgeRouterRcvdPkt.csv | cut -d, -f11  | sed "1 d" > MatEdgeRouterRcvdPkt.csv
cat edgeRouterDropPkt.csv | cut -d, -f11  | sed "1 d" > MatEdgeRouterDropPkt.csv


cat serversRcvdPktBytes.csv | cut -d, -f11  | sed "1 d" > MatServersRcvdPktBytes.csv
cat serversRcvdPkt.csv | cut -d, -f11  | sed "1 d" > MatServersRcvdPkt.csv

cat serversDropPkt.csv | cut -d, -f11  | sed "1 d" > MatServersDropPkt.csv
cat serversDropPktBytes.csv | cut -d, -f11  | sed "1 d" > MatServersDropPktBytes.csv



cat config.csv | cut -d, -f11  | sed "1 d" > MatConfig.csv

cat numTcpSessionApps.csv | cut -d, -f9  | sed "1 d" > MatNumTcpSessionApps.csv
cat numTcpSinkApps.csv | cut -d, -f9  | sed "1 d" > MatNumTcpSinkApps.csv
cat nodes.csv | cut -d, -f9  | sed "1 d" > MatNodes.csv

cat matrixSrc.csv | cut -d, -f9  | sed "1 d" > MatMatrixSrc.csv
cat matrixDest.csv | cut -d, -f9  | sed "1 d" > MatMatrixDest.csv

cat longFlowsNodes.csv | cut -d, -f9  | sed "1 d" > MatLongFlowsNodes.csv
cat shortFlowsNodes.csv | cut -d, -f9  | sed "1 d" > MatShortFlowsNodes.csv

cat randShortFlowsNodes.csv | cut -d, -f9  | sed "1 d" > MatRandShortFlowsNodes.csv
cat permMapShortFlowsVector.csv | cut -d, -f9  | sed "1 d" > MatPermMapShortFlowsVector.csv




if [ "$3" = "-p" ]  #p: plotting
then
/Applications/MATLAB_R2017a.app/bin/matlab -nodesktop -nosplash    -r "cd('matlabScriptsNew/'); plotResults($1,$2)"
#/Applications/MATLAB_R2017a.app/bin/matlab -nodesktop -nosplash    -r "plotThroughput($a,$b)"
#/Applications/MATLAB_R2017a.app/bin/matlab -nodesktop -nosplash    -r "plotNumFastRetsANDnumRTOs($a,$b)"
elif [ "$3" = "-ph" ] #p: plotting on HPC
then
matlab -nodesktop -nosplash    -r "cd('matlabScriptsNew/'); plotResults($1,$2)"
else
echo "no plotting"
fi

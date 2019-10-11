#sh -e run.sh
#!/bin/sh
#rm *.vec | rm *.sca | rm *.vci | rm *.csv

echo "Running Incast example … "      

find . -name "*.vec" -type f -delete|find . -name  "*.sca"  -type f -delete| find . -name "*.vci" -type f -delete | find . -name "*.csv" -type f -delete

../Incast   -m -u Cmdenv -n ../.:../../inet/src -l ../../inet/src/INET ../IncastTCP.ini  


scavetool export -T s -f 'module(**.tcpApp[*]) AND ("mohThroughput:mean")'  -F CSV-S -o temp.csv *.sca

scavetool export -T s -f 'module(**.tcpApp[*]) AND ("fctRecordv1:last")'  -F CSV-S -o temp2.csv *.sca
echo "dropped packets at the shared link at the receiver"
scavetool export -T s -f 'module(*.router.ppp[0].queue) AND name(dropPk:count)'  -F CSV-S -o temp3.csv *.sca

echo "RTO"
scavetool export -T v -f 'module(**.tcp) AND ("numRTOsMOH:vector" )'  -F CSV-R -o temp4.csv *.vec
scavetool export -T v -f 'module(**.tcp) AND ( "numFastRetransmissions:vector" )'  -F CSV-R -o temp5.csv  *.vec

cat temp.csv | cut -d, -f2,6  | sed "1 d" > throughput.csv
cat temp2.csv | cut -d, -f2,6  | sed "1 d" > fct.csv
cat temp3.csv | cut -d, -f2,6  | sed "1 d" > dropPkts.csv
cat temp4.csv | cut -d, -f9  | sed "1 d" > RTOs.csv
cat temp5.csv | cut -d, -f9  | sed "1 d" > fastRet.csv


/Applications/MATLAB_R2017a.app/bin/matlab -nodesktop -nosplash    -r "plotResults"





 

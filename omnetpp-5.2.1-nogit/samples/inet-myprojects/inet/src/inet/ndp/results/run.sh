#sh -e run.sh
#!/bin/sh
#rm *.vec | rm *.sca | rm *.vci | rm *.csv

echo "Running Incast example … "      

find . -name "*.vec" -type f -delete|find . -name  "*.sca"  -type f -delete| find . -name "*.vci" -type f -delete | find . -name "*.csv" -type f -delete

 

opp_run  -u Cmdenv -m -n ../../..:../../../../examples:../../../../tutorials -l ../../../INET ../IncastRQ.ini


scavetool export -T s -f 'module(**.raptorQApp[*]) AND ("mohThroughputRQ:mean")'  -F CSV-S -o temp1.csv *.sca
# scavetool export -T s -f 'module(**.tcpApp[*]) AND ("throughputRecord:last")'  -F CSV-S -o rrr.csv *.sca
scavetool export -T s -f 'module(**.raptorQApp[*]) AND ("fctRecordv2:last")'  -F CSV-S -o temp2.csv *.sca

scavetool export -T s -f 'module(*.router.ppp[0].queue) AND name(dropPk:count)'  -F CSV-S -o temp3.csv *.sca
#scavetool export -T v -f 'module(*.server.*) AND ("numRequestsRTOs:vector" )'  -F CSV-R -o temp4.csv *.vec




cat temp1.csv | cut -d, -f2,6  | sed "1 d" > throughput.csv
cat temp2.csv | cut -d, -f2,6  | sed "1 d" > fct.csv
cat temp3.csv | cut -d, -f2,6  | sed "1 d" > dropPkts.csv
cat temp4.csv | cut -d, -f9,9  | sed "1 d" > requestsRTOs.csv


/Applications/MATLAB_R2017a.app/bin/matlab -nodesktop -nosplash    -r "plotResults"





 

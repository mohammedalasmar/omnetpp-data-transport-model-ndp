#sh -e run.sh
#!/bin/sh
#rm *.vec | rm *.sca | rm *.vci | rm *.csv

echo "Running Incast example … "      

find . -name "*.vec" -type f -delete|find . -name  "*.sca"  -type f -delete| find . -name "*.vci" -type f -delete | find . -name "*.csv" -type f -delete




 /Volumes/LocalDataHD/m/ma/ma777/Desktop/omnetpp-5.1.1/samples/inet/src/./run_inet -u Cmdenv -f  /Volumes/LocalDataHD/m/ma/ma777/Desktop/omnetpp-5.1.1/samples/inet/src/inet/dataTransportCodes/Incast/Incast.ini 

#scavetool export -T s -f 'module(**.tcpApp[*]) AND ("mohThroughput:mean")'  -F CSV -o rrr.csv *.sca
 scavetool export -T s -f 'module(**.tcpApp[*]) AND ("throughputRecord:last")'  -F CSV -o rrr.csv *.sca
#scavetool export -T s -f 'module(**.tcpApp[*]) AND ("fctRecord:last")'  -F CSV -o rrr.csv *.sca

cat rrr.csv | cut -d, -f8,19  | sed "1 d" > nnn.csv

# /Applications/MATLAB_R2016a.app/bin/matlab -nodesktop -nosplash    -r "scriptFct"

/Applications/MATLAB_R2016a.app/bin/matlab -nodesktop -nosplash    -r "scriptThroughput"


quit


 
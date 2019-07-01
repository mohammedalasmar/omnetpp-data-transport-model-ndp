#sh -e run.sh
#!/bin/sh
#rm *.vec | rm *.sca | rm *.vci | rm *.csv

echo "Running Incast example … "      

find . -name "*.vec" -type f -delete|find . -name  "*.sca"  -type f -delete| find . -name "*.vci" -type f -delete | find . -name "*.csv" -type f -delete| find . -name "*.elog" -type f -delete


 
 

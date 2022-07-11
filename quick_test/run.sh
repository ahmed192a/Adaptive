#! /bin/sh


# print the current pid
echo "Current PID: $$";

#./build.sh ; 
cd ../Cloud
g++ server.cpp -o output.exe

# running the cloud server application
gnome-terminal -- './output.exe';

cd ../build/App ; 
./Adaptive_Platform


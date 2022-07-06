#! /bin/sh

#./build.sh ; 
cd ../Cloud
g++ server.cpp -o output.exe

# running the cloud server application
gnome-terminal -- './output.exe';

cd ../build/App ; 
./Adaptive_Platform

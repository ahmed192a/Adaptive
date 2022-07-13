#! /bin/sh


# print the current pid
echo "Current PID: $$";

#./build.sh ; 
cd ../Cloud
g++ server.cpp metadata.hpp -o output.exe

# running the cloud server application
gnome-terminal -- './output.exe';


# use putty for uart configuration
# gnome-terminal -- 'putty -serial /dev/ttyACM1';

# start adaptive platform
cd ../build/App ; 
./Adaptive_Platform


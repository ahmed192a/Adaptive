#! /bin/sh

# runningn the service discovery 
./ucm_test.sh

# compiling the cloud server application
cd ../Cloud
g++ server.cpp -o output.exe

# running the cloud server application
gnome-terminal -- './output.exe';

# running the OTA
cd ../build/App/processes
gnome-terminal -- './ota_process';

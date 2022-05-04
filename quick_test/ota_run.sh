#! /bin/sh

# runningn the service discovery 
cd ../build/test_partial_processes/SD_TEST;
gnome-terminal -- './SD/sd_process';
sudo gnome-terminal -- './ucm_server/ucm_server_test';

# compiling the cloud server application
cd ../../../Cloud
g++ server.cpp -o output.exe

# running the cloud server application
gnome-terminal -- './output.exe';

# running the OTA
cd ../build/App/processes
gnome-terminal -- './ota_process';

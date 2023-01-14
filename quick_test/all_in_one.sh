#!/bin/bash

# create a map for the options and the corresponding names
declare -A options 
options[0]="configure"
options[1]="build"
options[2]="run"
options[3]="test"
options[4]="clear_stuck"
options[5]="run ota"

#  if a parameter is passed, then it is the option else ask for the option
if [ -z "$1" ]; then
    # ask for the option
    echo "Please select an option:"
    #  print the options
    for i in "${!options[@]}"; do
        echo "$i) ${options[$i]}"
    done
    read -p "Enter your choice: " choice
else
    # check if the parameter is a valid option
    if [ -z "${options[$1]}" ]; then
        echo "Invalid option"
        exit 1
    fi
    # use the parameter as the option
    choice=$1
fi


# print the selected option
echo "You have selected ${options[$choice]}"
echo "Current PID: $$"


case $choice in
0)  # configure
    cd ..; 
    cmake -S . -B build
    ;;
1)  # build
    cd ../build;
    make
    ;;
2)  # run
    echo "Current PID: $$";
    echo "build and run cloud server"
    cd ../Cloud
    g++ server.cpp metadata.hpp -o output.exe
    gnome-terminal -- './output.exe';
    # wait for 1 second
    sleep 1; 
    echo "Run adaptive platform"
    cd ../build/App;
    ./Adaptive_Platform
    ;;
3)  # test
    cd ../build/Testing ;
    ./Adaptive_Platform-ut
    ;;
4)  # clear_stuck
    cd ../build/App/processes;
    rm -rf redirected/*;
    rm -r UCM_SERVER/SWP;
    rm sm_process/trigger560;
    rm sm_process/trigger550;
    rm sm_process/state_client_fifo;
    rm sm_process/execution_client_fifo;
    rm SD/data.csv;
    rm SD/execution_client_fifo;
    rm ota_process/meta-data.dat;
    rm ota_process/execution_client_fifo;
    rm UCM_SERVER/execution_client_fifo;
    rm UCM_SERVER/CurrentStatus450;
    ;;
5)  # run ota
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
    cd ../build/App/processes/ota_process
    gnome-terminal -- './ota_process';

    ;;
*)  # invalid choice
    echo "Invalid choice"
    ;;
esac


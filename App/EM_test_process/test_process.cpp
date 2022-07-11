/**
 * @file test_process.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "ara/exec/execution_client.hpp"
#include <unistd.h>
#include <signal.h>
#include <csignal>
#include "ara/Log_trace/Log.hpp"
using namespace std;
using namespace ara::exec;
Log lg("test_process");
ExecutionClient client;

int sigval = 0;
void handle_sigterm(int sig){
    sigval = sig;
    lg.Insert("terminating");
    client.ReportExecutionState(ExecutionState::kTerminating);
}

int main(){

    signal(SIGTERM, handle_sigterm);
    // struct sigaction sa;

    // sa.sa_handler = &handle_sigterm;
    // sa.sa_flags= SA_RESTART;
    // sigaction(SIGTERM, &sa, NULL);
    lg.Insert("[process]you are in the second file");
    lg.Insert("[process]process for testing");
    lg.Insert("[process]creating execution client");
    cout<<"\n\n\t\t[process]you are in the second file"<<endl;
    cout<<"\t\t[process]process for testing"<<endl;
    cout<<"\t\t[process]creating execution client "<<endl;
    client.ReportExecutionState(ExecutionState::kRunning);




    while (1)
    {
        cout<<"\t\t[process] running"<<endl;
        lg.Insert(to_string(sigval));
        usleep(3000);
        if(sigval)
        break;
    }
    lg.Insert("[process]finish reporting running to EM");
    cout<<"\t[process]finish reporting running to EM\n"<<endl;

    return 0;
}
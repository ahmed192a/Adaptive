#include <iostream>
#include "execution_client.h"
#include <unistd.h>
#include <signal.h>
#include "Log_trace/Log.h"
using namespace std;
using namespace ara::exec;
Log lg;
int sigval = 0;
void handle_sigterm(int sig){
    sigval = sig;
    lg.Insert("terminating","p");
}

int main(){

    struct sigaction sa;

    sa.sa_handler = &handle_sigterm;
    sa.sa_flags= SA_RESTART;
    sigaction(SIGTERM, &sa, NULL);
    lg.Insert("[process]you are in the second file", "p");
    lg.Insert("[process]process for testing", "p");
    lg.Insert("[process]creating execution client", "p");
    cout<<"\n\n\t\t[process]you are in the second file\n";
    cout<<"\t\t[process]process for testing\n";
    cout<<"\t\t[process]creating execution client \n";
    ExecutionClient client;
        fflush(stdin);
        fflush(stdout);
    client.ReportExecutionState(ExecutionState::kRunning);




    while (1)
    {
        cout<<"\t\t[process] running\n";
        lg.Insert(to_string(sigval), "P");
        usleep(1000);
        if(sigval)
        break;
    }
    lg.Insert("[process]finish reporting running to EM", "p");
    cout<<"\t[process]finish reporting running to EM\n\n";

    return 0;
}
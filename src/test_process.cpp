#include <iostream>
#include "execution_client.h"
#include <unistd.h>
using namespace std;
using namespace ara::exec;
int main(){
    cout<<"\n\n\t[process]you are in the second file\n";
    cout<<"\t[process]process for testing\n";
    cout<<"\t[process]creating execution client \n";
    ExecutionClient client;
           fflush(stdin);
        fflush(stdout);
    client.ReportExecutionState(ExecutionState::kRunning);

    cout<<"\t[process]finish reporting running to EM\n\n";

    return 0;
}
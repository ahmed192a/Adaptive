#include <iostream>
#include <memory>
#include <unistd.h>
#include <signal.h>
#include <csignal>
#include "ara/exec/state_client.hpp"
#include "ara/exec/function_group_state.hpp"
#include "ara/exec/execution_client.hpp"

using namespace std;
using namespace ara::exec;
int sigval = 0;
void handle_sigterm(int sig){
    sigval = 1;
    cout<<"{SM} terminating"<<endl;
}


int main()
{
    cout<<endl<<"[SM]"<<std::string(get_current_dir_name())<<endl;
    signal(SIGTERM, handle_sigterm);
    // struct sigaction sa;
    // sa.sa_handler = &handle_sigterm;    // handle SIGTERM
    // sa.sa_flags= SA_RESTART;            // restart system calls
    // sigaction(SIGTERM, &sa, NULL);      // register signal handler
    
    cout<<"\n\n\t\t[SM]you are in the second file"<<endl;
    cout<<"\t\t[SM]SM for testing"<<endl;
    cout<<"\t\t[SM]creating execution client "<<endl;
    ExecutionClient client;
    client.ReportExecutionState(ExecutionState::kRunning);

    StateClient sm_client;
    FunctionGroupState::CtorToken token;
    token.fg_name = "FG_1";
    token.c_state = "on";
    FunctionGroupState FGS(std::move(token));
    std::cout<<"[SM] FGS created "<<endl;
    std::future<boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc>> _future = sm_client.SetState(FGS);
    boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc> var = _future.get();
    std::cout<<"[SM] state changed"<<endl;
    cout<<"\t\t[SM] result "<<var.index()<<endl;
    // get<1>(var).get();
    while (1)
    {
        cout<<"\t\t[SM] running"<<endl;
        usleep(3000);
        if(sigval) break;
    }
    cout<<"\t[SM]finish reporting running to EM\n"<<endl;
    return 0;
}
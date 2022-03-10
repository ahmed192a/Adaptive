#include <signal.h>
#include "ara/SD_c/proxy.hpp"
#include <iostream>
#include "color/color.hpp"
#define SD_PORT    1690

/**
 * @todo
 *  - event id
 *  - field id
 *  - event unsubscribe
 *  - event send data in update notify
 *  - test field proxy
 */
Color::Modifier green(Color::FG_GREEN);
Color::Modifier def(Color::FG_DEFAULT);
void event_field_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    if (signum != SIGUSR1) return;
    if (siginfo->si_code != SI_QUEUE) return;
    std::cout <<"\t\t\t[CLIENT] receiver: Got value " << siginfo->si_int << std::endl;

}

int main(int argc, char **argv){
    std::cout<<green;
    pid_t pid = getpid();
    std::cout << "\t\t\t[CLIENT] receiver: PID is " << pid << std::endl;
    int result;

    struct sigaction signal_action;
    signal_action.sa_sigaction = event_field_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);

    // Event
    saam::proxy test;
    
    test.FindService(32);

    std::cout<<"\t\t\t[CLIENT] Result of ADD : ";
    result = test.Add(1,5);
    std::cout<<result <<std::endl;

    test.ev1.Subscribe();
    sleep(5);
    test.ev2.Subscribe();
    sleep(5);
    test.fd1.Subscribe();


    while(1) sleep(100);
    return 0;
}
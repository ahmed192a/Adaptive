

#include <signal.h>
#include "lib/common.h"

#define SD_PORT    1690


 void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    if (signum != SIGUSR1) return;
    if (siginfo->si_code != SI_QUEUE) return;

    printf("receiver: Got value %d\n", siginfo->si_int);
}

int main(int argc, char **argv){

    pid_t pid = getpid();
    struct sigaction signal_action;

    // Event
    std::cout << "receiver: PID is " << pid << std::endl;

    signal_action.sa_sigaction = signal_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);

    proxy test;
    
    test.FindService(SD_PORT, 32);

    //test.SendRequest();
    ara::ucm::pkgmgr::add_output adder(&test);
    char name [30] = "event1";
    
    test.Subscribe(name);
    sleep(5);
    strcpy(name, "event2");
    test.Subscribe(name);

   // ara::ucm::pkgmgr::add_output adder(&test);

    //adder();

    while(1) sleep(100);
    return 0;
}
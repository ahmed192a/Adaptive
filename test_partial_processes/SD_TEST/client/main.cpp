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

    printf("receiver: Got value %d\n", siginfo->si_int);
}

int main(int argc, char **argv){
    std::cout<<green;
    pid_t pid = getpid();
    std::cout << "receiver: PID is " << pid << std::endl;


    struct sigaction signal_action;
    signal_action.sa_sigaction = event_field_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);

    // Event
    saam::proxy test;
    
    test.FindService(32);

    std::cout<<"Result of ADD section-------------- \n" <<test.Add(1,5)<<std::endl;
    std::cout<<"END Result of ADD section-------------- \n";

    char name [30] = "event1";    
    test.ev1.Subscribe(name);
    sleep(5);
    strcpy(name, "event2");
    test.ev1.Subscribe(name);

    char name_field [30] = "field1";  
    test.ev1.Subscribe(name_field);


    while(1) sleep(100);
    return 0;
}
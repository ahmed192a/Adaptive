/**
 * @file event.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "event.h"
#include <unistd.h>
#include <signal.h>
#include <functional>

extern CServer s2; // To use the already opened socket between the server and the client

void (*g_handler)(int, siginfo_t *, void *);

//extern void signal_handler(int signum, siginfo_t *siginfo, void *ucontext){}


namespace ara
{
namespace com
{
namespace proxy_skeleton
{
namespace skeleton
{
Event event_object;
// internal function
// This function will then use the opened socket between the server and the client
// We use the socket to receive the Event_Name "a string containing the variable name"

void Event::setter(int process_id)
{
    Event::subscribers_data.insert(process_id);
    // print_subscribers();
}

void Event::print_subscribers()
{
    // printing set s1
    std::set<int, std::greater<int> >::iterator itr;
    std::cout << "\nThe set event_name is : \n";
    for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++) {
        std::cout << *itr << " ";
    }    
    std::cout << std::endl;
}

// We start the signal code in the constructor "For now"
// When the client send us something "number 2 for now", 
// We execute the signal_handler() "An internal Function"
Event::Event()
{   
    // initializing the event data 
    this->event_data = 5;
    
    pid_t pid = getpid();
    struct sigaction signal_action;

    // We print the server pid to make sure that the client is talking to our server
    std::cout << "receiver: PID is " << pid << std::endl;

    signal_action.sa_sigaction = g_handler;
    sigemptyset (&signal_action.sa_mask);
    signal_action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &signal_action, NULL);
}

void Event::update(int value)
{
    this->event_data = value;
    //sendevent(value , client);
    std::cout << "Udpate" << std::endl;
    notify(value);
}



void Event::notify(int value)
{
    union sigval sigval;
    //int clients = 10;
    // for(auto client : clients)
    // string msg = "update";
    // send(eventname , value , msg);
    sigval.sival_int = value;
    std::set<int, std::greater<int> >::iterator itr;
    std::cout << "\nThe set event_name is : \n";
    for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
    {
        printf("sender: sending %d to PID %d\n", sigval.sival_int, *itr);
        sigqueue(*itr, SIGUSR1, sigval);
    }
    

}

Event::~Event()
{
}



} // skeleton
} // internal
} // com
} // ara

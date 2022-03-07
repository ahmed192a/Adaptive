#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "../../../src/ara/com/ipc/server/socket_Server.h"
#include "../../../src/ara/com/ServiceDiscovery/skeleton.h"
#include "../../../src/ara/com/proxy_skeleton/skeleton/event.h"
#include "lib/data.h"


struct event_info{
    int process_id;
    char event_name[30];
};

using namespace std;

// Client Information
struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};

CServer s2(SOCK_STREAM); // Socket between the server and the client
ara::com::proxy_skeleton::skeleton::Event event1;
ara::com::proxy_skeleton::skeleton::Event event2;

/* Scenario 
* First file we run is the Service Discovery:
* The service discovery is always listening to its socket
* to receive Service Register from the server
* or to receive service discover from the client
* We then run the server whose first thing to do is to OfferService
* using the service disovery portnumber, it sends a struct to service discovery
* containing information about the server + its service
* the last file we run is the client
* the client first task is to request the service discovery to send it service information
* the client gives the service discovery a service id, and later receive a struct containing
* Process id and port number of the server
*/
void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
{
    static int count = 0;
    if (signum != SIGUSR1) return;
    if (siginfo->si_code != SI_QUEUE) return;
    

    printf("receiver: Got value %d\n", siginfo->si_int);
    
    if(siginfo->si_int == 2)
    {
        s2.AcceptServer();
        struct event_info e1;
        s2.ReceiveServer((struct event_info*) &e1, sizeof(struct event_info));
        // std::cout << "Event " << count << " " << e1.event_name << std::endl;  
        std::cout << e1.event_name << endl;
        if (strcmp(e1.event_name, "event1") == 0)
        {
            event1.setter(e1.process_id);
            std::cout << "Event1: " << std::endl;
            event1.print_subscribers();
        }
        else
        {
            event2.setter(e1.process_id);
            std::cout << "Event2: " << std::endl;
            event2.print_subscribers();
        }
        
        
        
        // in the future we are supposed to save the process id and the port number of the client
        // To notify the list of subscribed clients when a change occur to the subscribed variable
        // let's say for now that we'll make a vector for each event contaning pid & port_num of clients
        count++;
    }
}


int main(int argc, char **argv)
{
    
    // just by using Event constructor, we started the signals code "to receive subscription requests"


    ///////////////////////////////////////////////////////////////////////////////////////////////
    // We replaced these commented lines by just using this above object 

    //     pid_t pid = getpid();
    // struct sigaction signal_action;

    // // Event
    // std::cout << "receiver: PID is " << pid << std::endl;

    // signal_action.sa_sigaction = signal_handler;
    // sigemptyset (&signal_action.sa_mask);
    // signal_action.sa_flags = SA_SIGINFO;
    // sigaction(SIGUSR1, &signal_action, NULL);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    // We take the sever port number as the first argument 
    cout << "mypid: " << getpid() << endl;
    int portNum = atoi(argv[1]);

    // We then take object from skeleton, construct it giving
    // (Server port number, service discovery port number, server service id)
    skeleton s1(portNum, atoi(argv[2]), 32);

    // send to service discovery the offered service
    s1.start_service();

    /* TCP with client */
    char buffer[256];
   
    s2.OpenSocket(portNum);
    s2.BindServer();
    s2.ListenServer(1); 
    s2.AcceptServer();
    cout<<"accepted\n";

    strcpy(buffer, "=> Server connected...\n");

    // send a confirmation connect to client
    s2.SendServer(buffer, strlen(buffer));

    struct  C_Info x;
    
    // Receive a struct from client containing the method name and parameters
    s2.ReceiveServer((struct C_Info*) &x, sizeof(struct C_Info));

    // print the requested method
    cout << x.method_name << endl;

    // Perform the requested method then send the result
    s1.method_dispatch(x, s2);

    /////////////////////////////////////////////////////////////////////////////////////
    while (event1.subscribers_data.empty()){}
    event1.update(7);

    sleep(1);
    while (event2.subscribers_data.empty()){}
    event2.update(9);

    cout << "\nGoodbye..." << endl;

    s1.StopOfferService();

    // always be awake to receive stuff from signal
    while(1) sleep(100);
    s2.CloseSocket();
    return 0;    
}

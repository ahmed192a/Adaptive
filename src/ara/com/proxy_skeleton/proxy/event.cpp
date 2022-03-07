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
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <signal.h>

#include "event.h"

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {
                // Event::Event(int data, int pid)
                // {
                //     this->data = data;
                //     this->pid = pid;
                // }

                Event::Event()
                {
                }

                Event::~Event()
                {
                }

                void Event::setter(int port_number, int pid)
                {
                    this->port_number = port_number;
                    this->pid = pid;
                }

                void Event::Subscribe(char event_name[])
                {
                    // we first tried to use signals to send the event_name"string" directly
                    // That was a failed try so we turned into using the code under these comments

                    // union sigval sigval;
                    // char x[30] = "event_name";
                    // sigval.sival_ptr = (char *)x;
                    // printf("sender: sending %s to PID %d\n", (char *)sigval.sival_ptr, this->receive.process_id);
                    // sigqueue(this->receive.process_id, SIGUSR1, sigval);

                    // We first use signals to inform the sever that we wanna subscribe to an event
                    union sigval sigval;
                    sigval.sival_int = 2;
                    printf("sender: sending %d to PID %d\n", sigval.sival_int, this->pid);

                    // here we're sending number 2 to the server
                    sigqueue(this->pid, SIGUSR1, sigval);

                    // then here we open a socket between server and client
                    char hostbuffer[256];
                    CClient c1(SOCK_STREAM);
                    c1.OpenSocket();
                    bzero(hostbuffer, 256);
                    int hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

                    if (hostnameRet < 0)
                    {
                        std::cout << ("Unable to local machine get Host Name\n");
                    }

                    c1.GetHost("127.0.0.1", this->port_number);
                    c1.ClientConnect();

                    // here we're sending the event_name
                    struct event_info e1;
                    e1.process_id = getpid();
                    strcpy(e1.event_name, event_name);
                    c1.ClientWrite((struct event_info *)&e1, sizeof(struct event_info));
                    c1.CloseSocket();
                    /////////////////////////////////////////////////////////////////////////////////////////////
                    // union sigval sigval;

                    // printf("sender: sending %d to PID %d\n", sigval.sival_int, this->pid);
                    // // here we're sending number 2 to the server
                    // sigqueue(this->pid, SIGUSR1, sigval);

                    // CClient c2(SOCK_STREAM);
                    // c2.OpenSocket();
                    // bzero(hostbuffer,256);
                    // hostnameRet = gethostname(hostbuffer, sizeof(hostbuffer));

                    // if(hostnameRet < 0)
                    // {
                    //     std::cout<<("Unable to local machine get Host Name\n");
                    // }

                    // c2.GetHost("127.0.0.1", this->port_number);
                    // c2.ClientConnect();
                    // // here we're sending the event_name
                    // struct event_info e2 = {getpid(), event_name};
                    // c2.ClientWrite((struct event_info*) &e2, sizeof(struct event_info));

                    // c2.CloseSocket();
                }
                // void Event::update(int value)
                // {
                //     this->data = value;
                //     //sendevent(value , client);
                //     notify(value);
                // }

                // void Event::notify(int value)
                // {
                //     union sigval sigval;
                //     sigval.sival_int = value;
                //     printf("sender: sending %d to PID %d\n", sigval.sival_int, this->pid);
                //     sigqueue(this->pid, SIGUSR1, sigval);

                // }
            }
        }
    }
}

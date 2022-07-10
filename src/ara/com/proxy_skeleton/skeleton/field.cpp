/**
 * @file field.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/proxy_skeleton/skeleton/field.hpp"

#include <unistd.h>
#include <signal.h>

// extern CServer s2; // To use the already opened socket between the server and the client

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {

                // internal function
                // This function will then use the opened socket between the server and the client
                // We use the socket to receive the Event_Name "a string containing the variable name"
                // void signal_handler(int signum, siginfo_t *siginfo, void *ucontext)
                // {
                //     if (signum != SIGUSR1) return;
                //     if (siginfo->si_code != SI_QUEUE) return;

                //     printf("receiver: Got value %d\n", siginfo->si_int);

                //     if(siginfo->si_int == 2)
                //     {
                //         s2.AcceptServer();
                //         char x[30] ;
                //         s2.ReceiveServer((char *) &x, sizeof(x));
                //         std::cout << x << std::endl;
                //         // in the future we are supposed to save the process id and the port number of the client
                //         // To notify the list of subscribed clients when a change occur to the subscribed variable
                //         // let's say for now that we'll make a vector for each event contaning pid & port_num of clients
                //     }
                // }
                // template <typename T>
                // Field::Field(ServiceSkeleton* service, std::string name)
                // {

                // }
                // template <typename T>
                // Field<T>::Field
                // (
                //     ServiceSkeleton *service,
                //     std::string name
                // ):Event_S<T>(
                //     service,
                //     name
                // )
                // {
                // }
                // template <typename T>
                // Field<T>::~Field()
                // {
                // }

                // template <typename T>
                // void Field<T>::Update(int data, int pid)
                // {
                //     x = 777;
                //     std::string m_name = "djcnkh";
                //     SendEvent(m_name, x, true, pid);
                // }

                // template <typename T> 
                // void Field<T>::SendEvent(std::string eventName, int data, bool is_field, int pid)
                // {
                //     union sigval sigval;
                //     sigval.sival_int = data;
                //     printf("sender: sending %d to PID %d\n", sigval.sival_int, pid);
                //     sigqueue(pid, SIGUSR1, sigval);
                // }

            } // skeleton
        }     // internal
    }         // com
} // ara
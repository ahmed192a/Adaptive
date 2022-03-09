/**
 * @file event.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_INTERNAL_SKELETON_EVENT_H_
#define ARA_COM_INTERNAL_SKELETON_EVENT_H_

#include <stdlib.h>
#include <unistd.h>
#include <functional>

#include <time.h>
#include <signal.h>
#include <set>
#include <iterator>
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"

// extern void (*g_handler)(int, siginfo_t *, void *);

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {
                namespace EVENT{
                    void set_handle(void (*handler)(int, siginfo_t *, void *));
                }

                template <typename T>
                class Event
                {
                // private:
                    // void (*g_handler)(int, siginfo_t *, void *)
                public:
                    std::set<int> subscribers_data;
                    Event(
                        ServiceSkeleton *service,
                        std::string name)
                        : m_service{service},
                          m_name{name}
                    {
                        // initializing the event data
                        this->event_data = 5;

                        pid_t pid = getpid();

                        // We print the server pid to make sure that the client is talking to our server
                        std::cout << "Event in server's PID -> " << pid << std::endl;


                    }
                    ~Event() {}



                    void set_subscriber(int client_id)
                    {
                        subscribers_data.insert(client_id);
                    }

                    void print_subscribers()
                    {
                        // printing set s1
                        std::set<int, std::greater<int>>::iterator itr;
                        std::cout << "The set event_name is : \n";
                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            std::cout<<"\t=> " <<": "<< *itr << "\n";
                        }
                    }

                    void update(T value)
                    {
                        this->event_data = value;
                        // sendevent(value , client);
                        std::cout <<"Event : "<<m_name<< " is Udpated " << std::endl;
                        notify(value);
                    }

                    /**
                     * @brief 
                     * 
                     * @todo edit the sigval to carry any type not just int 
                     * 
                     * @param value 
                     */
                    void notify(T value)
                    {
                        union sigval sigval;
                        sigval.sival_int = value;
                        std::set<int, std::greater<int>>::iterator itr;
                        std::cout << "\nThe set event_name is : \n";
                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            printf("sender: sending %d to PID %d\n", sigval.sival_int, *itr);
                            sigqueue(*itr, SIGUSR1, sigval);
                        }
                    }

                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;
                    T event_data;
                    

                    // public:
                    //      Event(ServiceSkeleton *service, std::string name)
                    //          :EventBase(service, name)
                    //      {
                    //      }
                    //      void signal_handler(int signum, siginfo_t *siginfo, void *ucontext);

                    //     void Send(const T& data)
                    //     {
                    //         SendEvent(m_name, data, false);
                    //     }

                    //     void Send(ara::com::SampleAllocateePtr<T> data)
                    //     {
                    //         Send(*data);
                    //     }

                    //     ara::com::SampleAllocateePtr<T> Allocate()
                    //     {
                    //         return std::make_unique<T>();
                    //     }

                }; // Event
            }      // skeleton
        }          // internal
    }              // com
} // ara

#endif // ARA_COM_INTERNAL_SKELETON_EVENT_H_

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
#ifndef ARA_COM_PROXY_SKELETON_SKELETON_EVENT_H_
#define ARA_COM_PROXY_SKELETON_SKELETON_EVENT_H_

#include <stdlib.h>
#include <unistd.h>
#include <functional>
#include <algorithm>
#include <time.h>
#include <signal.h>
#include <set>
#include <iterator>
#include "ara/com/proxy_skeleton/skeleton/service_skeleton.hpp"
#include <arpa/inet.h>
// extern void (*g_handler)(int, siginfo_t *, void *);

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {
                namespace EVENT
                {
                    void set_handle(void (*handler)(int, siginfo_t *, void *));
                }

                template <typename T>
                class Event
                {
                    // private:
                    // void (*g_handler)(int, siginfo_t *, void *)
                public:
                    std::vector<ara::com::proxy_skeleton::Client_udp_Info> subscribers_data;
                    T event_data;
                    Event(
                        ServiceSkeleton *service,
                        std::string name,
                        int event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                    }
                    ~Event() {}

                    void set_subscriber(ara::com::proxy_skeleton::Client_udp_Info  client_id)
                    {
                        subscribers_data.push_back(client_id);
                    }

                    void Del_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {

                        subscribers_data.erase(std::remove(subscribers_data.begin(), subscribers_data.end(), client_id), subscribers_data.end());
                        //subscribers_data.erase(client_id);
                        // insert(client_id);
                    }

                    void print_subscribers()
                    {
                        // printing set s1
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info>::iterator itr;
                        std::cout << "the subscribers of " << m_name << " are : \n";
                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            // std::cout << "\t\t=> "<< ": " << *itr << "\n";
                        }
                    }

                    void update(T value)
                    {
                        this->event_data = value;
                        // sendevent(value , client);
                        std::cout << m_name << " is Udpated " << std::endl;
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
                        // union sigval sigval;
                        // sigval.sival_int = value;
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info>::iterator itr;

                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            // printf("sender: sending %d to PID %d\n", sigval.sival_int, *itr);
                            // sigqueue(*itr, SIGUSR1, sigval);
                            sockaddr_in fg;
                            fg.sin_family=AF_INET;
                            fg.sin_port= (*itr).port;
                            inet_pton(AF_INET, (*itr).addr.data(), &fg.sin_addr);
                            
                            m_service->SendEvent<T>(m_event_id, event_data, false,&(fg));
                        }
                    }
                    virtual void handlecall(ara::com::proxy_skeleton::event_info<T> &msg, ara::com::proxy_skeleton::Client_udp_Info client)
                    {
                        switch (msg.operation)
                        {
                        case 0:
                            // new value 
                            // event_data = msg_data;
                            break;
                        case 1:
                            set_subscriber(client);
                            break;
                        case 2:
                            Del_subscriber(client);
                            break;
                        default:
                            break;
                        }
                    }

                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;
                    int m_event_id;

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

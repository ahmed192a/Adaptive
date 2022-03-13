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
                private:
                    /**
                     * @brief
                     *
                     * @todo edit the sigval to carry any type not just int
                     *
                     * @param value
                     */
                    void notify(T value)
                    {
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info>::iterator itr;

                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            sockaddr_in fg;
                            fg.sin_family = AF_INET;
                            fg.sin_port = (*itr).port;
                            inet_pton(AF_INET, (*itr).addr.data(), &fg.sin_addr);
                            m_service->SendEvent<T>(m_event_id, event_data, &fg);
                        }
                    }

                protected:
                    ServiceSkeleton *m_service;
                    std::string m_name;
                    uint32_t m_event_id;
                    T event_data;
                    std::vector<ara::com::proxy_skeleton::Client_udp_Info> subscribers_data;

                public:
                    Event(
                        ServiceSkeleton *service,
                        std::string name,
                        uint32_t event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                    }
                    ~Event() {}

                    void set_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        subscribers_data.push_back(client_id);
                    }

                    void Del_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        subscribers_data.erase(std::remove(subscribers_data.begin(), subscribers_data.end(), client_id), subscribers_data.end());
                    }

                    void print_subscribers()
                    {
                        if(subscribers_data.empty())
                        {
                            std::cout << "the subscribers list of " << m_name << " is empty\n";
                            return ;
                        }
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info>::iterator itr;
                        std::cout << "the subscribers of " << m_name << " are : \n";
                        for (itr = this->subscribers_data.begin(); itr != this->subscribers_data.end(); itr++)
                        {
                            std::cout << "\t\t=> "
                                      << ": " << (*itr).port << "\n";
                        }
                    }

                    void update(T value)
                    {
                        this->event_data = value;
                        std::cout << m_name << " is Udpated " << std::endl;
                        notify(value);
                    }

                    void handlecall(ara::com::proxy_skeleton::event_info &msg, ara::com::proxy_skeleton::Client_udp_Info client)
                    {
                        switch (msg.operation)
                        {
                        case 0:
                            // new value
                            // event_data = msg_data;
                            break;
                        case 1:
                            set_subscriber(client);
                            print_subscribers();
                            break;
                        case 2:
                            Del_subscriber(client);
                            print_subscribers();
                            break;
                        default:
                            break;
                        }
                    }
                    std::vector<ara::com::proxy_skeleton::Client_udp_Info> getsub()
                    {
                        return subscribers_data;
                    }

                }; // Event
            }      // skeleton
        }          // internal
    }              // com
} // ara

#endif // ARA_COM_INTERNAL_SKELETON_EVENT_H_

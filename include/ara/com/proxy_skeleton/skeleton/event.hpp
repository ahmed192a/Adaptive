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
#include "ara/com/proxy_skeleton/skeleton/shared_sub/file.hpp"
#include "ara/com/deserializer.hpp"
#include "ara/com/serializer.hpp"
/**
 * @brief 
 * @todo  mutex on read and write file subcribers
 */
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
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info> subs = subscribers_data.getrows(subname_file.data());
                        for (itr =subs.begin(); itr !=subs.end(); itr++)
                        {
                            sockaddr_in fg;
                            fg.sin_family = AF_INET;
                            fg.sin_port = (*itr).port;
                            inet_pton(AF_INET, (*itr).addr.data(), &fg.sin_addr);
                            m_service->SendEvent<T>(m_event_id, event_data, fg);
                        }
                    }

                protected:
                    ServiceSkeleton *m_service;
                    std::string m_name;
                    uint32_t m_event_id; 
                    T event_data;
                    Subscriber subscribers_data;
                    std::string subname_file;
                    //std::mutex mu;

                public:
                    Event(
                        ServiceSkeleton *service,
                        std::string name,
                        uint32_t event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                        subname_file = m_name + m_service->m_service_id.toString()+ std::to_string(event_id); 
                        subscribers_data.clear(subname_file.data());  
                    }
                    ~Event() {}

                    void set_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        //mu.lock();
                        subscribers_data.write(subname_file.data(),client_id );
                        //mu.unlock();
                    }

                    void Del_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        //mu.lock();
                        subscribers_data.delete_record(subname_file.data(),client_id );
                        //mu.unlock();
                    }

                    void print_subscribers()
                    {
                        if(subscribers_data.getrows(subname_file.data()).empty())
                        {
                            std::cout << "the subscribers list of " << m_name << " is empty\n";
                            return ;
                        }
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info>::iterator itr;
                        std::cout << "the subscribers of " << m_name << " are : \n";
                        std::vector<ara::com::proxy_skeleton::Client_udp_Info> subs = subscribers_data.getrows(subname_file.data());
                        for (itr = subs.begin(); itr != subs.end(); itr++)
                        {
                            std::cout << "\t\t=> "
                                      << ": " << (*itr).port << "\n";
                        }
                    }

                    void update(T value)
                    {
                        event_data = value;
                        std::cout << m_name << " is Udpated " << std::endl;
                        //mu.lock();
                        notify(value);
                        //mu.unlock();
                    }

                    void handlecall(ara::com::proxy_skeleton::event_info &msg,std::vector<uint8_t>&data, ara::com::proxy_skeleton::Client_udp_Info client)
                    {
                        ara::com::Deserializer dser;
                        ara::com::Serializer ser;
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
                        case 3:
                            event_data = dser.deserialize<T>(data,0);
                            break;

                        case 4:
                            ser.serialize(event_data);
                            data = ser.Payload();
                            msg.data_size = data.size();
                            break;
                        default:
                            break;
                        }
                    }
                    std::vector<ara::com::proxy_skeleton::Client_udp_Info> getsub()
                    {
                        return subscribers_data.getrows(subname_file.data());
                    }

                }; // Event
            }      // skeleton
        }          // internal
    }              // com
} // ara

#endif // ARA_COM_INTERNAL_SKELETON_EVENT_H_

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
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
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
                protected:
                    /**
                     * @brief
                     *
                     * @todo edit the sigval to carry any type not just int
                     *
                     */
                    
                    void notify()
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

                
                    ServiceSkeleton *m_service;
                    std::string m_name;
                    uint32_t m_event_id; 
                    T event_data;
                    Subscriber subscribers_data;
                    std::string subname_file;
                    //std::mutex mu;

                public:
                /**
                 * @brief Construct a new Event object
                 * 
                 * @param service 
                 * @param name 
                 * @param event_id 
                 */
                    Event(
                        ServiceSkeleton *service,
                        std::string name,
                        uint32_t event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                        subname_file = m_name + to_string(m_service->m_service_id)+ std::to_string(event_id); 
                        subscribers_data.clear(subname_file.data());  
                    }
                    /**
                     * @brief Destroy the Event object
                     * 
                     */
                    ~Event() {}
                    /**
                     * @brief Set the subscriber object
                     * 
                     * @param client_id 
                     */
                    void set_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        //mu.lock();
                        subscribers_data.write(subname_file.data(),client_id );
                        //mu.unlock();
                    }
                    /**
                     * @brief Delete subscriber
                     * 
                     * @param client_id 
                     */
                    void Del_subscriber(ara::com::proxy_skeleton::Client_udp_Info client_id)
                    {
                        //mu.lock();
                        subscribers_data.delete_record(subname_file.data(),client_id );
                        //mu.unlock();
                    }
                    /**
                     * @brief print_subscribers 
                     *  
                     */
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
                    /**
                     * @brief update event and notify
                     * 
                     * @param value 
                     */
                    virtual void update(T value)
                    {
                        event_data = value;
                        std::cout << m_name << " is Udpated " << std::endl;
                        //mu.lock();
                        notify();
                        //mu.unlock();
                    }
                    /**
                     * @brief subhandlecall to get entry and option of some ip
                     * 
                     * @param sd_msg 
                     * @param client 
                     */
                    void subhandlecall(ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg, ara::com::proxy_skeleton::Client_udp_Info client)
                    {

                        auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];
                        auto option = (ara::com::option::Ipv4EndpointOption *)entry->FirstOptions()[0];
                        client.port = option->Port();
                        uint32_t TTL = entry->TTL();


                        if (TTL == 0)
                        {
                            Del_subscriber(client);
                            print_subscribers();
                        }else{

                            set_subscriber(client);
                            print_subscribers();
                        }
                        


                        // ara::com::Deserializer dser;
                        // ara::com::Serializer ser;
                        //   event_data = dser.deserialize<T>(data,0);
                        // ser.serialize(event_data);
                        // data = ser.Payload();
                        // msg.data_size = data.size();
                    }

                    // void HandleCall(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    // {
                    //     bool op = false;
                    //     std::vector<uint8_t> _data = sd_msg.GetPayload();
                    //     SOMEIP_MESSAGE::Message R_msg(
                    //         SOMEIP_MESSAGE::Message_ID{ (uint16_t)m_service->m_service_id.GetInstanceId(),(uint16_t) (sd_msg.MessageId().method_id|0x8000)},
                    //         SOMEIP_MESSAGE::Request_ID{5,6},
                    //         2, // protocol version
                    //         7, // Interface Version
                    //         SOMEIP_MESSAGE::MessageType::RESPONSE);
                    //     if(_data.size()>0) // SET
                    //     {
                    //         ara::com::Deserializer dser;
                    //         event_data = dser.deserialize<T>(_data,0);
                    //         op = true;

                    //     }else{ // GET
                    //         ara::com::Serializer ser;
                    //         ser.serialize(event_data);
                    //         _data = ser.Payload();
                    //     }
                    //     // Setpayload in message
                    //     R_msg.SetPayload(_data);
                    //     _data = R_msg.Serializer();
                    //     uint32_t msg_size = _data.size();
                    //     // send message
                    //     binding.Send(&msg_size, sizeof(msg_size));
                    //     binding.Send(_data.data(), msg_size);
                    //     binding.CloseSocket();
                    //     if(op) notify();
                    // }
                    /**
                     * @brief get_subscribers
                     * 
                     * @return std::vector<ara::com::proxy_skeleton::Client_udp_Info> 
                     */
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

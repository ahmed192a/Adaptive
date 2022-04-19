/**
 * @file service_proxy.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_INTERNAL_SERVICE_PROXY_H_
#define ARA_COM_INTERNAL_SERVICE_PROXY_H_

#include <iostream>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
#include "ara/com/serializer.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/entry/eventgroup_entry.hpp"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/deserializer.hpp"
#include <cstring>
#include <signal.h>
#include <future>
#include <arpa/inet.h>

#include <queue>
using SD_data = ara::com::proxy_skeleton::SD_data;

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {

                class ServiceProxy
                {
                private:
                    CClient service_proxy_tcp;
                    CClient service_proxy_udp;

                public:
                    struct SP_Handle 
                    {
                        int UDP_port;
                        SD_data m_server_com;
            
                    };

                    SP_Handle m_proxy_handle;
                    // a struct to receive in it the process id & port number
                    //  of the server from service discovery
                    ServiceProxy(SP_Handle proxy_handle); 
                    virtual ~ServiceProxy();
                    static ServiceHandleContainer<SP_Handle> FindService(FindServiceHandle FSH); // we send to the service discovery a request for a specific service

                    template <typename R, typename... Args>
                    R SendRequest(uint32_t method_id, Args &&...args)
                    {

                        SOMEIP_MESSAGE::Message R_msg(
                                SOMEIP_MESSAGE::Message_ID{ (uint16_t) this->m_proxy_handle.m_server_com.service_id, (uint16_t)(method_id&0x7F)},
                                SOMEIP_MESSAGE::Request_ID{5,6},
                                2, // protocol version
                                7, // Interface Version
                                SOMEIP_MESSAGE::MessageType::REQUEST);

                        R result; // to save the result of the method
                        ara::com::Serializer ser;
                        ara::com::Deserializer deser;

                        (ser.serialize(std::forward<Args>(args)), ...);


                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();

                        // get payload of argumnets
                        std::vector<uint8_t> msgser = ser.Payload();
                        // push the payload to the message
                        R_msg.SetPayload(msgser);
                        // get the serialized message
                        msgser = R_msg.Serializer();

                        int msg_size = msgser.size();
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&msgser[0], msg_size);
                        std::cout<<"SEND REQUEST\n";
                        // receive the methods result
                        msgser.clear();
                        service_proxy_tcp.ClientRead((void *)&msg_size, sizeof(msg_size));
                        msgser.resize(msg_size);
                        service_proxy_tcp.ClientRead((void *)&msgser[0], msg_size);
                        service_proxy_tcp.CloseSocket();


                        // deserialize the result
                        SOMEIP_MESSAGE::Message Res_msg = SOMEIP_MESSAGE::Message::Deserialize(msgser);
                        // get the payload
                        std::vector<uint8_t> _data_payload = Res_msg.GetPayload();
                        // deserialize the payload
                        result = deser.deserialize<R>(_data_payload,0);
                        return result;
                    }

                    template <typename R>
                    R SendRequest(uint32_t method_id)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                                SOMEIP_MESSAGE::Message_ID{ (uint16_t) this->m_proxy_handle.m_server_com.service_id, (uint16_t)method_id},
                                SOMEIP_MESSAGE::Request_ID{5,6},
                                2, // protocol version
                                7, // Interface Version
                                SOMEIP_MESSAGE::MessageType::REQUEST);

                        R result; // to save the result of the method
                        ara::com::Serializer ser;
                        ara::com::Deserializer deser;

                        ser.serialize(method_id);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);

                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();
                        service_proxy_tcp.ClientRead(buffer, bufsize);

                        // get payload of argumnets
                        std::vector<uint8_t> msgser = ser.Payload();
                        // push the payload to the message
                        R_msg.SetPayload(msgser);
                        // get the serialized message
                        msgser = R_msg.Serializer();
                        
                        int msg_size = msgser.size();
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&msgser[0], msg_size);
                        msgser.clear();
                        service_proxy_tcp.ClientRead((void *)&msg_size, sizeof(msg_size));
                        msgser.resize(msg_size);
                        service_proxy_tcp.ClientRead((void *)&msgser[0], msg_size);
                        service_proxy_tcp.CloseSocket();

                        // deserialize the result
                        SOMEIP_MESSAGE::Message Res_msg = SOMEIP_MESSAGE::Message::Deserialize(msgser);
                        // get the payload
                        std::vector<uint8_t> _data_payload = Res_msg.GetPayload();
                        // deserialize the payload
                        result = deser.deserialize<R>(_data_payload,0);

                        return result;
                    }

                    template <typename R>
                    R SendRequest( std::vector<uint8_t> data)
                    {
                        ara::com::Deserializer deser;
                        R result; 
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);
                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();
                        service_proxy_tcp.ClientRead(buffer, bufsize);

                        int msg_size = data.size();
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&data[0], msg_size);
                        std::vector<uint8_t> msgser;
                        service_proxy_tcp.ClientRead((void *)&msg_size, sizeof(msg_size));
                        msgser.reserve(msg_size);
                        service_proxy_tcp.ClientRead((void *)&msgser[0], msg_size);  
                        service_proxy_tcp.CloseSocket();

                        // deserialize the result
                        SOMEIP_MESSAGE::Message Res_msg = SOMEIP_MESSAGE::Message::Deserialize(msgser);
                        // get the payload
                        std::vector<uint8_t> _data_payload = Res_msg.GetPayload();
                        // deserialize the payload
                        result = deser.deserialize<R>(_data_payload,0);

                        return result;
                    }

                    template <typename... Args>
                    void SendFireAndForgetRequest(uint32_t method_id, Args &&...args)
                    {
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
                        (ser.serialize(std::forward<Args>(args)), ...);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);
                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();
                        service_proxy_tcp.ClientRead(buffer, bufsize);
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&msgser[0], msg_size);
                        service_proxy_tcp.CloseSocket();
                    }

                    void SendFireAndForgetRequest(uint32_t method_id)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                                SOMEIP_MESSAGE::Message_ID{ (uint16_t) this->m_proxy_handle.m_server_com.service_id, (uint16_t)method_id},
                                SOMEIP_MESSAGE::Request_ID{5,6},
                                2, // protocol version
                                7, // Interface Version
                                SOMEIP_MESSAGE::MessageType::REQUEST);
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);

                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();
                        service_proxy_tcp.ClientRead(buffer, bufsize); // read confirmation
                        
                        std::vector<uint8_t> msgser = ser.Payload();
                        R_msg.SetPayload(msgser);
                        int msg_size = msgser.size(); // sizeof = 4 bytes
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&msgser[0], msg_size);
                        service_proxy_tcp.CloseSocket();
                    }

                    // event
                    void EventSubscribe(int event_id)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        int pport = htons(m_proxy_handle.UDP_port);

                        ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage m_info;
                        ara::com::entry::EventgroupEntry event_gr_entry = ara::com::entry::EventgroupEntry::CreateSubscribeEventEntry ((uint16_t) this->m_proxy_handle.m_server_com.service_id, 
                                                                                        (uint16_t) this->m_proxy_handle.m_server_com.service_id,
                                                                                         1, // major version
                                                                                          event_id);


                        ara::com::option::Ipv4EndpointOption sub_option = ara::com::option::Ipv4EndpointOption::CreateSdEndpoint(false, 
                                                                                        ara::com::helper::Ipv4Address(127, 0, 0, 1),
                                                                                         option::Layer4ProtocolType::Udp, 
                                                                                         pport); 



                        event_gr_entry.AddFirstOption(&sub_option);
                        m_info.AddEntry(&event_gr_entry);

                        std::vector<uint8_t>_payload = m_info.Serializer();
                        uint32_t _payload_size = _payload.size();

                        // event_info e_info;
                        // e_info.operation = 1;
                        // e_info.event_id = event_id;
                        // e_info.service_id = m_proxy_handle.m_server_com.service_id;
                        // e_info.data_size = (sizeof(pport));
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)&_payload[0], _payload_size, (sockaddr *)&serv_addr);
                        service_proxy_udp.CloseSocket();

                        
                    }
                    void EventUnsubscribe(int event_id)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        SOMEIP_MESSAGE::sd::SomeIpSDMessage m_info;
                        entry::EventgroupEntry event_gr_entry = entry::EventgroupEntry::CreateUnsubscribeEventEntry ((uint16_t) this->m_proxy_handle.m_server_com.service_id, 
                                                                                        (uint16_t) this->m_proxy_handle.m_server_com.service_id,
                                                                                        1, // major version
                                                                                        event_id);

                        int pport = htons(m_proxy_handle.UDP_port);
                        option::Ipv4EndpointOption sub_option = option::Ipv4EndpointOption::CreateSdEndpoint(false,
                                                                                        helper::Ipv4Address(127, 0, 0, 1),
                                                                                        option::Layer4ProtocolType::Udp,
                                                                                        pport); 
                        event_gr_entry.AddFirstOption(&sub_option);
                        m_info.AddEntry(&event_gr_entry);

                        std::vector<uint8_t>_payload = m_info.Serializer();
                        uint32_t _payload_size = _payload.size();

                        // event_info e_info;
                        // e_info.operation = 2;
                        // e_info.event_id = event_id;
                        // e_info.service_id = m_proxy_handle.m_server_com.service_id;
                        // e_info.data_size = 0;
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)_payload.data(), _payload_size, (sockaddr *)&serv_addr);
                        service_proxy_udp.CloseSocket();
                    }

                    void Field_get(ara::com::proxy_skeleton::event_info &f_get, std::vector<uint8_t> &data)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        socklen_t slen = sizeof(serv_addr);

                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        ara::com::SOMEIP_MESSAGE::Message get_msg({(uint16_t) (f_get.service_id), (uint16_t) (f_get.event_id | 0x8000)},
                        {5,6},
                        5, // protocol verion
                        6, // interface version
                        ara::com::SOMEIP_MESSAGE::MessageType::REQUEST);
                        std::vector<uint8_t>_payload = get_msg.Serializer();
                        uint32_t _payload_size = _payload.size();
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)_payload.data(), _payload_size, (sockaddr *)&serv_addr);
                        _payload.clear();
                        service_proxy_udp.UDPRecFrom((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr, &slen);
                        service_proxy_udp.UDPRecFrom((void *)_payload.data(), _payload_size, (sockaddr *)&serv_addr, &slen);
                        ara::com::SOMEIP_MESSAGE::Message R_get_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(_payload);
                        service_proxy_udp.CloseSocket();
                        data = R_get_msg.GetPayload();
                    }
                    void Field_set(ara::com::proxy_skeleton::event_info &f_set, std::vector<uint8_t> &data)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        socklen_t slen = sizeof(serv_addr);

                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        ara::com::SOMEIP_MESSAGE::Message set_msg({(uint16_t) f_set.service_id, (uint16_t) (f_set.event_id | 0x8000)},
                        {5,6},
                        5, // protocol verion
                        6, // interface version
                        ara::com::SOMEIP_MESSAGE::MessageType::REQUEST);
                        set_msg.SetPayload(data);
                        std::vector<uint8_t>_payload = set_msg.Serializer();
                        uint32_t _payload_size = _payload.size();
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)_payload.data(), _payload_size, (sockaddr *)&serv_addr);
                        _payload.clear();
                        service_proxy_udp.UDPRecFrom((void *)&_payload_size, sizeof(_payload_size), (sockaddr *)&serv_addr, &slen);
                        service_proxy_udp.UDPRecFrom((void *)_payload.data(), _payload_size, (sockaddr *)&serv_addr, &slen);
                        ara::com::SOMEIP_MESSAGE::Message R_get_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(_payload);
                        service_proxy_udp.CloseSocket();
                        data = R_get_msg.GetPayload();
                    }
                };

            } // proxy
        }     // internal
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_SERVICE_PROXY_H_

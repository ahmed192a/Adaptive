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
                        // std::cout<<"Sending request\n";
                        R result; // to save the result of the method
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
                        (ser.serialize(std::forward<Args>(args)), ...);
                        std::vector<uint8_t> resdes;

                        int bufsize = 256; // dummy buffer to get connection confirmation
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);

                        service_proxy_tcp.OpenSocket();
                        service_proxy_tcp.GetHost("127.0.0.1", this->m_proxy_handle.m_server_com.port_number);
                        service_proxy_tcp.ClientConnect();
                        service_proxy_tcp.ClientRead(buffer, bufsize); // get confirmation
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        service_proxy_tcp.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        service_proxy_tcp.ClientWrite(&msgser[0], msg_size);
                        // receive the methods result
                        service_proxy_tcp.ClientRead((void *)&result, sizeof(result));
                        service_proxy_tcp.CloseSocket();
                        return result;
                    }

                    template <typename R>
                    R SendRequest(uint32_t method_id)
                    {
                        R result; // to save the result of the method
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
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
                        service_proxy_tcp.ClientRead((int *)&result, sizeof(result));
                        service_proxy_tcp.CloseSocket();
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

                        event_info e_info;
                        e_info.operation = 1;
                        e_info.event_id = event_id;
                        e_info.service_id = m_proxy_handle.m_server_com.service_id;
                        e_info.data_size = (sizeof(pport));

                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&e_info, sizeof(e_info), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)&pport, sizeof(pport), (sockaddr *)&serv_addr);
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
                        event_info e_info;
                        e_info.operation = 2;
                        e_info.event_id = event_id;
                        e_info.service_id = m_proxy_handle.m_server_com.service_id;
                        e_info.data_size = 0;
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&e_info, sizeof(e_info), (sockaddr *)&serv_addr);
                        service_proxy_udp.CloseSocket();
                    }

                    void Field_get(ara::com::proxy_skeleton::event_info &f_get, std::vector<uint8_t> &data)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        f_get.data_size = 0;
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&f_get, sizeof(f_get), (sockaddr *)&serv_addr);
                        socklen_t slen = sizeof(serv_addr);
                        service_proxy_udp.UDPRecFrom((void *)&data[0], data.size(), (sockaddr *)&serv_addr, &slen);
                        service_proxy_udp.CloseSocket();
                    }
                    void Field_set(ara::com::proxy_skeleton::event_info &f_set, std::vector<uint8_t> &data)
                    {
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(m_proxy_handle.m_server_com.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        f_set.data_size = data.size();
                        service_proxy_udp.OpenSocket();
                        service_proxy_udp.UDPSendTo((void *)&f_set, sizeof(f_set), (sockaddr *)&serv_addr);
                        service_proxy_udp.UDPSendTo((void *)&data[0], data.size(), (sockaddr *)&serv_addr);
                        service_proxy_udp.CloseSocket();
                    }
                };

            } // proxy
        }     // internal
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_SERVICE_PROXY_H_

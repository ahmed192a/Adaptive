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
                    CClient Cient_Server_connection;

                protected:
                public:
                    class SP_Handle
                    {
                    public:
                        CServer *m_client_UPD;
                        uint32_t m_SD_PortNum;
                        SP_Handle(CServer *client_UPD, uint32_t SD_PortNum)
                            : m_client_UPD{client_UPD},
                              m_SD_PortNum{SD_PortNum}
                        {
                        }
                        ~SP_Handle()
                        {
                        }
                    };

                    // CServer *Cient_Server_connection_DG;
                    SP_Handle *m_proxy_handle;
                    int m_service_id;
                    // a struct to receive in it the process id & port number
                    //  of the server from service discovery
                    SD_data server_handle;
                    ServiceProxy(SP_Handle *proxy_handle);
                    virtual ~ServiceProxy();
                    int FindService(int service_id); // we send to the service discovery a request for a specific service

                    template <typename R, typename... Args>
                    R SendRequest(uint32_t method_id, Args &&...args)
                    {
                        R result; // to save the result of the method
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
                        (ser.serialize(std::forward<Args>(args)), ...);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);
                        Cient_Server_connection.OpenSocket();
                        Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();
                        Cient_Server_connection.ClientRead(buffer, bufsize);
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                        // receive the methods result
                        Cient_Server_connection.ClientRead((int *)&result, sizeof(result));
                        Cient_Server_connection.CloseSocket();
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
                        Cient_Server_connection.OpenSocket();
                        Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();
                        Cient_Server_connection.ClientRead(buffer, bufsize);
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                        Cient_Server_connection.ClientRead((int *)&result, sizeof(result));
                        Cient_Server_connection.CloseSocket();
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
                        Cient_Server_connection.OpenSocket();
                        Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();
                        Cient_Server_connection.ClientRead(buffer, bufsize);
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                        Cient_Server_connection.CloseSocket();
                    }

                    void SendFireAndForgetRequest(uint32_t method_id)
                    {
                        ara::com::Serializer ser;
                        ser.serialize(method_id);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);
                        Cient_Server_connection.OpenSocket();
                        Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();
                        Cient_Server_connection.ClientRead(buffer, bufsize); // read confirmation
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();//sizeof = 4 bytes
                        Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                        Cient_Server_connection.CloseSocket();
                    }

                    // event
                    template <typename T>
                    void EventSubscribe(int event_id)
                    {
                        Serializer ser;

                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        event_info e_info;
                        e_info.operation = 1;
                        e_info.event_id = event_id;
                        e_info.service_id = m_service_id;

                        int obj_size = sizeof(e_info);
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&obj_size, sizeof(obj_size), (sockaddr *)&serv_addr);
                        
                        // int data_size = obj_size - 9;
                        // ser.serialize(obj_size);
                        ser.serialize(e_info);
                        std::vector<uint8_t> msgser = ser.Payload();
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&msgser[0], sizeof(msgser), (sockaddr *)&serv_addr);
                    }
                    template <typename T>
                    void EventUnsubscribe(int event_id)
                    {
                        Serializer ser;
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        event_info e_info;
                        e_info.operation = 2;
                        e_info.event_id = event_id;
                        e_info.service_id = m_service_id;
                        int obj_size = sizeof(e_info);
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&obj_size, sizeof(obj_size), (sockaddr *)&serv_addr);
                        // ser.serialize(obj_size);
                        ser.serialize(e_info);
                        std::vector<uint8_t> msgser = ser.Payload();
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&msgser[0], sizeof(msgser), (sockaddr *)&serv_addr);
                    }

                    void Field_get(ara::com::proxy_skeleton::event_info &f_get)
                    {
                        ara::com::Serializer ser;
                        uint32_t size = sizeof(f_get);
                        ser.serialize(size);
                        ser.serialize(f_get);
                        std::vector<uint8_t> msg = ser.Payload();

                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&msg[0], msg.size(), (sockaddr *)&serv_addr);
                        socklen_t slen = sizeof(serv_addr);
                        m_proxy_handle->m_client_UPD->UDPRecFrom(&f_get, sizeof(f_get), (sockaddr *)&serv_addr, &slen);
                    }
                    void Field_set(ara::com::proxy_skeleton::event_info &f_set)
                    {
                        ara::com::Serializer ser;
                        uint32_t size = sizeof(f_set);
                        ser.serialize(size);
                        ser.serialize(f_set);
                        std::vector<uint8_t> msg = ser.Payload();

                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                        }
                        m_proxy_handle->m_client_UPD->UDPSendTo((void *)&msg[0], msg.size(), (sockaddr *)&serv_addr);
                    }
                };

            } // proxy
        }     // internal
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_SERVICE_PROXY_H_

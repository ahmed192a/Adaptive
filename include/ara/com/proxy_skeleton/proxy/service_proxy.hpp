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
                    const int SD_PortNum = 1690;
                    CClient Cient_Server_connection;

                protected:
                public:
                    CServer *Cient_Server_connection_DG;
                    int m_service_id;
                    SD_data server_handle; // a struct to receive in it the process id & port number of the server from service discovery
                    ServiceProxy(CServer *client_UPD);
                    virtual ~ServiceProxy();
                    int FindService(int service_id); // we send to the service discovery a request for a specific service

                    // send to the server a requested method
                    // template <typename... Args>
                    // int SendRequest(Args &&...args)
                    // {
                    //     ara::com::Serializer ser;
                    //     (ser.serialize(std::forward<Args>(args)), ...);
                    //     int bufsize = 256;
                    //     char buffer[bufsize];
                    //     memset(buffer, '\0', bufsize);
                    //     Cient_Server_connection.OpenSocket();
                    //     Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                    //     Cient_Server_connection.ClientConnect();
                    //     Cient_Server_connection.ClientRead(buffer, bufsize);
                    //     std::vector<uint8_t> msgser = ser.Payload();
                    //     int msg_size = msgser.size();
                    //     Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                    //     Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                    //     int result; // to save the result of the method
                    //     // receive the methods result
                    //     Cient_Server_connection.ClientRead((int *)&result, sizeof(result));
                    //     Cient_Server_connection.CloseSocket();
                    //     return result;
                    // }


                    template <typename R, typename... Args>
                    R SendRequest(uint32_t method_id,Args &&...args)
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
                        R result; // to save the result of the method
                        // receive the methods result
                        Cient_Server_connection.ClientRead((int *)&result, sizeof(result));
                        Cient_Server_connection.CloseSocket();
                        return result;
                        // R s;
                        // return s;
                    }

                    template <typename R>
                    R SendRequest(uint32_t method_id)
                    {
                        R s;
                        return s;
                    }

                    template <typename... Args>
                    void SendFireAndForgetRequest(uint32_t method_id, Args &&...args)
                    {
                    }

                    void SendFireAndForgetRequest(uint32_t method_id)
                    {
                    }

                    // event
                    template <typename T>
                    void EventSubscribe(int event_id)
                    {
                        // Cient_Server_connection.OpenSocket();
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        // std::cout << "sub port num" << server_handle.port_number << std::endl;
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                            // return -1;
                        }
                        event_info<T> e_info;
                        e_info.operation = 1;
                        e_info.event_id = event_id;
                        e_info.service_id = m_service_id;
                        Cient_Server_connection_DG->UDPSendTo((void *)&e_info, sizeof(e_info), (sockaddr *)&serv_addr);
                        // Cient_Server_connection.CloseSocket();
                    }
                    template <typename T>
                    void EventUnsubscribe(int event_id)
                    {
                        // Cient_Server_connection.OpenSocket();
                        struct sockaddr_in serv_addr;
                        serv_addr.sin_family = AF_INET;
                        serv_addr.sin_port = htons(server_handle.port_number);
                        // std::cout << "sub port num" << server_handle.port_number << std::endl;
                        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
                        {
                            printf("\nInvalid address/ Address not supported \n");
                            // return -1;
                        }
                        event_info<T> e_info;
                        e_info.operation = 2;
                        e_info.event_id = event_id;
                        e_info.service_id = m_service_id;
                        Cient_Server_connection_DG->UDPSendTo((void *)&e_info, sizeof(e_info), (sockaddr *)&serv_addr);
                        // Cient_Server_connection.CloseSocket();
                    }

                    // HandleType m_handle;
                    // std::shared_ptr<binding_base_type> m_binding;
                    // std::map<std::string, std::function<void(std::shared_ptr<std::vector<uint8_t>>)>> m_eventHandlers;
                    // std::mutex m_mutexHandler;
                    // std::queue<std::shared_ptr<Message>> m_messages;
                    // std::mutex m_mutexMessage;
                    // std::condition_variable m_conditionMessages;
                    // bool m_terminated;
                    // std::vector<std::shared_ptr<ara::core::Promise<void>>> m_thread_joins;
                };

            } // proxy
        }     // internal
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_SERVICE_PROXY_H_

// service_proxy inherit event wa field
// proxy zy ucm,sm kda by inherit service_proxy wa kda by2dr yst5dm kol hagat event wa field

// class HandleType
// {
// // public:
//     bool operator==(const HandleType& other) const;
//     bool operator<(const HandleType& other) const;
//     HandleType& operator=(const HandleType& other);
//     const ara::com::InstanceIdentifier& GetInstanceId() const;

// private:
//     HandleType(std::string name, const ara::com::InstanceIdentifier& instance, ara::com::internal::NetWorkBindingType bindingType, uint16_t clientId);
//     std::string m_name;
//     ara::com::InstanceIdentifier m_instance;
//     ara::com::internal::NetWorkBindingType m_bindingType;
//     uint16_t m_clientId;

//     friend ServiceProxy;
// };

// ServiceProxy(std::string name, HandleType& handle);
// virtual ~ServiceProxy();

// void Subscribe();

// static ara::com::ServiceHandleContainer<HandleType> FindService(
//     std::string serviceName,
//     ara::com::InstanceIdentifier instance = ara::com::InstanceIdentifier::Any);

// static ara::com::FindServiceHandle StartFindService(
//     std::string serviceName,
//     ara::com::FindServiceHandler<HandleType> handler,
//     ara::com::InstanceIdentifier instance = ara::com::InstanceIdentifier::Any);

// static ara::com::FindServiceHandle StartFindService(
//     std::string serviceName,
//     ara::com::FindServiceHandlerExt<HandleType> handler,
//     ara::com::InstanceIdentifier instance = ara::com::InstanceIdentifier::Any);

// static void StopFindService(ara::com::FindServiceHandle handle);

//     void init();
// friend Event;
// private:
// int server_port_number; // to save the received port number from the service discovery
// void processMessage();

// void SetEventReceiveHandler(std::string name, std::function<void(std::shared_ptr<std::vector<uint8_t>>)> handler);
// void UnsetEventReceiveHandler(std::string name);
// void SetEventSubscriptionStateChangeHandler(std::string name, ara::com::SubscriptionStateChangeHandler handler);
// void UnsetEventSubscriptionStateChangeHandler(std::string name);
// ara::com::e2exf::E2EResult GetE2EResult(std::string name);

// template <typename T>
// void UpdateEventSample(std::string name,
//     ara::com::SampleContainer<ara::com::SamplePtr<const T>>& samples,
//     std::vector<std::shared_ptr<std::vector<uint8_t>>> payloads,
//     ara::com::FilterFunction<T> filter, size_t cacheSize = 1)
// {
//     m_binding->UpdateEventSample<T>(name, samples, payloads, filter, cacheSize);
// }

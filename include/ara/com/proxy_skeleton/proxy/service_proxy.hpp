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
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/serializer.hpp"

#include <cstring>
#include <signal.h>
#include <future>

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

                public:
                    int m_service_id;
                    SD_data server_handle; // a struct to receive in it the process id & port number of the server from service discovery
                    ServiceProxy();
                    virtual ~ServiceProxy();
                    int FindService(int service_id); // we send to the service discovery a request for a specific service

                    // send to the server a requested method
                    template <typename... Args>
                    int SendRequest(Args &&...args)
                    {
                        ara::com::Serializer ser;
                        (ser.serialize(std::forward<Args>(args)), ...);
                        int bufsize = 256;
                        char buffer[bufsize];
                        memset(buffer, '\0', bufsize);

                        Cient_Server_connection.OpenSocket();

                        // talk to the server using the received port number
                        Cient_Server_connection.GetHost("127.0.0.1", this->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();

                        // Receive a confirmation message from the server
                        Cient_Server_connection.ClientRead(buffer, bufsize);

                        C_Info x = {getpid(), "add", 3, 2};
                        std::vector<uint8_t> msgser = ser.Payload();
                        int msg_size = msgser.size();
                        Cient_Server_connection.ClientWrite((void *)&msg_size, sizeof(msg_size));
                        Cient_Server_connection.ClientWrite(&msgser[0], msg_size);
                        // printf("%d - %d - %d - %d \n", msgser[4],msgser[5],msgser[6],msgser[7]);
                        
                        // send the requested method, and the parameters
                        Cient_Server_connection.ClientWrite(&x, sizeof(C_Info));


                        int result; // to save the result of the method

                        // receive the methods result
                        Cient_Server_connection.ClientRead((int *)&result, sizeof(result));


                        Cient_Server_connection.CloseSocket();

                        return result;
                    }

                    template <typename... Args>
                    std::future<void> SendRequest(std::string name, Args &&...args)
                    {
                        std::future<void> f;

                        // f = m_binding->SendRequest(name, std::forward<Args>(args)...);

                        return f;
                    }

                    template <typename R, typename... Args>
                    std::future<R> SendRequest(std::string name, Args &&...args)
                    {
                        std::future<R> f;

                        // f = m_binding->SendRequest<R>(name, std::forward<Args>(args)...);

                        return f;
                    }

                    template <typename R>
                    std::future<R> SendRequest(std::string name)
                    {
                        std::future<R> f;

                        // f = m_binding->SendRequest<R>(name);

                        return f;
                    }

                    template <typename... Args>
                    void SendFireAndForgetRequest(std::string name, Args &&...args)
                    {
                        // m_binding->SendFireAndForgetRequest(name, std::forward<Args>(args)...);
                    }

                    void SendFireAndForgetRequest(std::string name)
                    {
                        // m_binding->SendFireAndForgetRequest(name);
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

// protected:
//     void init();
// friend Event;
// private:
// int server_port_number; // to save the received port number from the service discovery
// void processMessage();

// event
// void EventSubscribe(std::string name);
// void EventUnsubscribe(std::string name);
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

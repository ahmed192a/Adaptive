/**
 * @file service_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_
#define ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

// #include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/marshal.hpp"
#include <utility>
#include <unistd.h>
#include "ara/com/serializer.hpp"
// #include <map>
#include <queue>
#include <future>

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {

                class ServiceSkeleton
                {
                public:
                    ServiceSkeleton(
                        std::string name,
                        int portNum,
                        int sd_portNum,
                        int service_id,
                        ara::com::InstanceIdentifier instance,
                        CServer *server_UDP,
                        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
                        : m_instance(instance.GetInstanceId()),
                          m_name{name},
                          portNumber{portNum},
                          service_descovery_port_number{sd_portNum}, 
                          service_id{service_id},
                          m_mode{mode},
                          server_client_connenction{server_UDP}
                    {
                    }

                    virtual ~ServiceSkeleton() {}

                    virtual void OfferService() 
                    {
                        SD_data service = {service_id, getpid() ,portNumber, true};

                        this->cliaddr.sin_family = AF_INET; // IPv4
                        this->cliaddr.sin_addr.s_addr = INADDR_ANY;
                        this->cliaddr.sin_port = htons(service_descovery_port_number);

                        this->server_client_connenction->UDPSendTo(( SD_data*)&service, sizeof( SD_data), ( struct sockaddr *) &this->cliaddr);
                    }

                    void StopOfferService() 
                    {
                        SD_data service = {service_id, getpid() ,portNumber, false};

                        this->server_client_connenction->UDPSendTo((  void *)&service, sizeof( SD_data), ( struct sockaddr *) &this->cliaddr);
                        int x;
                        socklen_t len = sizeof(this->cliaddr);
                    }

                    // std::future<bool> ProcessNextMethodCall(){}
                    template <typename T>
                    void SendEvent(int event_id, const T &data, bool is_field, sockaddr_in *client_add)
                    {
                        ara::com::Serializer ser;
                        ser.serialize(data);
                        ara::com::proxy_skeleton::event_info msg_;
                        msg_.service_id = m_instance.GetInstanceId();
                        msg_.event_id = event_id;
                        msg_.data = ser.Payload();
                        ser.Clear();
                        uint32_t size = sizeof(msg_);
                        ser.serialize(size);
                        ser.serialize(msg_);
                        std::vector<uint8_t> msg = ser.Payload();
                        // server_client_connenction.OpenSocket();
                        server_client_connenction->UDPSendTo((void *)&msg[0], msg.size(), (sockaddr *)client_add);
                        // server_client_connenction->UDPSendTo((void *)&data, sizeof(data), (sockaddr *)client_add);
                        // server_client_connenction.CloseSocket();
                    }

                protected:
                    void init() {}
                    // virtual void DispatchMethodCall(Message msg, std::shared_ptr<int> binding) = 0;

                    template <typename Class, typename R, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(Args...),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     sHandleCall(c, method, msg, binding, std::index_sequence_for(Args...));
                    // }

                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(Args...),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     sHandleCall(c, method, msg, binding, std::index_sequence_for(Args...));
                    // }

                    template <typename Class, typename R>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     std::future<R> f = (c.*method)();
                    //    // f.then([this, msg, binding](std::future<R> &&f) -> bool
                    //    //        {
                    //         R r = f.get();

                    //         binding.Send(&r, sizeof(int));
                    //         binding.CloseSocket();
                    //      //   return true; });
                    // }

                    template <typename Class>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     std::future<void> f = (c.*method)();
                    //     //f.then([this, msg, binding](std::future<void> &&f) -> bool
                    //     //       {
                    //         f.get();

                    //         binding.Send(&msg, sizeof(int));
                    //         binding.ClientClose();
                    //     //    return true; });
                    // }

                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     sHandleCall(c, method, msg, binding, std::index_sequence_for(Args...));
                    // }

                    template <typename Class>
                    void HandleCall(Class &c,
                                    void (Class::*method)(),
                                    Message msg,
                                    Socket &binding);
                    // {
                    //     (c.*method)();
                    // }

                    template <typename T>
                    std::future<T> NoHandler()
                    {
                        std::promise<T> p;
                        try
                        {
                            // code that may throw
                            throw std::runtime_error("Field No Handler");
                        }
                        catch (...)
                        {
                            try
                            {
                                // store anything thrown in the promise
                                p.set_exception(std::current_exception());
                            }
                            catch (...)
                            {
                            } // set_exception() may throw too
                        }

                        return p.get_future();
                    }

                    bool HasRequest();

                    void ProcessRequest();

                private:
                    int portNumber; /* Server PortNumber */
                    int service_id;
                    int service_descovery_port_number;
                    struct sockaddr_in cliaddr;

                    template <typename Class, typename R, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<R> (Class::*method)(Args...),
                                     Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg.payload);

                        // std::shared_ptr<std::promise<R>> p = std::make_shared<std::promise<R>>();
                        // std::future<R> f = p->get_future();
                        std::future<void> f = (c.*method)(unmarshaller.template unmarshal<index>()...);
                        // std::future<R> f = (c.*method)(unmarshaller.template unmarshal<index>()...);
                        // p->set_value((c.*method)(unmarshaller.template unmarshal<index>()...));

                        // f.then([this, msg, binding](std::future<R> &&f) -> bool
                        //       {
                        R r = f.get();
                        // get the data then serialize it and send it
                        binding.Send(&r, sizeof(int));
                        binding.CloseSocket();
                        // return true; });
                    }
                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<void> (Class::*method)(Args...),
                                     Message msg,
                                     Socket binding,
                                     std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg.payload);

                        std::future<void> f = (c.*method)(unmarshaller.template unmarshal<index>()...);

                        // f.then([this, msg, binding](std::future<void> &&f) -> bool
                        //        {
                        // TO DO: no return value but return result
                        f.get();
                        // get the data then serialize it and send it

                        binding.Send(&msg, sizeof(int));
                        binding.CloseSocket();
                        // return true; });
                    }

                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     void (Class::*method)(Args...),
                                     Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg.payload);
                        (c.*method)(unmarshaller.template unmarshal<index>()...);
                    }

                    std::string m_name;
                    int m_fd;
                    ara::com::InstanceIdentifier m_instance;
                    ara::com::MethodCallProcessingMode m_mode;
                    CServer *server_client_connenction;

                    // bool m_terminated;
                    // std::queue<std::shared_ptr<Message>> m_requestMessages;
                    // std::mutex m_mutex;
                    // std::condition_variable m_condition;
                    // std::vector<std::shared_ptr<std::promise<void>>> m_thread_joins;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

/**
 * @file service_skeleton.h
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

#include "com/proxy_skeleton/service_base.h"
#include "com/proxy_skeleton/definitions.h"
#include "data_type.h"
#include "core/future.h"
#include "ipc/server/socket_Server.h"
#include "marshal.h"

#include <map>
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

                class ServiceSkeleton : public ara::com::proxy_skeleton::ServiceBase
                {
                public:
                    ServiceSkeleton(
                        std::string name,
                        ara::com::InstanceIdentifier instance,
                        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
                        : ServiceBase(name), m_instance(instance.GetInstanceId())
                    {
                        m_name = name;
                        m_mode = mode;
                    }

                    virtual ~ServiceSkeleton();

                    void OfferService();

                    void StopOfferService();

                    std::future<bool> ProcessNextMethodCall();

                protected:
                    void init();
                    virtual void DispatchMethodCall(Message msg, std::shared_ptr<int> binding) = 0;

                    template <typename Class, typename R, typename... Args>
                    void HandleCall(Class &c,
                                    ara::core::Future<R> (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding)
                    {
                        sHandleCall(c, method, msg,binding, std::index_sequence_for(Args...));
                       
                    }
                    template <typename Class, typename R, typename... Args, std::size_t... index>
                    void sHandleCall(Class& c,
                                    ara::core::Future<R> (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding,
                                    std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg->payload);
                        ara::core::Future<R> f = (c.*method)(unmarshaller.template unmarshal<index>()...);

                        f.then([this, msg](ara::core::Future<R> &&f) -> bool
                        {
                            R r = f.get();
                            // get the data then serialize it and send it
                            binding.SendServer(&r, sizeof(int));
                            binding.ClientClose();
                            return true; 
                        });
                    }

                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    ara::core::Future<void> (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding)
                    {
                        sHandleCall(c, method, msg, binding,std::index_sequence_for(Args...));
                    }
                    template <typename Class,typename... Args, std::size_t... index>
                    void sHandleCall(Class& c,
                                    ara::core::Future<void> (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding,
                                    std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg->payload);

                        ara::core::Future<R> f = (c.*method)(unmarshaller.template unmarshal<index>()...);

                        f.then([this, msg](ara::core::Future<R> &&f) -> bool
                        {
                            // TO DO: no return value but return result
                            f.get();
                            // get the data then serialize it and send it
                            binding.SendServer(&msg, sizeof(int));
                            binding.ClientClose();
                            return true; 
                        });
                    }

                    template <typename Class, typename R>
                    void HandleCall(Class &c,
                                    ara::core::Future<R> (Class::*method)(),
                                    Message msg,
                                    CServer binding)
                    {
                        ara::core::Future<R> f = (c.*method)();
                        f.then([this, msg](ara::core::Future<R> &&f) -> bool
                        {
                            R r = f.get();

                            binding.SendServer(&r, sizeof(int));
                            binding.ClientClose();
                            return true;
                        });
                    }

                    template <typename Class>
                    void HandleCall(Class &c,
                                    ara::core::Future<void> (Class::*method)(),
                                    Message msg,
                                    CServer binding)
                    {
                        ara::core::Future<void> f = (c.*method)();
                        f.then([this, msg](ara::core::Future<void> &&f) -> bool
                        {
                            f.get();

                            binding.SendServer(&msg, sizeof(int));
                            binding.ClientClose();
                            return true;
                        });
                    }

                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding)
                    {
                        sHandleCall(c,method,msg,binding,std::index_sequence_for(Args...));
                    }

                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    Message msg,
                                    CServer binding,
                                    std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg->payload);
                        (c.*method)(unmarshaller.template unmarshal<index>()...);
                    }


                    template <typename Class>
                    void HandleCall(Class &c,
                                    void (Class::*method)(),
                                    Message msg,
                                    CServer binding)
                    {
                        (c.*method)();
                    }

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

                private:
                    template <typename T>
                    void SendEvent(std::string eventName, const T &data, bool is_field)
                    {
                    }

                    bool HasRequest();

                    void ProcessRequest();

                    int m_fd;
                    ara::com::InstanceIdentifier m_instance;
                    ara::com::MethodCallProcessingMode m_mode;
                    bool m_terminated;
                    std::queue<std::shared_ptr<Message>> m_requestMessages;
                    std::mutex m_mutex;
                    std::condition_variable m_condition;
                    std::vector<std::shared_ptr<std::promise<void>>> m_thread_joins;

                    // friend SkeletonBase;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_
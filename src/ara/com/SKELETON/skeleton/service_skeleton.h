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

#ifndef ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_
#define ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_


// #include "internall/skeleton/event.h"
// #include "internall/skeleton/field.h"
#include "types.h"
#include "../service_base.h"
#include "../definitions.h"
// #include <ara/com/types.h>
// #include <ara/com/internal/service_base.h>
// #include <ara/com/internal/definitions.h>
// #include <ara/com/internal/binding/skeleton_network_binding_base.h>


#include <map>
#include <queue>
#include <future>


namespace ara
{
    namespace com
    {
        namespace SKELETON
        {
            namespace skeleton
            {

                struct C_Info
                {
                    int process_id;
                    char method_name[30];
                    int param1;
                    int param2;
                };
                class ServiceSkeleton : public ara::com::SKELETON::ServiceBase
                {
                public:

                    ServiceSkeleton(
                        std::string name,
                        ara::com::InstanceIdentifier instance,
                        ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent)
                        :ServiceBase(name)
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
                    virtual void DispatchMethodCall(const std::shared_ptr<Message> msg, std::shared_ptr<int> binding) = 0;

                template <typename Class, typename... Args>
                 void HandleCall(Class& c,
                    void (Class::*method)(),
                    const struct C_Info& message,
                    int binding
                )
                {
                   // binding->HandleCall(c, method, msg);
                    int result = method(message.param1);
                    cserver.SendServer(&result, sizeof(int));
                    cserver.ClientClose();
                }


                template <typename Class>
                 void HandleCall(Class& c,
                    void (Class::*method)(),
                    const struct C_Info& message,
                    CServer& cserver
                )
                {
                   // binding->HandleCall(c, method, msg);
                    int result = method();
                    cserver.SendServer(&result, sizeof(int));
                    cserver.ClientClose();
                }

                  template <typename Class, typename R>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(),
                                    const struct C_Info& message,
                                    CServer& cserver)
                    {
                        //binding->HandleCall(c, method, msg);
                    }

                    template <typename Class>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(),
                                    const struct C_Info& message,
                                    CServer& cserver)
                    {
                        //binding->HandleCall(c, method, msg);
                    }

                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    const struct C_Info& message,
                                    CServer& cserver)
                    {
                        //binding->HandleCall(c, method, msg, std::index_sequence_for<Args...>());
                    }

                    template <typename Class>
                    void HandleCall(Class &c,
                                    void (Class::*method)(),
                                    const struct C_Info& message,
                                   CServer& cserver)
                    {
                       // binding->HandleCall(c, method, msg);
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
                    //ara::com::InstanceIdentifier m_instance;
                    ara::com::MethodCallProcessingMode m_mode;
                    bool m_terminated;
                    // std::map<ara::com::internal::NetWorkBindingType, std::shared_ptr<binding_base_type>> m_bindings;
                    std::queue<std::shared_ptr<Message>> m_requestMessages;
                    std::mutex m_mutex;
                    std::condition_variable m_condition;
                    std::vector<std::shared_ptr<std::promise<void>>> m_thread_joins;

                    // friend SkeletonBase;
                };

            } // skeleton
        }     // internal
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_SKELETON_SERVICE_SKELETON_H_
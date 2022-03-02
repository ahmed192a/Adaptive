#ifndef ARA_COM_INTERNAL_SERVICE_PROXY_H_
#define ARA_COM_INTERNAL_SERVICE_PROXY_H_

// #include "proxy.hpp"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "../../ServiceDiscovery/Service_Discovery/client/CClient.h"
#include "../../../../data.h"

#include "event.h"
#include <signal.h>
// #include <ara/com/internal/binding/proxy_network_binding_base.h>

#include <queue>

// struct SD_data{
//     int service_id;
//     int process_id;
//     int port_number;
//     bool message_type;
// };

namespace ara
{
namespace com
{
namespace proxy_skeleton
{
namespace proxy
{

// using binding_base_type = ara::com::internal::binding::ProxyNetworkBindingBase;

class ProxyBase;

// class ServiceProxy : public ara::com::internal::ServiceBase
class ServiceProxy : public Event
{
public:
    ServiceProxy();
    virtual ~ServiceProxy();
    int FindService(int portNumber, int service_id); // we send to the service discovery a request for a specific service
    int SendRequest(); // send to the server a requested method
private:
    struct SD_data receive; // a struct to receive in it the process id & port number of the server from service discovery
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

    //deh zy method el fe proxy bta3naaa
    // template <typename... Args>
    
    
    // template <typename... Args>
    // ara::core::Future<void> SendRequest(std::string name, Args&&... args)
    // {
    //     ara::core::Future<void> f;

    //     f = m_binding->SendRequest(name, std::forward<Args>(args)...);
        
    //     return f;
    // }
    
    // template <typename R, typename... Args>
    // ara::core::Future<R> SendRequest(std::string name, Args&&... args)
    // {
    //     ara::core::Future<R> f;
        
    //     f = m_binding->SendRequest<R>(name, std::forward<Args>(args)...);
        
    //     return f;
    // }
    
    // template <typename R>
    // ara::core::Future<R> SendRequest(std::string name)
    // {
    //     ara::core::Future<R> f;
        
    //     f = m_binding->SendRequest<R>(name);
        
    //     return f;
    // }
    
    // template <typename... Args>
    // void SendFireAndForgetRequest(std::string name, Args&&... args)
    // {
    //     m_binding->SendFireAndForgetRequest(name, std::forward<Args>(args)...);
    // }
    
    // void SendFireAndForgetRequest(std::string name)
    // {
    //     m_binding->SendFireAndForgetRequest(name);
    // }
    
    
    // HandleType m_handle;
    // std::shared_ptr<binding_base_type> m_binding;
    // std::map<std::string, std::function<void(std::shared_ptr<std::vector<uint8_t>>)>> m_eventHandlers;
    // std::mutex m_mutexHandler;
    // std::queue<std::shared_ptr<Message>> m_messages;
    // std::mutex m_mutexMessage;
    // std::condition_variable m_conditionMessages;
    // bool m_terminated;
    // std::vector<std::shared_ptr<ara::core::Promise<void>>> m_thread_joins;
    
    friend ProxyBase;
};

} // proxy
} // internal
} // com
} // ara


#endif  // ARA_COM_INTERNAL_SERVICE_PROXY_H_


// service_proxy inherit event wa field
// proxy zy ucm,sm kda by inherit service_proxy wa kda by2dr yst5dm kol hagat event wa field

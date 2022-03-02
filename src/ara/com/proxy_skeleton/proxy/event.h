#ifndef ARA_COM_INTERNAL_PROXY_EVENT_H_
#define ARA_COM_INTERNAL_PROXY_EVENT_H_

#include "../../ServiceDiscovery/Service_Discovery/client/CClient.h"
#include <string.h>
#include <string>
#include <unistd.h>
#include "../../../../data.h"


namespace ara
{
namespace com
{
namespace proxy_skeleton
{
namespace proxy
{

// template <typename T>
// class Event : public EventBase
class Event
{
public:
    Event();
    ~Event();
    void Subscribe(char event_name[]); // We use setter to get the port_number & pid of the server from outside"service_proxy"
    void setter(int port_number, int pid);
private:
    int pid; // Saving the process id of the server we want to subscribe to its event
    int port_number; // Saving the port_number of the server we want to subscribe to its event
    // Event(ServiceProxy* service, std::string name)
    //     :EventBase(service, name)
    // {
    // }

    // Event(int data, int pid);
    // void update(int value);
    // void notify(int value);
    
// private:
    // bool Update(ara::com::FilterFunction<T> filter = {})
    // {
    //     std::lock_guard<std::mutex> guard(m_mutex);
        
    //     if (m_cacheSize == 0)
    //     {
    //         return false;
    //     }
        
    //     if (m_policy == ara::com::EventCacheUpdatePolicy::kNewestN)
    //     {
    //         m_samples.clear();
    //     }
                
    //     UpdateEventSample(m_name, m_samples, m_data, filter, m_cacheSize);
        
    //     m_data.clear();

    //     return !m_samples.empty();
    // }
    
    // const ara::com::SampleContainer<ara::com::SamplePtr<const T>>& GetCachedSamples() const
    // {
    //     return m_samples;
    // }
    
    // void Cleanup()
    // {
    //     if (m_policy == ara::com::EventCacheUpdatePolicy::kNewestN)
    //     {
    //         std::lock_guard<std::mutex> guard(m_mutex);
    //         m_samples.clear();
    //     }
        
    //     EventBase::Cleanup();
    // }
   

    // int data; // the value that the client subscribe to get notified about its updates
    
    // ara::com::SampleContainer<ara::com::SamplePtr<const T>> m_samples;


}; // Event
} // proxy
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_PROXY_EVENT_H_

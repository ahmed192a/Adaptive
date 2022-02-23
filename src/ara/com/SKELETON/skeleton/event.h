/**
 * @file event.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARA_COM_INTERNAL_SKELETON_EVENT_H_
#define ARA_COM_INTERNAL_SKELETON_EVENT_H_

#include "types.h"
// #include "event_base.h"

namespace ara
{
namespace com
{
namespace SKELETON
{
namespace skeleton
{

template <typename T>
class Event //: public EventBase
{
    private:
    ServiceSkeleton *m_service;
    std::string m_name;

public:
    Event(ServiceSkeleton *service, std::string name)
        // :EventBase(service, name)
    {
        m_service = service;
        m_name = name;
    }
    
    virtual ~Event(){}
    
    void Send(const T& data)
    {
        m_service->SendEvent(m_name, data, false);
    }
    
    void Send(ara::com::SampleAllocateePtr<T> data)
    {
        Send(*data);
    }
    
    ara::com::SampleAllocateePtr<T> Allocate()
    {
        return std::make_unique<T>();
    }
};

} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_EVENT_H_

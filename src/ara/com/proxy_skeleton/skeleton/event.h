/**
 * @file event.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_COM_INTERNAL_SKELETON_EVENT_H_
#define ARA_COM_INTERNAL_SKELETON_EVENT_H_

// #include <ara/com/types.h>
// // #include "event_base.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <signal.h>
#include "../../ipc/server/socket_Server.h"
#include "../../../../data.h"
#include <set>
#include <iterator>

// Service_Discovery/server/CServer.h


namespace ara
{
namespace com
{
namespace proxy_skeleton
{
namespace skeleton
{

// template <typename T>
class Event
{
public:
    Event();
    virtual ~Event();
    void setter(int process_id);
    void print_subscribers();
    // friend void signal_handler(int signum, siginfo_t *siginfo, void *ucontext);  
    std::set<int> subscribers_data; 
    void update(int value);
    void notify(int value);
private: 
    int event_data;
    
 

//public:
//     Event(ServiceSkeleton *service, std::string name)
//         :EventBase(service, name)
//     {
//     }    
//     void signal_handler(int signum, siginfo_t *siginfo, void *ucontext);
   
//     void Send(const T& data)
//     {
//         SendEvent(m_name, data, false);
//     }
    
//     void Send(ara::com::SampleAllocateePtr<T> data)
//     {
//         Send(*data);
//     }
    
//     ara::com::SampleAllocateePtr<T> Allocate()
//     {
//         return std::make_unique<T>();
//     }

}; // Event
} // skeleton
} // internal
} // com
} // ara

#endif  // ARA_COM_INTERNAL_SKELETON_EVENT_H_

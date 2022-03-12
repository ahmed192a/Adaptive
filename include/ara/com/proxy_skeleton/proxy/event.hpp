/**
 * @file event.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_
#define ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {

                template <typename T>
                class Event
                {
                public:
                    Event(
                        ServiceProxy *service,
                        std::string name,
                        int event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                    }
                    ~Event() {}
                    void Subscribe()
                    {
                        m_service->EventSubscribe<T>(m_event_id);
                    }

                    void UnSubscribe()
                    {
                        m_service->EventUnsubscribe<T>(m_event_id);
                    }

                    // template <typename T>
                    void handlecall(ara::com::proxy_skeleton::event_notify<T> val)
                    {

                        // sockaddr_in echoClntAddr; /* Address of datagram source */
                        // unsigned int clntLen;     /* Address length */

                        // clntLen = sizeof(echoClntAddr);
                        // m_service->Cient_Server_connection_DG->UDPRecFrom(&event_data, sizeof(event_data), (sockaddr *)&echoClntAddr, &clntLen);
                         event_data = val.newdata;
                    }
                    T get_value()
                    {
                        return event_data;
                    }

                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    T event_data;
                    int m_event_id;

                }; // Event
            }      // proxy
        }          // proxy_skeleton
    }              // com
} // ara

#endif // ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

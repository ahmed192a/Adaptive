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
#include "ara/com/deserializer.hpp"
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
                protected:
                    ServiceProxy *m_service;
                    std::string m_name;
                    std::shared_ptr<T> event_data;
                    uint32_t m_event_id;

                public:
                    Event(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t event_id)
                        : m_service{service},
                          m_name{name},
                          m_event_id{event_id}
                    {
                        event_data = std::make_shared<T>();
                    }
                    ~Event() {}

                    void Subscribe()
                    {
                        m_service->EventSubscribe(m_event_id);
                        std::cout<<"subscribe -- \n";
                    }

                    void UnSubscribe()
                    {
                        m_service->EventUnsubscribe(m_event_id);
                    }

                    void handlecall(ara::com::proxy_skeleton::event_info& val, std::vector<uint8_t > &msg)
                    {
                        ara::com::Deserializer dser;
                        *event_data = dser.deserialize<T>(msg, 0);
                        // event_data = val.newdata;
                    }
                    T  get_value()
                    {
                        return *event_data;
                    }

                }; // Event
            }      // proxy
        }          // proxy_skeleton
    }              // com
} // ara

#endif // ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

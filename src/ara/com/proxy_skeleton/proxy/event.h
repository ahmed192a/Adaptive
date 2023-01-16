/**
 * @file event.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Base class for all events.
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_
#define ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

#include "ara/com/proxy_skeleton/proxy/service_proxy.h"
#include "ara/com/deserializer.h"
namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {
                /**
                 * @brief Event Base class for all events.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class Event
                {
                protected:
                    ServiceProxy *m_service;        /*!< pointer to service proxy */
                    std::string m_name;             /*!< name of the event */
                    std::shared_ptr<T> event_data;  /*!< event data */
                    uint32_t m_event_id;            /*!< id of the event */

                public:
                    /**
                     * @brief Construct a new Event object
                     * 
                     * @param service   pointer to service proxy 
                     * @param name      name of the event
                     * @param event_id  id of the event
                     */
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


                    /**
                     * @brief get the id of the event (unique identifier)
                     * 
                     * @return int 
                     */
                    int Get_event_id()
                    {
                        return m_event_id;
                    }
                    /**
                     * @brief Destroy the Event object
                     * 
                     */
                    ~Event() {}
                    /**
                     * @brief Subscribe to event
                     * 
                     */
                    void Subscribe()
                    {
                        m_service->EventSubscribe(m_event_id);
                        std::cout << "subscribe -- \n";
                    }
                    /**
                     * @brief Unsubscribe from event
                     * 
                     */
                    void UnSubscribe()
                    {
                        m_service->EventUnsubscribe(m_event_id);
                    }
                    /**
                     * @brief Get the Event Data object
                     * 
                     * @param msg   message to be deserialized
                     */
                    void handlecall(std::vector<uint8_t> &msg)
                    {
                        ara::com::Deserializer dser;
                        *event_data = dser.deserialize<T>(msg, 0);
                    }
                    /**
                     * @brief Get the value object
                     * 
                     * @return T 
                     */
                    T get_value()
                    {
                        return *event_data;
                    }

                }; // Event
            }// proxy
        }// proxy_skeleton
    }// com
} // ara

#endif // ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

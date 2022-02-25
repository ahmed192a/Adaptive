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

#ifndef ARA_COM_proxy_skeleton_SKELETON_EVENT_H_
#define ARA_COM_proxy_skeleton_SKELETON_EVENT_H_


namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {

                template <typename T>
                class Event
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    Event(ServiceSkeleton *service, std::string name)
                    {
                        m_service = service;
                        m_name = name;
                    }

                    virtual ~Event() {}

                    void Send(const T &data)
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
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_EVENT_H_

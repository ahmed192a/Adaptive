/**
 * @file field.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_proxy_skeleton_SKELETON_FIELD_H_
#define ARA_COM_proxy_skeleton_SKELETON_FIELD_H_
// #include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
// #include <string>
// #include <future>
#include <bits/stdc++.h>

#include "ara/com/proxy_skeleton/skeleton/event.hpp"
namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {
                template <typename T>
                using FieldSetHandler = std::function<T(const T &data)>;

                template <typename T>
                using FieldGetHandler = std::function<T()>;

                /**
                 * @brief has getter ,setter , notifier
                 *
                 * @tparam T
                 */
                template <typename T>
                class Field : public Event<T>
                {
                public:
                    /**
                     * @brief Construct a new Field object
                     * @todo edit all other fields
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    Field(
                        ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                 name,
                                                 field_id)
                    {
                    }
                    // void handlecall(ara::com::proxy_skeleton::event_info &msg,std::vector<uint8_t>&data, ara::com::proxy_skeleton::Client_udp_Info client)
                    // {
                    //     ara::com::Deserializer dser;
                    //     ara::com::Serializer ser;
                    //     switch (msg.operation)
                    //     {
                    //     case 0:
                    //         // new value
                    //         // event_data = msg_data;
                    //         break;
                    //     case 1:
                    //         Event<T>::set_subscriber(client);
                    //         Event<T>::print_subscribers();
                    //         break;
                    //     case 2:
                    //         Event<T>::Del_subscriber(client);
                    //         // Event<T>::print_subscribers();
                    //         break;
                    //     case 3:
                    //         Event<T>::event_data = dser.deserialize<T>(data,0);
                    //         std::cout<<"data is seted***************\n\n\n";
                    //         break;

                    //     case 4:
                    //         ser.serialize(Event<T>::event_data);
                    //         data = ser.Payload();
                    //         msg.data_size = data.size();
                    //         break;
                    //     default:
                    //         break;
                    //     }
                    // }

                    virtual ~Field() {}
                   
                };

                template <typename T>
                class FieldNoSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoSetter(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr)
                    {
                    }

                    virtual ~FieldNoSetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }

                    void RegisterGetHandler(FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    FieldGetHandler<T> GetHandler;
                };

                template <typename T>
                class FieldNoGetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoGetter(ServiceSkeleton *service, std::string name)
                        : SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoGetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }

                    void RegisterSetHandler(FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    FieldSetHandler<T> SetHandler;
                };

                template <typename T>
                class FieldNoGetterAndSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoGetterAndSetter(ServiceSkeleton *service, std::string name)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoGetterAndSetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }
                };

                template <typename T>
                class FieldNoNotifier
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifier(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr), SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifier() {}

                    void RegisterGetHandler(FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    void RegisterSetHandler(FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    FieldGetHandler<T> GetHandler;
                    FieldSetHandler<T> SetHandler;
                };

                template <typename T>
                class FieldNoNotifierAndSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndSetter(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifierAndSetter() {}

                    void RegisterGetHandler(FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    FieldGetHandler<T> GetHandler;
                };

                template <typename T>
                class FieldNoNotifierAndGetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndGetter(ServiceSkeleton *service, std::string name)
                        : SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifierAndGetter() {}

                    void RegisterSetHandler(FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    FieldSetHandler<T> SetHandler;
                };

                /* Interface for creating field opject ddepending on the input (getter/notifier/setter)*/
                template <typename T, bool hasGetter, bool hasNotifier, bool hasSetter>
                struct FieldType
                {
                    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
                };

                /*if all true create object of Field class*/
                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };
                /*if No Setter create object of FieldNoSetter class*/
                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoSetter<T>;
                };

                /*if No Getter create object of FieldNoGetter class*/
                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };

                /*if No Getter & Setter create object of FieldNoGetterAndSetter class*/
                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };
                /*if No Notifier create object of FieldNoNotifier class*/
                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoNotifier<T>;
                };
                /*if No Notifier & setter create object of FieldNoNotifierAndSetter class*/
                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };
                /*if No Notifier & Getter create object of FieldNoNotifierAndGetter class*/
                template <typename T>
                struct FieldType<T, false, false, true>
                {
                    using type = FieldNoNotifierAndGetter<T>;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_FIELD_H_

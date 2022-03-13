/**
 * @file field.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_PROXY_FIELD_H_
#define ARA_COM_PROXY_SKELETON_PROXY_FIELD_H_

#include "ara/com/proxy_skeleton/proxy/event.hpp"
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
                class Field : public Event<T>
                {
                public:
                    Field(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }

                    ~Field() {}

                    /**
                     * @brief
                     *
                     * @todo implemention code
                     *         - send request to server to Get this field value
                     *         - msg sent is (m_name + "_Get", value)
                     *         - this request will return the current value
                     * @return T
                     */
                    T Get()
                    {
                        T value;
                        ara::com::Deserializer dser;
                        std::vector<uint8_t> data;
                        data.resize(sizeof(value));
                        ara::com::proxy_skeleton::event_info e_get;
                        e_get.event_id = m_field_id;
                        e_get.service_id = m_service->m_proxy_handle.m_server_com.service_id;
                        e_get.operation = 4;
                        //e_get.data_size= data.size();
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                    /**
                     * @brief
                     *
                     * @todo implemention code
                     *         - send request to server to set this field value
                     *         - msg sent is (m_name + "_Set", value)
                     *         - this request will return the updated
                     * @param value
                     * @return T
                     */
                    T Set(T &value)
                    {
                        ara::com::Serializer ser;
                        ser.serialize(value);
                        std::vector<uint8_t> data = ser.Payload();
                        ara::com::proxy_skeleton::event_info e_set;
                        e_set.event_id = m_field_id;
                        e_set.service_id = m_service->m_proxy_handle.m_server_com.service_id;
                        e_set.operation = 3;
                        e_set.data_size = data.size();
                        m_service->Field_set(e_set, data);
                        return value;
                    }

                private:
                    //CClient m_Cient_Server_connection;
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;
                };

                template <typename T>
                class FieldNoSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoSetter(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoSetter() {}

                    std::future<T> Get()
                    {
                        // return m_service->SendRequest<T>(m_name + "_Set", value);

                        // return EventBase::SendRequest<T>(EventBase::m_name + "_Get");
                    }
                };

                template <typename T>
                class FieldNoGetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoGetter(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoGetter() {}

                    std::future<T> Set(const T &value)
                    {
                        // return m_service->SendRequest<T>(m_name + "_Get");
                        //  return EventBase::SendRequest<T>(EventBase::m_name + "_Set", value);
                    }
                };

                template <typename T>
                class FieldNoGetterAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoGetterAndSetter(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoGetterAndSetter() {}
                };

                template <typename T>
                class FieldNoNotifier : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifier(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoNotifier() {}

                    std::future<T> Get()
                    {
                        // return m_service->SendRequest<T>(m_name + "_Get");
                    }

                    std::future<T> Set(const T &value)
                    {
                        // return m_service->SendRequest<T>(m_name + "_Set", value);
                    }
                };

                template <typename T>
                class FieldNoNotifierAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndSetter(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoNotifierAndSetter() {}

                    std::future<T> Get()
                    {
                        // return m_service->SendRequest<T>(m_name + "_Get");
                    }
                };

                template <typename T>
                class FieldNoNotifierAndGetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndGetter(ServiceProxy *service, std::string name)
                        : Event<T>(service, name)
                    {
                    }

                    virtual ~FieldNoNotifierAndGetter() {}

                    std::future<T> Set(const T &value)
                    {
                        // return SendRequest<T>(std::string m_name + "_Set", value);
                    }
                };

                template <typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
                struct FieldType
                {
                    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
                };

                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };

                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoSetter<T>;
                };

                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };

                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };

                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoNotifier<T>;
                };

                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };

                template <typename T>
                struct FieldType<T, false, false, true>
                {
                    using type = FieldNoNotifierAndGetter<T>;
                };

            } // proxy
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_INTERNAL_PROXY_FIELD_H_

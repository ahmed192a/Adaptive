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
                /**
                 * @brief Base class for all fields.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class Field : public Event<T>
                {
                public:
                    /**
                     * @brief Construct a new Field object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
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
                    /**
                     * @brief Destroy the Field object
                     * 
                     */
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
                        // e_get.data_size= data.size();
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
                    // CClient m_Cient_Server_connection;
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;
                };
                /**
                 * @brief Class for field with no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Setter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoSetter(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Setter object
                     * 
                     */
                    ~FieldNoSetter() {}
                    /**
                     * @brief Get the value of the field
                     * 
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
                        // e_get.data_size= data.size();
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                };
                /**
                 * @brief Class for field with no getter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoGetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Getter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoGetter(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Getter object
                     * 
                     */
                    ~FieldNoGetter() {}
                    /**
                     * @brief Set the value of the field
                     * 
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
                };
                /**
                 * @brief Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoGetterAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Getter And Setter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoGetterAndSetter(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Getter And Setter object
                     * 
                     */
                    ~FieldNoGetterAndSetter() {}
                };
                /**
                 * @brief Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifier : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Notifier object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoNotifier(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Notifier object
                     * 
                     */
                    ~FieldNoNotifier() {}
                    /**
                     * @brief Get the value of the field
                     * 
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
                        // e_get.data_size= data.size();
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                    /**
                     * @brief Set the value of the field
                     * 
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
                };
                /**
                 * @brief Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifierAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Notifier And Setter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoNotifierAndSetter(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Notifier And Setter object
                     * 
                     */
                    ~FieldNoNotifierAndSetter() {}
                    /**
                     * @brief Get the value of the field
                     * 
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
                        // e_get.data_size= data.size();
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                };
                /**
                 * @brief Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifierAndGetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    uint32_t m_field_id;

                public:
                    /**
                     * @brief Construct a new Field No Notifier And Getter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoNotifierAndGetter(
                        ServiceProxy *service,
                        std::string name,
                        uint32_t field_id)
                        : Event<T>(service, name, field_id),
                          m_service{service},
                          m_name{name},
                          m_field_id{field_id}
                    {
                    }
                    /**
                     * @brief Destroy the Field No Notifier And Getter object
                     * 
                     */
                    ~FieldNoNotifierAndGetter() {}
                    /**
                     * @brief Set the value of the field
                     * 
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
                };
                /**
                 * @brief Class for field.
                 * 
                 * @tparam T 
                 * @tparam hasGetter 
                 * @tparam hasSetter 
                 * @tparam hasNotifier 
                 */
                template <typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
                struct FieldType
                {
                    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
                };
                /**
                 * @brief Class for field with getter, setter and notifier.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };
                /**
                 * @brief Class for field with no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoSetter<T>;
                };
                /**
                 * @brief Class for field with no getter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };
                /**
                 * @brief Class for field with no getter and setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };
                /**
                 * @brief Class for field with no notifier.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoNotifier<T>;
                };
                /**
                 * @brief Class for field with no notifier and setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };
                /**
                 * @brief Class for field with no getter and notifier.
                 * 
                 * @tparam T 
                 */
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

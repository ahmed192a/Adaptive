/**
 * @file field.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Base class for all fields.
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_PROXY_FIELD_H_
#define ARA_COM_PROXY_SKELETON_PROXY_FIELD_H_

#include "ara/com/proxy_skeleton/proxy/event.h"
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
                 * @brief Field Base class for all fields.
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
                     * @param service   pointer to service proxy
                     * @param name      name of the field
                     * @param field_id  id of the field
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
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                    /**
                     * @brief Set the value of the field
                     *
                     * @param value     value to be set
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
                        m_service->Field_set(e_set, data);
                        return value;
                    }

                private:
                    ServiceProxy *m_service;       /*!< pointer to service proxy */
                    std::string m_name;             /*!< name of the field */
                    uint32_t m_field_id;            /*!< id of the field */
                };
                /**
                 * @brief FieldNoSetter Class for field with no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;    /*!< pointer to service proxy */
                    std::string   m_name;       /*!< name of the field */
                    uint32_t      m_field_id;   /*!< id of the field */

                public:
                    /**
                     * @brief Construct a new Field No Setter object
                     * 
                     * @param service       pointer to service proxy
                     * @param name          name of the field
                     * @param field_id      id of the field
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
                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                };
                /**
                 * @brief FieldNoGetter Class for field with no getter.
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
                     * @param value     value to be set
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
                        m_service->Field_set(e_set, data);
                        return value;
                    }
                };
                /**
                 * @brief FieldNoGetterAndSetter Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoGetterAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;        /*!< pointer to service proxy */
                    std::string m_name;             /*!< name of the field */
                    uint32_t m_field_id;            /*!< id of the field */

                public:
                    /**
                     * @brief Construct a new Field No Getter And Setter object
                     * 
                     * @param service       pointer to service proxy
                     * @param name          name of the field
                     * @param field_id      id of the field
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
                 * @brief FieldNoNotifier Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifier : public Event<T>
                {
                private:
                    ServiceProxy *m_service;    /*!< pointer to service proxy */
                    std::string m_name;         /*!< name of the field */
                    uint32_t m_field_id;        /*!< id of the field */

                public:
                    /**
                     * @brief Construct a new Field No Notifier object
                     * 
                     * @param service       pointer to service proxy
                     * @param name          name of the field
                     * @param field_id      id of the field
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
                        m_service->Field_set(e_set, data);
                        return value;
                    }
                };
                /**
                 * @brief FieldNoNotifierAndSetter Class for field with no getter and no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifierAndSetter : public Event<T>
                {
                private:
                    ServiceProxy *m_service;        /*!< pointer to service proxy */
                    std::string m_name;             /*!< name of the field */
                    uint32_t m_field_id;            /*!< id of the field */

                public:
                    /**
                     * @brief Construct a new Field No Notifier And Setter object
                     * 
                     * @param service           pointer to service proxy
                     * @param name              name of the field
                     * @param field_id          id of the field
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

                        m_service->Field_get(e_get, data);
                        value = dser.deserialize<T>(data, 0);
                        return value;
                    }
                };
                /**
                 * @brief FieldNoNotifierAndGetter Class for field with no getter and no setter.
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
                        m_service->Field_set(e_set, data);
                        return value;
                    }
                };
                /**
                 * @brief FieldType Class for field.
                 * 
                 * @tparam T            type of the field
                 * @tparam hasGetter    true if field has getter
                 * @tparam hasSetter    true if field has setter
                 * @tparam hasNotifier  true if field has notifier
                 */
                template <typename T, bool hasGetter, bool hasSetter, bool hasNotifier>
                struct FieldType
                {
                    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
                };
                /**
                 * @brief FieldType Class for field with getter, setter and notifier.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };
                /**
                 * @brief FieldType Class for field with no setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoSetter<T>;
                };
                /**
                 * @brief FieldType Class for field with no getter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };
                /**
                 * @brief FieldType Class for field with no getter and setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };
                /**
                 * @brief FieldType Class for field with no notifier.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoNotifier<T>;
                };
                /**
                 * @brief FieldType Class for field with no notifier and setter.
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };
                /**
                 * @brief FieldType Class for field with no getter and notifier.
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

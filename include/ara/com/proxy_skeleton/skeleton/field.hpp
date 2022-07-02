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
                // template <typename T>
                // using FieldSetHandler = std::function<T(const T &data)>;

                // template <typename T>
                // using FieldGetHandler = std::function<T()>;

                /**
                 * @brief class field -->  has getter ,setter , notifier
                 *
                 * @tparam T
                 * 
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
                    /**
                     * @brief Handle set method 
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Deserializer dser;
                        this->event_data = dser.deserialize<T>(_data, 0);

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                        this->notify();
                    }
                    /**
                     * @brief Handle Get method
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Serializer ser;
                        ser.serialize(this->event_data);
                        _data = ser.Payload();

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                    }
                    /**
                     * @brief Destroy the Field object
                     * 
                     */
                    virtual ~Field() {}
                };
                 
                 /**
                  * @brief class FieldNoSetter has get method
                  * 
                  * @tparam T 
                  */
                template <typename T>
                class FieldNoSetter : public Event<T>
                {
                public:
                /**
                 * @brief Construct a new Field No Setter object
                 * 
                 * @param service 
                 * @param name 
                 * @param field_id 
                 */
                    FieldNoSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                    }
                    /**
                     * @brief Destroy the Field No Setter object
                     * 
                     */
                    virtual ~FieldNoSetter() {}
                    /**
                     * @brief Handle Get method
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Serializer ser;
                        ser.serialize(this->event_data);
                        _data = ser.Payload();

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                    }
                };
                
                /**
                 * @brief class FieldNoGetter to set method
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoGetter : public Event<T>
                {
                public:
                /**
                 * @brief Construct a new Field No Getter object
                 * 
                 * @param service 
                 * @param name 
                 * @param field_id 
                 */
                    FieldNoGetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    /**
                     * @brief Destroy the Field No Getter object
                     * 
                     */
                    virtual ~FieldNoGetter() {}
                    /**
                     * @brief Handle set method 
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Deserializer dser;
                        this->event_data = dser.deserialize<T>(_data, 0);

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                        this->notify();
                    }
                };
                
                /**
                 * @brief class Field No Getter And Setter --> update event
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoGetterAndSetter : public Event<T>
                {
                public:
                /**
                 * @brief Construct a new Field No Getter And Setter object
                 * 
                 * @param service 
                 * @param name 
                 * @param field_id 
                 */
                    FieldNoGetterAndSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    /**
                     * @brief Destroy the Field No Getter And Setter object
                     * 
                     */
                    virtual ~FieldNoGetterAndSetter() {}
                    /**
                     * @brief update event
                     * 
                     * @param data 
                     */
                    void Update(const T &data)
                    {
                        this->m_service->SendEvent(this->m_name, data, true);
                    }
                };
                
                /**
                 * @brief class Field No Notifier --> update event
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifier : public Event<T>
                {
                public:
                /**
                 * @brief Construct a new Field No Notifier object
                 * 
                 * @param service 
                 * @param name 
                 * @param field_id 
                 */
                    FieldNoNotifier( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    /**
                     * @brief Destroy the Field No Notifier object
                     * 
                     */
                    virtual ~FieldNoNotifier() {}
                    /**
                     * @brief update event
                     * 
                     * @param value 
                     */
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }
                };
                 
                /**
                 * @brief class Field No Notifier And Setter --> to handle get then update
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifierAndSetter : public Event<T>
                {
                public:
                    /**
                     * @brief Construct a new Field No Notifier And Setter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoNotifierAndSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    /**
                     * @brief Destroy the Field No Notifier And Setter object
                     * 
                     */
                    virtual ~FieldNoNotifierAndSetter() {}
                    /**
                     * @brief handle get field value
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Serializer ser;
                        ser.serialize(this->event_data);
                        _data = ser.Payload();

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                    }
                    /**
                     * @brief update event
                     * 
                     * @param value 
                     */
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }
                };
                /**
                 * @brief class Field No Notifier And Getter
                 * 
                 * @tparam T 
                 */
                template <typename T>
                class FieldNoNotifierAndGetter : public Event<T>
                {
                public:
                    /**
                     * @brief Construct a new Field No Notifier And Getter object
                     * 
                     * @param service 
                     * @param name 
                     * @param field_id 
                     */
                    FieldNoNotifierAndGetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    /**
                     * @brief update event
                     * 
                     * @param value 
                     */
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }
                    /**
                     * @brief Destroy the Field No Notifier And Getter object
                     * 
                     */
                    virtual ~FieldNoNotifierAndGetter() {}
                    /**
                     * @brief HandleSet method
                     * 
                     * @param sd_msg 
                     * @param binding 
                     */
                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id, (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        ara::com::Deserializer dser;
                        this->event_data = dser.deserialize<T>(_data, 0);

                        // Setpayload in message
                        R_msg.SetPayload(_data);
                        _data = R_msg.Serializer();
                        uint32_t msg_size = _data.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_data.data(), msg_size);
                        binding.CloseSocket();
                        this->notify();
                    }
                };
           
                /**
                 * @brief Interface for creating field opject ddepending on the input (getter/notifier/setter)
                 * 
                 * @tparam T 
                 * @tparam hasGetter 
                 * @tparam hasNotifier 
                 * @tparam hasSetter 
                 */
                template <typename T, bool hasGetter,bool hasSetter, bool hasNotifier>
                struct FieldType
                {
                    using type = typename FieldType<T,hasGetter, hasSetter,  hasNotifier>::type;
                };
                /**
                 * @brief if all true create object of Field class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };

                /**
                 * @brief if No Setter create object of FieldNoSetter class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoSetter<T>;
                };
                /**
                 * @brief if No Getter create object of FieldNoGetter class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };
                /**
                 * @brief if No Getter & Setter create object of FieldNoGetterAndSetter class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, false, true>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };
                /**
                 * @brief if No Notifier create object of FieldNoNotifier class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoNotifier<T>;
                };
                /**
                 * @brief if No Notifier & setter create object of FieldNoNotifierAndSetter class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };
                /**
                 * @brief if No Notifier & Getter create object of FieldNoNotifierAndGetter class
                 * 
                 * @tparam T 
                 */
                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoNotifierAndGetter<T>;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_FIELD_H_

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
                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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
                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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
                    virtual ~Field() {}
                };

                template <typename T>
                class FieldNoSetter : public Event<T>
                {
                public:
                    FieldNoSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                    }

                    virtual ~FieldNoSetter() {}

                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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

                template <typename T>
                class FieldNoGetter : public Event<T>
                {
                public:
                    FieldNoGetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }

                    virtual ~FieldNoGetter() {}

                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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

                template <typename T>
                class FieldNoGetterAndSetter : public Event<T>
                {
                public:
                    FieldNoGetterAndSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }

                    virtual ~FieldNoGetterAndSetter() {}

                    void Update(const T &data)
                    {
                        this->m_service->SendEvent(this->m_name, data, true);
                    }
                };

                template <typename T>
                class FieldNoNotifier : public Event<T>
                {
                public:
                    FieldNoNotifier( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }

                    virtual ~FieldNoNotifier() {}
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }
                };

                template <typename T>
                class FieldNoNotifierAndSetter : public Event<T>
                {
                public:
                    FieldNoNotifierAndSetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }

                    virtual ~FieldNoNotifierAndSetter() {}
                 
                    void HandleGet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data;
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }
                };

                template <typename T>
                class FieldNoNotifierAndGetter : public Event<T>
                {
                public:
                    FieldNoNotifierAndGetter( ServiceSkeleton *service,
                        std::string name,
                        uint32_t field_id) : Event<T>(service,
                                                      name,
                                                      field_id)
                    {
                        this->m_name = name;
                        this->m_service = service;
                    }
                    void update(T value) override
                    {
                        this->event_data = value;
                        std::cout << this->m_name << " is Udpated " << std::endl;
                    }

                    virtual ~FieldNoNotifierAndGetter() {}
                    void HandleSet(ara::com::SOMEIP_MESSAGE::Message sd_msg, Socket &binding)
                    {
                        std::vector<uint8_t> _data = sd_msg.GetPayload();
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service->m_service_id.GetInstanceId(), (uint16_t)(sd_msg.MessageId().method_id | 0x8000)},
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

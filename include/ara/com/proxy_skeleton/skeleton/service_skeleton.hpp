/**
 * @file service_skeleton.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_
#define ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

// #include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
#include "ara/com/ipc/server/socket_Server.hpp"
#include "ara/com/ipc/client/socket_Client.hpp"
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/marshal.hpp"
#include <utility>
#include <unistd.h>
#include "ara/com/serializer.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
// #include <map>
#include <queue>
#include <future>

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {
                /**
                 * @brief class ServiceSkeleton
                 * 
                 */
                class ServiceSkeleton
                {
                public:
                    struct SK_Handle
                    {

                        uint32_t service_portnum;
                        uint32_t sd_portnum;
                        // CClient *m_server_UPD;
                    };
                    SK_Handle m_skeleton_handle;
                    ara::com::InstanceIdentifier &m_service_id;
                    ara::com::InstanceIdentifier &m_instance_id;
                    /**
                     * @brief Construct a new Service Skeleton object
                     * 
                     * @param service_id 
                     * @param instance 
                     * @param skeleton_handle 
                     * @param mode 
                     */
                    ServiceSkeleton(
                        InstanceIdentifier &service_id,
                        InstanceIdentifier &instance,
                        SK_Handle skeleton_handle,
                        MethodCallProcessingMode mode = MethodCallProcessingMode::kEvent)
                        : m_service_id(service_id),
                          m_skeleton_udp(SOCK_DGRAM),
                          m_instance_id(instance),
                          m_mode{mode},
                          m_skeleton_handle{skeleton_handle}
                    {

                        // skeleton_handle.m_server_UPD = &m_skeleton_udp;
                        this->cliaddr.sin_family = AF_INET; // IPv4
                        this->cliaddr.sin_addr.s_addr = INADDR_ANY;
                        this->cliaddr.sin_port = htons(m_skeleton_handle.sd_portnum);
                    }
                    /**
                     * @brief Destroy the Service Skeleton object
                     * 
                     */
                    virtual ~ServiceSkeleton() {}
                    /**
                     * @brief Offer Service 
                     * 
                     */
                    void OfferService()
                    {
                        this->m_skeleton_udp.OpenSocket();
                        const uint32_t minorV = 0;
                        const uint8_t majorV = 1;
                        SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
                        entry::ServiceEntry offer_service_e = entry::ServiceEntry::CreateOfferServiceEntry(m_service_id.GetInstanceId(), 0, majorV, minorV);
                        option::Ipv4EndpointOption optionA = option::Ipv4EndpointOption::CreateSdEndpoint(false, helper::Ipv4Address(127, 0, 0, 1), option::Layer4ProtocolType::Udp, m_skeleton_handle.service_portnum);
                        offer_service_e.AddFirstOption(&optionA);
                        sd_msg.AddEntry(&offer_service_e);
                        std::vector<uint8_t> _payload = sd_msg.Serializer();
                        uint32_t _size = _payload.size();
                        this->m_skeleton_udp.UDPSendTo((void *)&_size, sizeof(_size), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.UDPSendTo((void *)_payload.data(), _payload.size(), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.CloseSocket();
                    }
                    /**
                     * @brief StopOfferService
                     * 
                     */
                    void StopOfferService()
                    {
                        const uint32_t minorV = 0;
                        const uint8_t majorV = 1;
                        const uint32_t stop_ttl = 0;
                        this->m_skeleton_udp.OpenSocket();
                        // SD_data service = {m_service_id.GetInstanceId(), getpid() ,m_skeleton_handle.service_portnum, false};
                        SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
                        entry::ServiceEntry stop_offer_e = entry::ServiceEntry::CreateOfferServiceEntry(m_service_id.GetInstanceId(), 0, majorV, minorV, stop_ttl);
                        sd_msg.AddEntry(&stop_offer_e);
                        std::vector<uint8_t> _payload = sd_msg.Serializer();
                        uint32_t _size = _payload.size();
                        this->m_skeleton_udp.UDPSendTo((void *)&_size, sizeof(_size), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.UDPSendTo((void *)_payload.data(), _payload.size(), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.CloseSocket();
                    }

                    /**
                     * @brief
                     * @todo edit vector data in event info
                     * @tparam T
                     * @param event_id
                     * @param data
                     * @param is_field
                     * @param client_add
                     */
                    template <typename T>
                    void SendEvent(int event_id, const T &data, sockaddr_in client_add)
                    {
                        /* Serialize the data */
                        ara::com::Serializer ser;
                        ser.serialize(data);
                        std::vector<uint8_t> sermsg = ser.Payload();
                        /* Fill the event info object */
                        ara::com::proxy_skeleton::event_info msg_;
                        msg_.service_id = m_service_id.GetInstanceId();
                        msg_.event_id = event_id;
                        /* send the event info object then send the serialized data */
                        std::cout << "send event to client " << client_add.sin_port << std::endl;
                        // Create Mesaage {, event_id | 0x8000}, NOTIFICATION
                        ara::com::SOMEIP_MESSAGE::Message M1({(uint16_t)this->m_service_id.GetInstanceId(), (uint16_t)(event_id | 0x8000)}, {1, 2}, 3, 4, ara::com::SOMEIP_MESSAGE::MessageType::NOTIFICATION);
                        // SetPayload(sermsg)
                        M1.SetPayload(sermsg);
                        // vector jjj = mes.Serializer
                        std::vector<uint8_t> __payload = M1.Serializer();
                        // size of vector
                        uint32_t size = __payload.size();

                        this->m_skeleton_udp.OpenSocket();
                        this->m_skeleton_udp.UDPSendTo((void *)&size, sizeof(size), (sockaddr *)&client_add);
                        this->m_skeleton_udp.UDPSendTo((void *)&__payload[0], __payload.size(), (sockaddr *)&client_add);
                        this->m_skeleton_udp.CloseSocket();
                    }

                protected:
                    /**
                     * @brief 1- HandleCall  R ARGS
                     * 
                     * @tparam Class 
                     * @tparam R 
                     * @tparam Args 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename R, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        /**
                         * @brief Construct a new s Handle Call object
                         * 
                         */
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                    /**/
                    /**
                     * @brief 2- HandleCall future<void> ARGS
                     * 
                     * @tparam Class 
                     * @tparam Args 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                    /**
                     * @brief 3- HandleCall R
                     * 
                     * @tparam Class 
                     * @tparam R 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename R>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        R result = (c.*method)();
                        // create serialize object
                        ara::com::Serializer s1;
                        // serialize the result
                        s1.serialize(result);
                        // create SOME IP message
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service_id.GetInstanceId(), (uint16_t)(msg.MessageId().method_id & 0x7fff)},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);
                        // Setpayload in message
                        std::vector<uint8_t> _payload = s1.Payload();
                        R_msg.SetPayload(_payload);
                        _payload = R_msg.Serializer();
                        uint32_t msg_size = _payload.size();
                        // send message
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_payload.data(), msg_size);

                        binding.CloseSocket();
                    }
                    /**
                     * @brief 4- HandleCall future <void>
                     * 
                     * @tparam Class 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);
                        std::future<void> f = (c.*method)();
                        f.get();
                        std::vector<uint8_t> _payload = R_msg.Serializer();
                        uint32_t msg_size = _payload.size();
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_payload.data(), msg_size);
                        binding.CloseSocket();
                    }
                    /**
                     * @brief 5- HandleCall void ARGS
                     * 
                     * @tparam Class 
                     * @tparam Args 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        /**
                         * @brief Construct a new s Handle Call object
                         * 
                         */
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                    /**
                     * @brief 6- HandleCall void
                     * 
                     * @tparam Class 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class>
                    void HandleCall(Class &c,
                                    void (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        (c.*method)();
                        binding.CloseSocket();
                    }
                    /**
                     * @brief No Handler --> handle error
                     * 
                     * @param method_id 
                     * @param binding 
                     */
                    void NoHandler(uint16_t method_id, Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id.GetInstanceId(), method_id},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::ReturnCode::E_UNKNOWN_METHOD,
                            SOMEIP_MESSAGE::MessageType::ERROR);

                        std::vector<uint8_t> _Payload = R_msg.Serializer();
                        uint32_t size = _Payload.size();
                        binding.Send(&size, sizeof(size));
                        binding.Send(_Payload.data(), size);
                        binding.CloseSocket();
                    }
                private:
                /**
                 * @brief sHandleCall
                 * 
                 * @tparam Class 
                 * @tparam R 
                 * @tparam Args 
                 * @tparam index 
                 * @param c 
                 * @param method 
                 * @param msg 
                 * @param binding 
                 */
                    template <typename Class, typename R, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<R> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        vector<uint8_t> payload = msg.getload();
                        ara::com::Deserializer dser;
                        uint64_t xx = dser.deserialize<uint64_t>(payload, 0);

                        Marshal<Args...> unmarshaller(payload);
                        std::future<R> result = (c.*method)(unmarshaller.template unmarshal<index>()...);
                        R rval = result.get();
                        ara::com::Serializer ser;
                        ser.serialize(rval);
                        std::vector<uint8_t> _payload = ser.Payload();
                        R_msg.SetPayload(_payload);
                        _payload = R_msg.Serializer();
                        uint32_t msg_size = _payload.size();
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_payload.data(), msg_size);
                        binding.CloseSocket();
                    }
                    /**
                     * @brief sHandleCall handle return type future void
                     * 
                     * @tparam Class 
                     * @tparam Args 
                     * @tparam index 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<void> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket binding,
                                     std::index_sequence<index...>)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);

                        Marshal<Args...> unmarshaller(msg.GetPayload());

                        std::future<void> f = (c.*method)(unmarshaller.template unmarshal<index>()...);
                        f.get();
                        std::vector<uint8_t> _payload = R_msg.Serializer();
                        uint32_t msg_size = _payload.size();
                        binding.Send(&msg_size, sizeof(msg_size));
                        binding.Send(_payload.data(), msg_size);
                        binding.CloseSocket();
                    }
                    /**
                     * @brief sHandleCall handle return type void
                     * 
                     * @tparam Class 
                     * @tparam Args 
                     * @tparam index 
                     * @param c 
                     * @param method 
                     * @param msg 
                     * @param binding 
                     */
                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     void (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        Marshal<Args...> unmarshaller(msg.GetPayload());
                        (c.*method)(unmarshaller.template unmarshal<index>()...);
                    }
                    // Private variables
                    struct sockaddr_in cliaddr;
                    ara::com::MethodCallProcessingMode m_mode;
                    CClient m_skeleton_udp;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

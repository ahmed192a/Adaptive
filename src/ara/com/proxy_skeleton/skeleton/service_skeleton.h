/**
 * @file service_skeleton.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_
#define ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

#include "ara/com/proxy_skeleton/data_type.h"
#include "ara/com/ipc/server/socket_Server.h"
#include "ara/com/ipc/client/socket_Client.h"
#include "ara/com/SOMEIP/SomeipSDMessage.h"
#include "ara/com/serializer.h"
#include "ara/com/marshal.h"
#include <utility>
#include <unistd.h>
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
                    /**
                     * @struct ServiceSkeleton::SK_Handle
                     * @brief ServiceSkeleton handles the communication with the service
                     * 
                     */
                    struct SK_Handle
                    {

                        uint32_t service_portnum;   //!< service port number
                        uint32_t sd_portnum;        //!< Service Discovery port number
                    };
                    SK_Handle m_skeleton_handle;                        //!< skeleton handle
                    ara::com::proxy_skeleton::ServiceId &m_service_id;  //!< service id
                    ara::com::InstanceIdentifier &m_instance_id;        //!< instance id
                    
                    /**
                     * @brief Construct a new Service Skeleton object
                     * 
                     * @param service_id            service id of the service
                     * @param instance              instance id of the service
                     * @param skeleton_handle       skeleton handle
                     * @param mode                  mode of the service
                     */
                    ServiceSkeleton(
                        ara::com::proxy_skeleton::ServiceId &service_id,
                        InstanceIdentifier &instance,
                        SK_Handle skeleton_handle,
                        MethodCallProcessingMode mode = MethodCallProcessingMode::kEvent)
                        : m_service_id(service_id),
                          m_skeleton_udp(SOCK_DGRAM),
                          m_instance_id(instance),
                          m_mode{mode},
                          m_skeleton_handle{skeleton_handle}
                    {

                        this->cliaddr.sin_family = AF_INET;             // IPv4
                        this->cliaddr.sin_addr.s_addr = INADDR_ANY;     // IP of the client (INADDR_ANY = listen on all interfaces)
                        this->cliaddr.sin_port = htons(m_skeleton_handle.sd_portnum);   // Port of the client
                    }
                    /**
                     * @brief Destroy the Service Skeleton object
                     * 
                     */
                    virtual ~ServiceSkeleton() {}

                    /**
                     * @brief Get the Service Id object
                     * 
                     * @return const ara::com::proxy_skeleton::ServiceId 
                     */
                    const ara::com::proxy_skeleton::ServiceId GetServiceId()
                    {
                        return m_service_id;
                    }
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
                        entry::ServiceEntry offer_service_e = entry::ServiceEntry::CreateOfferServiceEntry(m_service_id, m_instance_id.GetInstanceId(), majorV, minorV);
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
                        //entry::ServiceEntry stop_offer_e = entry::ServiceEntry::CreateOfferServiceEntry(m_service_id, 0, majorV, minorV, stop_ttl);
                        entry::ServiceEntry stop_offer_e = entry::ServiceEntry::CreateStopOfferEntry(m_service_id, m_instance_id.GetInstanceId(), majorV, minorV);
                        sd_msg.AddEntry(&stop_offer_e);
                        std::vector<uint8_t> _payload = sd_msg.Serializer();
                        uint32_t _size = _payload.size();
                        this->m_skeleton_udp.UDPSendTo((void *)&_size, sizeof(_size), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.UDPSendTo((void *)_payload.data(), _payload.size(), (struct sockaddr *)&this->cliaddr);
                        this->m_skeleton_udp.CloseSocket();
                    }

                    /**
                     * @brief SendEvent     send an event update to clients
                     * @tparam T            type of the event
                     * @param event_id      event id
                     * @param data          data of the event
                     * @param client_add    client address
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
                        msg_.service_id = m_service_id;
                        msg_.event_id = event_id;
                        /* send the event info object then send the serialized data */
                        std::cout << "send event to client " << client_add.sin_port << std::endl;
                        // Create Mesaage {, event_id | 0x8000}, NOTIFICATION
                        ara::com::SOMEIP_MESSAGE::Message M1({(uint16_t)this->m_service_id, (uint16_t)(event_id | 0x8000)}, {1, 2}, 3, 4, ara::com::SOMEIP_MESSAGE::MessageType::NOTIFICATION);
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
                    /**
                     * @brief NoServiceHandler --> handle error
                     * 
                     * @param S_msg         --> message from client
                     * @param binding       --> binding of the client
                     */
                    static void NoServiceHandler(SOMEIP_MESSAGE::Message S_msg, Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            SOMEIP_MESSAGE::Message_ID{S_msg.MessageId().serivce_id, S_msg.MessageId().method_id}, 
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::ReturnCode::E_UNKNOWN_SERVICE,
                            SOMEIP_MESSAGE::MessageType::ERROR);

                        std::vector<uint8_t> _Payload = R_msg.Serializer();
                        uint32_t size = _Payload.size();
                        binding.Send(&size, sizeof(size));
                        binding.Send(_Payload.data(), size);
                        binding.CloseSocket();
                    }

                protected:
                    /**
                     * @brief 1- HandleCall  R ARGS
                     * 
                     * @tparam Class        Class to call the method on
                     * @tparam R            Return type of the method
                     * @tparam Args         Argument types of the method
                     * @param c             object of type Class to call the method on
                     * @param method        method to be called
                     * @param msg           message from client
                     * @param binding       binding of the client
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
                     * @tparam Class        Class to call the method on
                     * @tparam Args         Argument types of the method
                     * @param c             object of type Class to call the method on
                     * @param method        method to be called
                     * @param msg           message from client
                     * @param binding       binding of the client
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
                     * @tparam Class        Class to call the method on
                     * @tparam R            Return type of the method
                     * @param c             object of type Class to call the method on
                     * @param method        method to be called
                     * @param msg           message from client
                     * @param binding       binding of the client
                     */
                    template <typename Class, typename R>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        std::future<R> f = (c.*method)();
                        R result = f.get();
                        // create serialize object
                        ara::com::Serializer s1;
                        // serialize the result
                        s1.serialize(result);
                        // create SOME IP message
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{(uint16_t)this->m_service_id, (uint16_t)(msg.MessageId().method_id & 0x7fff)},
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
                     * @brief 4- HandleCall future void
                     * 
                     * @tparam Class        Class to call the method on
                     * @param c             object of type Class to call the method on
                     * @param method        method to be called
                     * @param msg           message from client
                     * @param binding       binding of the client
                     */
                    template <typename Class>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id, msg.MessageId().method_id},
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
                     * @tparam Class    Class to call the method on
                     * @tparam Args     Argument types of the method
                     * @param c         object of type Class to call the method on
                     * @param method    method to be called
                     * @param msg       message from client
                     * @param binding   binding of the client
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
                     * @tparam Class    Class to call the method on
                     * @param c         object of type Class to call the method on
                     * @param method    method to be called
                     * @param msg       message from client
                     * @param binding   binding of the client
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
                     * @param method_id     method id of the method that was called
                     * @param binding       binding of the client
                     */
                    void NoMethodHandler(uint16_t method_id, Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Request_ID{5, 6},
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id, method_id},
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
                 * @tparam Class    Class to call the method on
                 * @tparam R        Return type of the method
                 * @tparam Args     Argument types of the method
                 * @tparam index    index of the method
                 * @param c         object of type Class to call the method on
                 * @param method    method to be called
                 * @param msg       message from client
                 * @param binding   binding of the client
                 */
                    template <typename Class, typename R, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<R> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id, msg.MessageId().method_id},
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
                     * @tparam Class        Class to call the method on
                     * @tparam Args         Argument types of the method
                     * @tparam index        index of the method
                     * @param c             object of type Class to call the method on
                     * @param method        method to be called
                     * @param msg           message from client
                     * @param binding       binding of the client
                     */
                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<void> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket binding,
                                     std::index_sequence<index...>)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{this->m_service_id, msg.MessageId().method_id},
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
                     * @tparam Class    Class to call the method on
                     * @tparam Args     The types of the arguments to the method
                     * @tparam index    The size of the index sequence
                     * @param c         The object to call the method on
                     * @param method    The method to call
                     * @param msg       The message to handle
                     * @param binding   The socket to send the response on
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
        }  // proxy_skeleton
    }  // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_SERVICE_SKELETON_H_

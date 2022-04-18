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

                class ServiceSkeleton
                {
                public:
                    struct SK_Handle
                    {
                       
                        uint32_t service_portnum;
                        uint32_t sd_portnum;
                         //CClient *m_server_UPD;
                    };
                    SK_Handle m_skeleton_handle;
                    ara::com::InstanceIdentifier &m_service_id;
                    ara::com::InstanceIdentifier &m_instance_id;

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

                    virtual ~ServiceSkeleton() {}

                    void OfferService() 
                    {
                        this->m_skeleton_udp.OpenSocket();
                        const uint32_t minorV= 0;
                        const uint8_t majorV= 1;
                        SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
                        entry::ServiceEntry offer_service_e = entry::ServiceEntry::CreateOfferServiceEntry (m_service_id.GetInstanceId(),0, majorV, minorV);
                        option::Ipv4EndpointOption optionA=option::Ipv4EndpointOption::CreateSdEndpoint(false ,helper::Ipv4Address(127, 0, 0, 1) ,option::Layer4ProtocolType::Udp,m_skeleton_handle.service_portnum);
                        offer_service_e.AddFirstOption(&optionA);
                        sd_msg.AddEntry(&offer_service_e);
                        std::vector<uint8_t> _payload = sd_msg.Serializer();
                        uint32_t _size=_payload.size();
                        this->m_skeleton_udp.UDPSendTo((  void *)&_size, sizeof(_size), ( struct sockaddr *) &this->cliaddr);
                        this->m_skeleton_udp.UDPSendTo((  void *)_payload.data(), _payload.size(), ( struct sockaddr *) &this->cliaddr);   
                        this->m_skeleton_udp.CloseSocket();
                    }

                    void StopOfferService() 
                    {
                        const uint32_t minorV= 0;
                        const uint8_t majorV= 1;
                        const uint32_t stop_ttl = 0;
                        this->m_skeleton_udp.OpenSocket();
                        // SD_data service = {m_service_id.GetInstanceId(), getpid() ,m_skeleton_handle.service_portnum, false};
                        SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
                        entry::ServiceEntry stop_offer_e = entry::ServiceEntry::CreateOfferServiceEntry (m_service_id.GetInstanceId(),0, majorV, minorV,stop_ttl);
                        sd_msg.AddEntry(&stop_offer_e);
                        std::vector<uint8_t> _payload = sd_msg.Serializer();
                        uint32_t _size = _payload.size();
                        this->m_skeleton_udp.UDPSendTo((  void *)&_size, sizeof(_size), ( struct sockaddr *) &this->cliaddr);
                        this->m_skeleton_udp.UDPSendTo((  void *)_payload.data(), _payload.size(), ( struct sockaddr *) &this->cliaddr);
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
                        msg_.operation = 0;
                        msg_.data_size = sermsg.size();
                        /* send the event info object then send the serialized data */
                        std::cout<<"send event to client "<< client_add.sin_port<<std::endl;
                        this->m_skeleton_udp.OpenSocket();
                        this->m_skeleton_udp.UDPSendTo((void *)&msg_, sizeof(msg_), (sockaddr *)&client_add);
                        this->m_skeleton_udp.UDPSendTo((void *)&sermsg[0], sermsg.size(), (sockaddr *)&client_add);
                        this->m_skeleton_udp.CloseSocket();
                    }

                protected:
                /*1 R ARGS*/
                    template <typename Class, typename R, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<R> (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                /*2 future<void> ARGS*/
                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                /*3 R */
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
                            SOMEIP_MESSAGE::Message_ID{ this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5,6},
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
                /*4 future <void>*/
                    template <typename Class>
                    void HandleCall(Class &c,
                                    std::future<void> (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                                SOMEIP_MESSAGE::Message_ID{ this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                                SOMEIP_MESSAGE::Request_ID{5,6},
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
                /*5 void ARGS*/
                    template <typename Class, typename... Args>
                    void HandleCall(Class &c,
                                    void (Class::*method)(Args...),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
                    }
                /*6 void */
                    template <typename Class>
                    void HandleCall(Class &c,
                                    void (Class::*method)(),
                                    SOMEIP_MESSAGE::Message msg,
                                    Socket &binding)
                    {
                        (c.*method)();
                    }

                    template <typename T>
                    std::future<T> NoHandler()
                    {
                        std::promise<T> p;
                        try
                        {
                            // code that may throw
                            throw std::runtime_error("Field No Handler");
                        }
                        catch (...)
                        {
                            try
                            {
                                // store anything thrown in the promise
                                p.set_exception(std::current_exception());
                            }
                            catch (...)
                            {
                            } // set_exception() may throw too
                        }

                        return p.get_future();
                    }

                private:
                    template <typename Class, typename R, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                      std::future<R> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket &binding,
                                     std::index_sequence<index...>)
                    {
                        SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{ this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5,6},
                            2, // protocol version
                            7, // Interface Version
                            SOMEIP_MESSAGE::MessageType::RESPONSE);
                            
                        Marshal<Args...> unmarshaller(msg.GetPayload());
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
                    template <typename Class, typename... Args, std::size_t... index>
                    void sHandleCall(Class &c,
                                     std::future<void> (Class::*method)(Args...),
                                     SOMEIP_MESSAGE::Message msg,
                                     Socket binding,
                                     std::index_sequence<index...>)
                    {
                       SOMEIP_MESSAGE::Message R_msg(
                            SOMEIP_MESSAGE::Message_ID{ this->m_service_id.GetInstanceId(), msg.MessageId().method_id},
                            SOMEIP_MESSAGE::Request_ID{5,6},
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

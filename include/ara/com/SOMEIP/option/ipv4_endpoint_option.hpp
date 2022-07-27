/**
 * @file ipv4_endpoint_option.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IPV4_ENDPOINT_OPTION_H
#define IPV4_ENDPOINT_OPTION_H

#include <stdexcept>
#include "ara/com/SOMEIP/option/option.hpp"
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"

namespace ara
{
    namespace com
    {
        namespace option
        {
            /// @brief IPv4 endpoint option for both generic and service discovery purposes
            class Ipv4EndpointOption : public Option
            {
            private:
                static const Layer4ProtocolType DefaultSdProtocol = Layer4ProtocolType::Udp;    //!< default protocol for service discovery messages is UDP
                static const uint16_t DefaultSdPort = 30490;                            //!< default port for service discovery messages is 30490

                helper::Ipv4Address GBIpAddress;                        //!< IPv4 address of the gateway
                Layer4ProtocolType GBL4Proto;                           //!< Layer 4 protocol of the gateway
                uint16_t GBPort;                                        //!< port of the gateway

                // constexpr Ipv4EndpointOption(
                //     OptionType type,
                //     bool discardable,
                //     helper::Ipv4Address ipAddress,
                //     Layer4ProtocolType protocol,
                //     uint16_t port) noexcept : Option(type, discardable),
                //                               GBIpAddress{ipAddress},
                //                               GBL4Proto{protocol},
                //                               GBPort{port}
                // {
                // }

            public:
            /**
             * @brief constructor for IPv4 endpoint option
             * 
             * @param type option type
             * @param discardable option discardable flag
             * @param ipAddress IPv4 address of the gateway
             * @param protocol Layer 4 protocol of the gateway
             * @param port port of the gateway
             */
            constexpr Ipv4EndpointOption(
                    OptionType type,
                    bool discardable,
                    helper::Ipv4Address ipAddress,
                    Layer4ProtocolType protocol,
                    uint16_t port) noexcept : Option(type, discardable),
                                              GBIpAddress{ipAddress},
                                              GBL4Proto{protocol},
                                              GBPort{port}
                {
                }

                Ipv4EndpointOption() = delete;
                /**
                 * @brief Destroy the Ipv 4 Endpoint Option object
                 * 
                 */
                ~Ipv4EndpointOption(){}
                /**
                 * @brief Get Length of the IPv4 endpoint option
                 * 
                 * @return uint16_t 
                 */
                uint16_t Length() const noexcept override;

                /// @brief Get IP address
                /// @returns IPv4 address
                helper::Ipv4Address IpAddress() const noexcept;

                /// @brief Get protocol
                /// @returns OSI layer-4 protocol
                Layer4ProtocolType L4Proto() const noexcept;

                /// @brief Get port
                /// @returns Network port number
                uint16_t Port() const noexcept;

                std::vector<uint8_t> Payload()  override;

                /// @brief Unitcast endpoint factory
                /// @param discardable Indicates whether the option can be discarded or not
                /// @param ipAddress IP address
                /// @param protocol Layer-4 protocol
                /// @param port Port number
                /// @returns Unicast IPv4 endpoint
                static Ipv4EndpointOption CreateUnitcastEndpoint(
                    bool discardable,
                    helper::Ipv4Address ipAddress,
                    Layer4ProtocolType protocol,
                    uint16_t port) noexcept;

                /// @brief Multicast endpoint factory
                /// @param discardable Indicates whether the option can be discarded or not
                /// @param ipAddress IP address
                /// @param port Port number
                /// @returns Multicast IPv4 endpoint
                static Ipv4EndpointOption CreateMulticastEndpoint(
                    bool discardable,
                    helper::Ipv4Address ipAddress,
                    uint16_t port);

                /// @brief Service discovery factroy
                /// @param discardable Indicates whether the option can be discarded or not
                /// @param ipAddress IP address
                /// @param protocol Layer-4 protocol
                /// @param port Port number
                /// @returns Service discovery IPv4 endpoint
                static Ipv4EndpointOption CreateSdEndpoint(
                    bool discardable,
                    helper::Ipv4Address ipAddress,
                    Layer4ProtocolType protocol = DefaultSdProtocol,
                    uint16_t port = DefaultSdPort) noexcept;
            };
        }
    }
}

#endif
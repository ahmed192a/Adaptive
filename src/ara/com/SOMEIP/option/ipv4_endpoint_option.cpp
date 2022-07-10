/**
 * @file ipv4_endpoint_option.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.hpp"

namespace ara
{
    namespace com
    {
        namespace option
        {
            uint16_t Ipv4EndpointOption::Length() const noexcept
            {
                const uint8_t OptionLength = 9;
                return OptionLength;
            }

            helper::Ipv4Address Ipv4EndpointOption::IpAddress() const noexcept
            {
                return GBIpAddress;
            }

            Layer4ProtocolType Ipv4EndpointOption::L4Proto() const noexcept
            {
                return GBL4Proto;
            }

            uint16_t Ipv4EndpointOption::Port() const noexcept
            {
                return GBPort;
            }

            std::vector<uint8_t> Ipv4EndpointOption::Payload() 
            {
                std::vector<uint8_t> _result = Option::BasePayload();

                GBIpAddress.Inject(_result); 

                const uint8_t ReservedByte = 0x00;
                _result.push_back(ReservedByte);

                uint8_t _protocolByte = static_cast<uint8_t>(GBL4Proto);
                _result.push_back(_protocolByte);

                helper::Inject(_result, GBPort);

                return _result;
            }

            Ipv4EndpointOption Ipv4EndpointOption::CreateUnitcastEndpoint(
                bool discardable,
                helper::Ipv4Address ipAddress,
                Layer4ProtocolType protocol,
                uint16_t port) noexcept
            {
                Ipv4EndpointOption _result(
                    OptionType::IPv4Endpoint,
                    discardable,
                    ipAddress,
                    protocol,
                    port);

                return _result;
            }

            Ipv4EndpointOption Ipv4EndpointOption::CreateMulticastEndpoint(
                bool discardable,
                helper::Ipv4Address ipAddress,
                uint16_t port)
            {
                const uint8_t MulticastOctetMin = 224;
                const uint8_t MulticastOctetMax = 239;

                uint8_t _firstOctet = ipAddress.Octets[0];
                if ((_firstOctet < MulticastOctetMin) ||
                    (_firstOctet > MulticastOctetMax))
                {
                    throw std::invalid_argument("IP address is out of range.");
                }

                Ipv4EndpointOption _result(
                    OptionType::IPv4Multicast,
                    discardable,
                    ipAddress,
                    Layer4ProtocolType::Udp,
                    port);

                return _result;
            }

            Ipv4EndpointOption Ipv4EndpointOption::CreateSdEndpoint(
                bool discardable,
                helper::Ipv4Address ipAddress,
                Layer4ProtocolType protocol,
                uint16_t port) noexcept
            {
                Ipv4EndpointOption _result(
                    OptionType::IPv4SdEndpoint,
                    discardable,
                    ipAddress,
                    protocol,
                    port);

                return _result;
            }
        }
    }
}
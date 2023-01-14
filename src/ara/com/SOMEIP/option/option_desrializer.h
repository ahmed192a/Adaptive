/**
 * @file option_desrializer.hpp
 * @author 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef OPTION_DESRIALIZER_H
#define OPTION_DESRIALIZER_H
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.h"
#include "ara/com/SOMEIP/option/option.h"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.h"
namespace ara{
    namespace com{
        namespace option{
            /**
             * @brief Class for Option deserialization
             * 
             */
            class OptionDeserializer
            {
            public:
                /**
                 * @brief Deserialize Option from byte array
                 * 
                 * @param payload   byte array containing Option payload
                 * @param offset    offset in byte array
                 * @return Option*  pointer to deserialized Option
                 */
                static Option* Deserialize(
                    const std::vector<uint8_t> &payload,
                    std::size_t offset) noexcept
                    {
                        offset +=2;
                        Option* _result = nullptr;
                        const OptionType _optionType = static_cast<OptionType>(payload[offset]);
                        offset += 1;
                        bool _discardable = payload[offset] & 0x01;
                        offset += 1;
                        switch(_optionType)
                        {
                            case OptionType::IPv4Endpoint:
                            {
                                helper::Ipv4Address _ipAddress(
                                    payload[offset],
                                    payload[offset + 1],
                                    payload[offset + 2],
                                    payload[offset + 3]);
                                offset += 4;
                                const uint8_t _reservedByte = payload[offset];
                                offset += 1;
                                const uint8_t _protocolByte = payload[offset];
                                offset += 1;
                                const uint16_t _port = (payload[offset] << 8) | payload[offset + 1];
                                offset += 2;
                                _result = new Ipv4EndpointOption(
                                    OptionType::IPv4Endpoint,
                                    _discardable,
                                    _ipAddress,
                                    static_cast<Layer4ProtocolType>(_protocolByte),
                                    _port);
                                break;
                            }
                            case OptionType::IPv4Multicast:
                            {
                                helper::Ipv4Address _ipAddress(
                                    payload[offset],
                                    payload[offset + 1],
                                    payload[offset + 2],
                                    payload[offset + 3]);
                                offset += 4;
                                const uint8_t _reservedByte = payload[offset];
                                offset += 1;
                                const uint8_t _protocolByte = payload[offset];
                                offset += 1;
                                const uint16_t _port = (payload[offset] << 8) | payload[offset + 1];
                                offset += 2;
                                _result = new Ipv4EndpointOption(
                                    OptionType::IPv4Multicast,
                                    _discardable,
                                    _ipAddress,
                                    static_cast<Layer4ProtocolType>(_protocolByte),
                                    _port);
                                break;
                            }
                            case OptionType::IPv4SdEndpoint:
                            {
                                helper::Ipv4Address _ipAddress(
                                    payload[offset],
                                    payload[offset + 1],
                                    payload[offset + 2],
                                    payload[offset + 3]);
                                offset += 4;
                                const uint8_t _reservedByte = payload[offset];
                                offset += 1;
                                const uint8_t _protocolByte = payload[offset];
                                offset += 1;
                                const uint16_t _port = (payload[offset] << 8) | payload[offset + 1];
                                offset += 2;
                                _result = new Ipv4EndpointOption(
                                    OptionType::IPv4SdEndpoint,
                                    _discardable,
                                    _ipAddress,
                                    static_cast<Layer4ProtocolType>(_protocolByte),
                                    _port);
                                break;
                            }
                            case OptionType::LoadBalancing: // not implemented
                            default:
                            {
                                _result = nullptr;
                                break;
                            }
                        }
                        return _result;

                    }
            };

        }
    }
}
#endif // OPTION_DESRIALIZER_H
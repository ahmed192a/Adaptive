/**
 * @file ipv4_address.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IPV4_ADDRESS_H
#define IPV4_ADDRESS_H

#include <array>
#include <vector>
#include <stdint.h>

namespace ara
{
    namespace com
    {
        namespace helper
        {
            /// @brief IPv4 address wrapper helper
            class Ipv4Address
            {
                public:
                /// @brief IPv4 address octets
                std::array<uint8_t, 4> Octets;

                Ipv4Address() = delete;

                /// @brief Constructor
                /// @param octet0 IPv4 first octet
                /// @param octet1 IPv4 second octet
                /// @param octet2 IPv4 third octet
                /// @param octet3 IPv4 forth octet
                Ipv4Address(
                    uint8_t octet0,
                    uint8_t octet1,
                    uint8_t octet2,
                    uint8_t octet3) noexcept;

                ~Ipv4Address() noexcept = default;

                /// @brief Inject an IP address into a byte vector
                /// @param vector Byte vector
                /// @param ipAddress IP address to be injected
                void Inject(
                    std::vector<uint8_t> &vector);

                
                /// @brief Ipv4Address equality operator override
                /// @param address1 First address to compare
                /// @param address2 Second address to compare
                /// @returns True if both addresses are equal; otherwise false
                bool operator==(Ipv4Address address2)
                {
                    bool _result =
                        (this->Octets[0] == address2.Octets[0]) &&
                        (this->Octets[1] == address2.Octets[1]) &&
                        (this->Octets[2] == address2.Octets[2]) &&
                        (this->Octets[3] == address2.Octets[3]);

                    return _result;
                }

                /// @brief Ipv4Address inequality operator override
                /// @param address1 First address to compare
                /// @param address2 Second address to compare
                /// @returns True if both addresses are not equal; otherwise false
                bool operator!=(Ipv4Address address2)
                {
                    bool _result = !(*this == address2);

                    return _result;
                }
            };

        }
    }
}

#endif
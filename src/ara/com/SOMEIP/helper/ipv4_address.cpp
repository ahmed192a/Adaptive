/**
 * @file ipv4_address.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"

namespace ara
{
    namespace com
    {
        namespace helper
        {
            Ipv4Address::Ipv4Address(
                uint8_t octet0,
                uint8_t octet1,
                uint8_t octet2,
                uint8_t octet3) noexcept : Octets{octet0, octet1, octet2, octet3}
            {
            }

            void Ipv4Address::Inject(std::vector<uint8_t> &vector)
            {
                vector.insert(
                    vector.end(),
                    this->Octets.begin(),
                    this->Octets.end());
            }
        };
    }
}
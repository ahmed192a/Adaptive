/**
 * @file service_entry.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/entry/service_entry.hpp"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            ServiceEntry::ServiceEntry(EntryType type,
                                       uint16_t serviceId,
                                       uint16_t instanceId,
                                       uint32_t ttl,
                                       uint8_t majorVersion,
                                       uint32_t minorVersion) noexcept : Entry(type, serviceId, instanceId, ttl, majorVersion),
                                                                         GBMinorVersion{minorVersion}
            {
            }

            bool ServiceEntry::ValidateOption(
                const option::Option *option) const noexcept
            {
                bool _result = Entry::ValidateOption(option);

                // Multicast option is not allowed in service entries.
                _result &=
                    (option->Type() != option::OptionType::IPv4Multicast) &&
                    (option->Type() != option::OptionType::IPv6Multicast);

                return _result;
            }

            
            uint32_t ServiceEntry::MinorVersion() const noexcept
            {
                return GBMinorVersion;
            }

            std::vector<uint8_t> ServiceEntry::Payload(uint8_t &optionIndex) const
            {
                std::vector<uint8_t> _result = Entry::BasePayload(optionIndex);
                helper::Inject(_result, GBMinorVersion);

                return _result;
            }

            ServiceEntry ServiceEntry::CreateFindServiceEntry(
                uint16_t serviceId,
                uint32_t ttl,
                uint16_t instanceId,
                uint8_t majorVersion,
                uint32_t minorVersion)
            {
                const EntryType cFindServiceEntry = EntryType::Finding;

                if (ttl == 0)
                {
                    throw std::invalid_argument("find TTL cannot be zero.");
                }

                ServiceEntry _result(
                    cFindServiceEntry,
                    serviceId,
                    instanceId,
                    ttl,
                    majorVersion,
                    minorVersion);

                return _result;
            }

            ServiceEntry ServiceEntry::CreateOfferServiceEntry(
                uint16_t serviceId,
                uint16_t instanceId,
                uint8_t majorVersion,
                uint32_t minorVersion,
                uint32_t ttl )
            {
                const EntryType cOfferServiceEntry = EntryType::Offering;

                if (ttl == 0)
                {
                    throw std::invalid_argument("offer TTL cannot be zero.");
                }

                ServiceEntry _result(
                    cOfferServiceEntry,
                    serviceId,
                    instanceId,
                    ttl,
                    majorVersion,
                    minorVersion);

                return _result;
            }

            ServiceEntry ServiceEntry::CreateStopOfferEntry(
                uint16_t serviceId,
                uint16_t instanceId,
                uint8_t majorVersion,
                uint32_t minorVersion) noexcept
            {
                const EntryType OfferServiceEntry = EntryType::Offering;
                const uint32_t StopOfferTTL = 0x000000;

                ServiceEntry _result(
                    OfferServiceEntry,
                    serviceId,
                    instanceId,
                    StopOfferTTL,
                    majorVersion,
                    minorVersion);

                return _result;
            }
        }
    }
}
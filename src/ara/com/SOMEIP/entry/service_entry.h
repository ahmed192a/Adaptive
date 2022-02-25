#ifndef SERVICE_ENTRY_H
#define SERVICE_ENTRY_H

#include <stdint.h>
#include "entry.h"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            /// @brief Entry to find and offer a service
            class ServiceEntry : public Entry
            {
            private:
                static const uint32_t InfiniteTtl = 0xffffff;
                static const uint16_t AnyInstanceId = 0xffff;
                static const uint32_t AnyMinorVersion = 0xffffffff;

                uint32_t GBMinorVersion;

                ServiceEntry(EntryType type,
                             uint16_t serviceId,
                             uint16_t instanceId,
                             uint32_t ttl,
                             uint8_t majorVersion,
                             uint32_t minorVersion) noexcept;

            protected:
                virtual bool ValidateOption(
                    const option::Option *option) const noexcept override;

            public:
                ServiceEntry() = delete;

                /// @brief Get minor version
                /// @returns Service minor version
                uint32_t MinorVersion() const noexcept;

                virtual std::vector<uint8_t> Payload(uint8_t &optionIndex) const override;

                /// @brief Find a service entry factory
                /// @param serviceId Service in interest ID
                /// @param ttl Entry time to live
                /// @param instanceId Service in interest instance ID
                /// @param majorVersion Service in interest major version
                /// @param minorVersion Service in interest minor version
                /// @returns Find service entry
                static ServiceEntry CreateFindServiceEntry(
                    uint16_t serviceId,
                    uint32_t ttl = InfiniteTtl,
                    uint16_t instanceId = AnyInstanceId,
                    uint8_t majorVersion = AnyMajorVersion,
                    uint32_t minorVersion = AnyMinorVersion);

                /// @brief Offer a service entry factory
                /// @param serviceId Service in interest ID
                /// @param instanceId Service in interest instance ID
                /// @param majorVersion Service in interest major version
                /// @param minorVersion Service in interest minor version
                /// @returns Offer service entry
                static ServiceEntry CreateOfferServiceEntry(
                    uint16_t serviceId,
                    uint16_t instanceId,
                    uint8_t majorVersion,
                    uint32_t minorVersion,
                    uint32_t ttl = InfiniteTtl);

                /// @brief Stop offer a service entry factory
                /// @param serviceId Service in interest ID
                /// @param instanceId Service in interest instance ID
                /// @param majorVersion Service in interest major version
                /// @param minorVersion Service in interest minor version
                /// @returns Stop service offering entry
                static ServiceEntry CreateStopOfferEntry(
                    uint16_t serviceId,
                    uint16_t instanceId,
                    uint8_t majorVersion,
                    uint32_t minorVersion) noexcept;
            };
        }
    }
}

#endif
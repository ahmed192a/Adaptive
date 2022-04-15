/**
 * @file eventgroup_entry.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef EVENTGROUP_ENTRY_H
#define EVENTGROUP_ENTRY_H

#include "ara/com/SOMEIP/entry/entry.hpp"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            /// @brief Entry to subscribe/unsubscribe to/from an event-group
            class EventgroupEntry : public Entry
            {
            private:
                static const uint32_t NackTTL = 0x000000;
                uint16_t GBEventgroupId;

                

                bool isAcknowledge() const noexcept;

            protected:
                virtual bool ValidateOption(
                    const option::Option *option) const noexcept override{return  false;}

            public:
                EventgroupEntry(EntryType type,
                                             uint16_t serviceId,
                                             uint16_t instanceId,
                                             uint32_t ttl,
                                             uint8_t majorVersion,
                                             uint16_t eventgroupId) noexcept : Entry(type, serviceId, instanceId, ttl, majorVersion),
                                                                               GBEventgroupId{eventgroupId}
                {
                }
                // EventgroupEntry(EntryType type,
                //                 uint16_t serviceId,
                //                 uint16_t instanceId,
                //                 uint32_t ttl,
                //                 uint8_t majorVersion,
                //                 uint16_t eventgroupId) noexcept;
                EventgroupEntry() = delete;

                /// @brief Get event-group ID
                /// @returns Event-group ID for subscription/unsubscription
                uint16_t EventgroupId() const noexcept;

                virtual std::vector<uint8_t> Payload(uint8_t &optionIndex) const override;

                /// @brief Subscribe to an event-group entry factory
                /// @param serviceId Service in interest ID
                /// @param instanceId Service in interest instance ID
                /// @param majorVersion Service in interest major version
                /// @param eventgroupId Event-group in interest ID
                /// @returns Subscribe event-group entry
                static EventgroupEntry CreateSubscribeEventEntry(
                    uint16_t serviceId,
                    uint16_t instanceId,
                    uint8_t majorVersion,
                    uint16_t eventgroupId) noexcept;

                /// @brief Unsubscribe from an event-group entry factory
                /// @param serviceId Service in interest ID
                /// @param instanceId Service in interest instance ID
                /// @param majorVersion Service in interest major version
                /// @param eventgroupId Event-group in interest ID
                /// @returns Unsubscribe event-group entry
                static EventgroupEntry CreateUnsubscribeEventEntry(
                    uint16_t serviceId,
                    uint16_t instanceId,
                    uint8_t majorVersion,
                    uint16_t eventgroupId) noexcept;

                /// @brief Positive acknowledge of an event-group entry factory
                /// @param eventgroupEntry Received subscribe event-group entry
                /// @returns Acknowledge event-group subscription entry
                static EventgroupEntry CreateAcknowledgeEntry(
                    const EventgroupEntry &eventgroupEntry) noexcept;

                /// @brief Negative acknowledge of an event-group entry factory
                /// @param eventgroupEntry Received subscribe event-group entry
                /// @returns Negative acknowledge event-group subscription entry
                static EventgroupEntry CreateNegativeAcknowledgeEntry(
                    const EventgroupEntry &eventgroupEntry) noexcept;
            };
        }
    }
}

#endif
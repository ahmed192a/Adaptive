#ifndef LOADBALANCING_OPTION_H
#define LOADBALANCING_OPTION_H

#include "option.h"

namespace ara
{
    namespace com
    {
        namespace option
        {
            /// @brief Service load balancing option
            class LoadBalancingOption : public Option
            {
            private:
                uint16_t GBPriority;
                uint16_t GBWeight;

            public:
                LoadBalancingOption() = delete;

                /// @brief Constructor
                /// @param discardable Indicates whether the option can be discarded or not
                /// @param priority Service instance priority
                /// @param weight Servince instance random selection weight
                constexpr LoadBalancingOption(
                    bool discardable,
                    uint16_t priority,
                    uint16_t weight) noexcept : Option(OptionType::LoadBalancing, discardable),
                                                GBPriority{priority},
                                                GBWeight{weight}
                {
                }

                virtual uint16_t Length() const noexcept override;

                /// @brief Get priority
                /// @returns Service instance priority
                uint16_t Priority() const noexcept;

                /// @brief Get weight
                /// @returns Servince instance random selection weight
                uint16_t Weight() const noexcept;

                virtual std::vector<uint8_t> Payload()  override;
            };
        }
    }
}

#endif
/**
 * @file loadbalancing_option.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "./loadbalancing_option.h"

namespace ara
{
    namespace com
    {
        namespace option
        {
            uint16_t LoadBalancingOption::Length() const noexcept
            {
                const uint8_t OptionLength = 5;
                return OptionLength;
            }

            uint16_t LoadBalancingOption::Priority() const noexcept
            {
                return GBPriority;
            }

            uint16_t LoadBalancingOption::Weight() const noexcept
            {
                return GBWeight;
            }

            std::vector<uint8_t> LoadBalancingOption::Payload() 
            {
                auto _result = Option::BasePayload();

                helper::Inject(_result, GBPriority);
                helper::Inject(_result, GBWeight);

                return _result;
            }
        }
    }
}
/**
 * @file option.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/option/option.hpp"

namespace ara
{
    namespace com
    {
        namespace option
        {
            OptionType Option::Type() const noexcept
            {
                return GBType;
            }

            bool Option::Discardable() const noexcept
            {
                return GBDiscardable;
            }

            std::vector<uint8_t> Option::BasePayload() 
            {
                std::vector<uint8_t> _result;

                helper::Inject(_result, Length());

                uint8_t _type = static_cast<uint8_t>(GBType);
                _result.push_back(_type);

                const uint8_t _discardableFlag = static_cast<uint8_t>(GBDiscardable);
                _result.push_back(_discardableFlag);

                return _result;
            }
        }
    }
}
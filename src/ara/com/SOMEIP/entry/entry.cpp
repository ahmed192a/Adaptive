/**
 * @file entry.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/entry/entry.hpp"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            Entry::Entry(EntryType type,
                         uint16_t serviceId,
                         uint16_t instanceId,
                         uint32_t ttl, 
                         uint8_t majorVersion) noexcept :GBType{type},
                                                         GBServiceId{serviceId},
                                                         GBInstanceId{instanceId},
                                                         GBMajorVersion{majorVersion},
                                                         GBTTL{ttl}
            {
            }

            

            bool Entry::ContainsOption(option::OptionType optionType) const noexcept
            {
                for (auto firstOption : GBFirstOptions)
                {
                    if (firstOption->Type() == optionType)
                    {
                        return true;
                    }
                }

                for (auto secondOption : GBSecondOptions)
                {
                    if (secondOption->Type() == optionType)
                    {
                        return true;
                    }
                }

                return false;
            }

            EntryType Entry::Type() const noexcept
            {
                return GBType;
            }

            uint16_t Entry::ServiceId() const noexcept
            {
                return GBServiceId;
            }

            uint16_t Entry::InstanceId() const noexcept
            {
                return GBInstanceId;
            }

            uint8_t Entry::MajorVersion() const noexcept
            {
                return GBMajorVersion;
            }

            uint32_t Entry::TTL() const noexcept
            {
                return GBTTL;
            }

            const std::vector<option::Option *> &Entry::FirstOptions() const noexcept
            {
                return GBFirstOptions;
            }

            void Entry::AddFirstOption(option::Option *firstOption)
            {
                
                     GBFirstOptions.push_back(firstOption);
                
            
            }

            const std::vector<option::Option *> &Entry::SecondOptions() const noexcept
            {
                return GBSecondOptions;
            }

            void Entry::AddSecondOption(option::Option *secondOption)
            {
                
                
                    GBSecondOptions.push_back(secondOption);
                
                
            }

            std::vector<uint8_t> Entry::BasePayload(uint8_t &optionIndex) const
            {
                std::vector<uint8_t> _result;

                uint8_t _type = static_cast<uint8_t>(Type());
                _result.push_back(_type);

                _result.push_back(optionIndex);
                uint8_t _firstOptionsSize = FirstOptions().size();
                optionIndex += _firstOptionsSize;

                _result.push_back(optionIndex);
                uint8_t _secondOptionsSize = SecondOptions().size();
                optionIndex += _secondOptionsSize;

                const uint8_t OptionSizeBitLength = 4;
                _firstOptionsSize <<= OptionSizeBitLength;
                _firstOptionsSize |= _secondOptionsSize;
                _result.push_back(_firstOptionsSize);

                helper::Inject(_result, ServiceId());
                helper::Inject(_result, InstanceId());

                const uint8_t TTLSizeBitLength = 24;
                uint32_t _majorVersion = MajorVersion();
                _majorVersion <<= TTLSizeBitLength;
                _majorVersion |= TTL();
                helper::Inject(_result, _majorVersion);

                return _result;
            }
        }
    }
}
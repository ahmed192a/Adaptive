#include "entry.h"

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

            bool Entry::ValidateOption(const option::Option *option) const noexcept
            {
                bool _result=true;

                switch (option->Type())
                {
                case option::OptionType::Configuration:
                {
                    bool _containsConfiguration =
                        !ContainsOption(option::OptionType::Configuration);

                    // Each entry can only have at maximum one configuration option.
                    _result = _containsConfiguration;

                    break;
                }
                case option::OptionType::LoadBalancing:
                {
                    bool _containsLoadBalancing =
                        !ContainsOption(option::OptionType::LoadBalancing);

                    // Each entry can only have at maximum one load balancing option.
                    _result = _containsLoadBalancing;

                    break;
                }
                // case option::OptionType::IPv4SdEndpoint:
                // case option::OptionType::IPv6SdEndpoint:
                // {
                //     // Service discovery endpoints are not allowed in entries.
                //     _result = false;

                //     break;
                // }
                default:
                {
                    // Other options cannot be validated in the base entry class.
                    _result = true;

                    break;
                }
                }

                return _result;
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
                bool _valid = ValidateOption(firstOption);

                if (_valid)
                {
                    GBFirstOptions.push_back(firstOption);
                }
                else
                {
                    throw std::invalid_argument("The option cannot be added.");
                }
            }

            const std::vector<option::Option *> &Entry::SecondOptions() const noexcept
            {
                return GBSecondOptions;
            }

            void Entry::AddSecondOption(option::Option *secondOption)
            {
                bool _valid = ValidateOption(secondOption);

                if (_valid)
                {
                    GBSecondOptions.push_back(secondOption);
                }
                else
                {
                    throw std::invalid_argument("The option cannot be added.");
                }
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
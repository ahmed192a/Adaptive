/**
 * @file SomeipSDMessage.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/com/SOMEIP/SomeipSDMessage.hpp"
#include "ara/com/SOMEIP/option/option_desrializer.hpp"
#include "ara/com/SOMEIP/entry/entry_desrializer.hpp"
#include <iostream>
using namespace std;
namespace ara
{
    namespace com
    {
        namespace SOMEIP_MESSAGE
        {
            namespace sd
            {
                SomeIpSDMessage::SomeIpSDMessage() : 
                                                    Message(
                                                         MID,
                                                         RID,
                                                         ProtocolVersion,
                                                         InterfaceVersion,
                                                         Messagetype),
                                                         Rebooted{true}
                {
                }

                uint32_t SomeIpSDMessage::getEntriesLength() const noexcept
                {
                    const uint32_t EntrySize = 16;
                    uint32_t noOFEntries = entries.size();
                    uint32_t result = noOFEntries*EntrySize;

                    return result;
                }

                uint32_t SomeIpSDMessage::getOptionsLength() const noexcept
                {
                    const uint32_t OptionLengthFieldSize = 3;
                    uint32_t result = 0;

                    for (auto entry : entries)
                    {
                        for (auto firstOption : entry->FirstOptions())
                        {
                            result += OptionLengthFieldSize + firstOption->Length();
                        }

                        for (auto secondOption : entry->SecondOptions())
                        {
                            result += OptionLengthFieldSize + secondOption->Length();
                        }
                    }

                    return result;
                }

                const std::vector<entry::Entry *> &SomeIpSDMessage::Entries() const noexcept
                {
                    return entries;
                }

                void SomeIpSDMessage::AddEntry(entry::Entry *entry)
                {
                    entries.push_back(entry);
                }

                uint32_t SomeIpSDMessage::Length()  noexcept
                {
                    const uint32_t LengthFieldSize = 4;
                    // Request ID + Versions + Message Type + Return Code +Message ID
                    const uint32_t GeneralHeaderSize = 12;
                    // Flags + Reserved
                    const uint32_t SdHeaderSize = 4;

                    uint32_t entriesLength = LengthFieldSize + getEntriesLength();
                    uint32_t optionsLength = LengthFieldSize + getOptionsLength();
                    uint32_t result =
                        GeneralHeaderSize +
                        LengthFieldSize +
                        SdHeaderSize +
                        entriesLength +
                        optionsLength;

                    return result;
                }

                void SomeIpSDMessage::SetSessionId(uint16_t sessionId)
                {
                    if (sessionId == 0)
                    {
                        throw std::invalid_argument(
                            "Session ID cannot be zero for the SD message.");
                    }

                    Message::SetSessionId(sessionId);
                }

                bool SomeIpSDMessage::IncrementSessionId() noexcept
                {
                    bool wrapped = Message::IncrementSessionId();
                    // If the message is rebooted, check for wrapping
                    Rebooted &= !wrapped;

                    return wrapped;
                }

                std::vector<uint8_t> SomeIpSDMessage::Payload() 
                {
                    // General SOME/IP header payload insertion
                    std::vector<uint8_t> _result = Message::Payload();

                    if (Rebooted)
                    {
                        // Both Unicast Support and Explicit Initial Data Control flags are on.
                        const uint32_t RebootedFlag = 0xe0000000;
                        helper::Inject(_result, RebootedFlag);
                    }
                    else
                    {
                        // Both Unicast Support and Explicit Initial Data Control flags are on.
                        const uint32_t NotRebootedFlag = 0x60000000;
                        helper::Inject(_result, NotRebootedFlag);
                    }

                    uint8_t lastOptionIndex = 0;
                    std::vector<uint8_t> entriesPayload;
                    std::vector<uint8_t> optionsPayload;
                    for (auto entry : entries)
                    {
                        auto entryPayload = entry->Payload(lastOptionIndex);
                        helper::Concat(
                            entriesPayload, std::move(entryPayload));

                        for (auto firstOption : entry->FirstOptions())
                        {
                            auto firstOptionPayload = firstOption->Payload();
                            helper::Concat(
                                optionsPayload, std::move(firstOptionPayload));
                            ++lastOptionIndex;
                        }

                        for (auto secondOption : entry->SecondOptions())
                        {
                            auto secondOptionPayload = secondOption->Payload();
                            helper::Concat(
                                optionsPayload, std::move(secondOptionPayload));
                            ++lastOptionIndex;
                        }
                    }

                    // Entries length and payloads insertion
                    uint32_t entriesLength = getEntriesLength();
                    helper::Inject(_result, entriesLength);
                    helper::Concat(_result, std::move(entriesPayload));

                    // Options length and payloads insertion
                    uint32_t optionsLength = getOptionsLength();
                    helper::Inject(_result, optionsLength);
                    helper::Concat(_result, std::move(optionsPayload));

                    return _result;
                }

                void SomeIpSDMessage::Deserialize(const std::vector<uint8_t> &payload)
                {
                    uint32_t offset = 16;
                    // Flags extraction
                    const uint32_t RebootedFlag = 0xe0000000;
                    const uint32_t NotRebootedFlag = 0x60000000;
                    uint32_t flags = helper::Extract<uint32_t>(payload, offset);
                    Rebooted = (flags & RebootedFlag) == RebootedFlag;
                    offset += 4;
                    
                    std::cout<<"Entries payload extraction\n";
                    // Entries payload extraction
                    uint32_t entriesLength = payload[offset]<<24 | payload[offset+1]<<16 | payload[offset+2]<<8 | payload[offset+3];
                    std::cout<<"entriesLength "<<entriesLength<<std::endl;
                    offset += 4;
                    uint32_t entriesPayloadOffset = offset;
                    std::cout<<"entriesPayloadOffset "<<entriesPayloadOffset<<std::endl;
                    // uint32_t entriesPayloadLength = entriesLength - 4;
                    std::vector<uint8_t> entriesPayload =
                        helper::Extracts(payload, entriesPayloadOffset, entriesLength);
                    offset += entriesLength;

                    std::cout<<"Options payload extraction\n";
                    // Options payload extraction
                    uint32_t optionsLength = payload[offset]<<24 | payload[offset+1]<<16 | payload[offset+2]<<8 | payload[offset+3];
                    std::cout<<"optionsLength "<<optionsLength<<std::endl;
                    offset += 4;
                    uint32_t optionsPayloadOffset = offset;
                    std::cout<<"optionsPayloadOffset "<<optionsPayloadOffset<<std::endl;
                    // uint32_t optionsPayloadLength = optionsLength - 4;
                    std::vector<uint8_t> optionsPayload =
                        helper::Extracts(payload, optionsPayloadOffset, optionsLength);
                    offset += optionsLength;
                    cout<<"offset "<<optionsPayload.size()<<endl;

                    std::cout<<"Entries extraction\n";
                    // Entries extraction
                    uint32_t entriesOffset = 0;
                    std::vector<std::pair<uint8_t, uint8_t>> firstop;
                    std::vector<std::pair<uint8_t, uint8_t>> secondop;
                    while (entriesOffset < entriesLength)
                    {
                        std::pair<uint8_t, uint32_t> firstOption ;
                        std::pair<uint32_t, uint32_t> secondOption ;
                        firstOption.first = entriesPayload[entriesOffset+1];
                        firstOption.second = (entriesPayload[entriesOffset+3] >> 4) & 0x0f;
                        secondOption.first = entriesPayload[entriesOffset+2];
                        secondOption.second = entriesPayload[entriesOffset+3] & 0x0f;

                        firstop.push_back(firstOption);
                        secondop.push_back(secondOption);
                        auto entry = entry::Entry_Deserializer::Deserialize(entriesPayload, entriesOffset);
                        entries.push_back(entry);
                        entriesOffset += 16;
                    }
                    std::cout<<"Options extraction\n";
                    // Options extraction
                    std::vector<ara::com::option::Option *> options;
                    uint32_t optionsOffset = 0;
                    while (optionsOffset < optionsLength)
                    {
                        auto option = option::OptionDeserializer::Deserialize(optionsPayload, optionsOffset);
                        options.push_back(option);
                        optionsOffset += option->Length() + 3;
                    }
                    std::cout<<"Option ins extraction\n";
                    // Options insertion
                    uint32_t entryIndex = 0;
                    for (auto entry : entries)
                    {
                        uint8_t firstOptionIndex = firstop[entryIndex].first;
                        uint8_t secondOptionIndex = secondop[entryIndex].first;
                        uint8_t firstOptionLength = firstop[entryIndex].second;
                        uint8_t secondOptionLength = secondop[entryIndex].second;

                        for (uint8_t optionIndex = firstOptionIndex; optionIndex < firstOptionLength; ++optionIndex)
                        {
                            auto option = options[optionIndex];
                            entry->AddFirstOption(option);
                        }

                        for (uint8_t optionIndex = secondOptionIndex; optionIndex < secondOptionLength; ++optionIndex)
                        {
                            auto option = options[optionIndex];
                            entry->AddSecondOption(option);
                        }
                        entryIndex++;
                    }

                }

            }
        }
    }
}
#include "SomeipSDMessage.h"
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
                SomeIpSDMessage::SomeIpSDMessage() : Rebooted{true},
                                                    Message(
                                                         MID,
                                                         RID,
                                                         ProtocolVersion,
                                                         InterfaceVersion,
                                                         Messagetype)
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

                uint32_t SomeIpSDMessage::Length() const noexcept
                {
                    const uint32_t LengthFieldSize = 4;
                    // Request ID + Versions + Message Type + Return Code
                    const uint32_t GeneralHeaderSize = 8;
                    // Flags + Reserved
                    const uint32_t SdHeaderSize = 4;

                    uint32_t entriesLength = LengthFieldSize + getEntriesLength();
                    uint32_t optionsLength = LengthFieldSize + getOptionsLength();
                    uint32_t result =
                        GeneralHeaderSize +
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
            }
        }
    }
}
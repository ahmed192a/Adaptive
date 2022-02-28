#ifndef SOMEIPSDMESSAGE_H
#define SOMEIPSDMESSAGE_H

#include <stdint.h>
#include <vector>
#include <utility>
#include "../someip_message.h"
#include "../../entry/entry.h"

namespace ara
{
    namespace com
    {
        namespace someip
        {
            namespace sd
            {
               
                class SomeIpSDMessage : public Message
                {
                private:
                    static const uint32_t MessageId = 0xffff8100;
                    static const uint16_t ClientId = 0x0000;
                    static const uint8_t ProtocolVersion = 0x01;
                    static const uint8_t InterfaceVersion = 0x01;
                    static const MessageType MessageType = MessageType:NOTIFICATION;

                    bool Rebooted;
                    std::vector<entry::Entry *> Entries;

                    uint32_t getEntryLength() const noexcept;
                    uint32_t getOptionLength() const noexcept;

                public:
                    SomeIpSdMessage();

                    const std::vector<entry::Entry *> &Entries() const noexcept;

                    
                    void AddEntry(entry::Entry *entry);

                    uint32_t Length() const noexcept override;

                    void SetSessionId(uint16_t sessionId) override;

                    bool IncrementSessionId() noexcept override;

                    std::vector<uint8_t> Payload() const override;
                };
            }
        }
    }
}
#endif
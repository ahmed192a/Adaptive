#ifndef SOMEIPSDMESSAGE_H
#define SOMEIPSDMESSAGE_H

#include <stdint.h>
#include <vector>
#include <utility>
#include "Message.h"
#include "entry/entry.h"

namespace ara
{
    namespace com
    {
        namespace SOMEIP_MESSAGE
        {
            namespace sd
            {
               
                class SomeIpSDMessage : public Message
                {
                private:
                	static constexpr struct Request_ID RID={.client_id =0, .session_id=1 };
					static constexpr struct Message_ID MID={0xffff,0x8100};
                    static const uint8_t ProtocolVersion = 0x01;
                    static const uint8_t InterfaceVersion = 0x01;
                    static const MessageType Messagetype = MessageType::NOTIFICATION;

                    bool Rebooted =false;
                    std::vector<entry::Entry *> entries;

                    uint32_t getEntriesLength() const noexcept;
                    uint32_t getOptionsLength() const noexcept;

                public:
                    SomeIpSDMessage();

                    const std::vector<entry::Entry *> &Entries() const noexcept;

                    
                    void AddEntry(entry::Entry *entry);

                    uint32_t Length() const noexcept override;

                    void SetSessionId(uint16_t sessionId) override;

                    bool IncrementSessionId() noexcept override;

                    std::vector<uint8_t> Payload()  override;
                };
            }
        }
    }
}
#endif
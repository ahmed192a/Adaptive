/**
 * @file SomeipSDMessage.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SOMEIPSDMESSAGE_H
#define SOMEIPSDMESSAGE_H

#include <stdint.h>
#include <vector>
#include <memory>
#include <utility>
#include "ara/com/SOMEIP/Message.h"
#include "ara/com/SOMEIP/entry/entry.h"
#include "ara/com/SOMEIP/entry/service_entry.h"
#include "ara/com/SOMEIP/option/ipv4_endpoint_option.h"

namespace ara
{
    namespace com
    {
        namespace SOMEIP_MESSAGE
        {
            namespace sd
            {
                /**
                 * @brief Class for SOME/IP SD Message
                 * @see Message classs in Message.hpp
                 *
                 */
                class SomeIpSDMessage : public Message
                {
                private:
                	static constexpr struct Request_ID RID={.client_id =0, .session_id=1 };     //!< Request ID for SD messages (client_id, session_id) = (0, 1)
					static constexpr struct Message_ID MID={0xffff,0x8100};                     //!< Message ID for SD messages (service_id, instance_id) = (0xffff, 0x8100)
                    static const uint8_t ProtocolVersion = 0x01;                                //!< Protocol version of SD messages = 0x01
                    static const uint8_t InterfaceVersion = 0x01;                               //!< Interface version of SD messages = 0x01
                    static const MessageType Messagetype = MessageType::NOTIFICATION;           //!< Message type of SD messages = NOTIFICATION

                    bool Rebooted =false;                                                       //!< Flag to indicate if the device has been rebooted
                    std::vector<entry::Entry *> entries;                                        //!< Vector of entries to be sent in the SD message
                    /**
                     * @brief Get the Entries Length object
                     * 
                     * @return uint32_t   Length of the entries in the SD message
                     *
                     */
                    uint32_t getEntriesLength() const noexcept;
                    /**
                     * @brief Get the Options Length object
                     * 
                     * @return uint32_t  Length of the options in the SD message
                     */
                    uint32_t getOptionsLength() const noexcept;

                public:
                    /**
                     * @brief Construct a new Some Ip SD Message object
                     * 
                     */
                    SomeIpSDMessage();

                    /**
                     * @brief Entries Method that returns vector of entries in the SD message
                     * 
                     * @return const std::vector<entry::Entry *>& 
                     */
                    const std::vector<entry::Entry *> &Entries() const noexcept;
                    
                    /**
                     * @brief AddEntry Method that adds an entry to the SD message
                     * 
                     * @param entry  pointer to the Entry to be added to the SD message
                     */
                    void AddEntry(entry::Entry *entry);

                    /**
                     * @brief Length Method that returns the length of the SD message
                     * 
                     * @return uint32_t 
                     */
                    uint32_t Length()  noexcept override;

                    /**
                     * @brief Set the Session Id object
                     * 
                     * @param sessionId 
                     */
                    void SetSessionId(uint16_t sessionId) override;

                    /**
                     * @brief IncrementSessionId Method that increments the session id of the SD message
                     * 
                     * @return true 
                     * @return false 
                     */
                    bool IncrementSessionId() noexcept override;

                    /**
                     * @brief Serialize Method that serializes the SD message
                     * 
                     * @return std::vector<uint8_t>     payload of the serialized SD message
                     */
                    std::vector<uint8_t> Serializer()  override;

                    /**
                     * @brief Deserialize Method that deserializes vector of bytes into the SD message
                     * 
                     * @param payload   vector of bytes to be deserialized into the SD message
                     */
                    void Deserialize(const std::vector<uint8_t> &payload);

                };
            }
        }
    }
}
#endif

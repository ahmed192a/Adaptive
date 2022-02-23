#include"Message.h"

namespace ara
{
    namespace com
    {
        namespace entry
        {
            Message::Message(struct Message_ID mID,uint32_t length,struct Request_ID rID,uint8_t protocol_version,uint8_t interface_version,MessageType Mtype,ReturnCode Rcode)noexcept:Header(mID,length,rID,protocol_version,interface_version,Mtype,Rcode)noexcept:
            GBMessageID{mID},GBlength{length},GBRequest_ID{rID},GBProtocol_Version{protocol_version},GBinterface_version{interface_version},GBMessageType{MType},GBReturnCode{Rcodr}
            {}
            Message::Message(struct Message_ID mID,uint32_t length,struct Request_ID rID,uint8_t protocol_version,uint8_t interface_version,MessageType Mtype,ReturnCode Rcode)noexcept
            :Message(struct Message_ID mID,uint32_t length,struct Request_ID rID,uint8_t protocol_version,uint8_t interface_version,MessageType Mtype,ReturnCode Rcode::E_OK)
            {
                 if ((MessageType != Message::REQUEST) &&
                    (MessageType != Message::NOTIFICATION))
                {
                    // E2E is not supported yet.
                    throw std::invalid_argument("Invalid message type.");
                }
            }
            Message::Message(struct Message_ID mID,uint32_t length,struct Request_ID rID,uint8_t protocol_version,uint8_t interface_version,MessageType Mtype,ReturnCode Rcode)noexcept
            :Message(struct Message_ID mID,uint32_t length,struct Request_ID rID,uint8_t protocol_version,uint8_t interface_version,MessageType Mtype,ReturnCode Rcode)
            {
                 if ((MessageType != Message::REQUEST) ||
                    (MessageType != Message::NOTIFICATION))
                {
                    // E2E is not supported yet.
                    throw std::invalid_argument("Invalid message type.");
                }
                else if ((MessageType != Message::ERROR) &&
                         (ReturnCode == ReturnCode::E_OK))
                {
                    // Error message cannot have OK return code.
                    throw std::invalid_argument("Invalid return code.");
                }

            }
              uint32_t Message::MessageId() const noexcept
            {
                return GBMessageType;
            }

            uint16_t Message::ClientId() const noexcept
            {
                return GBRequest_ID.client_id;
            }

            uint16_t Message::SessionId() const noexcept
            {
                return GBRequest_ID.Session_id;
            }
            
            void Message::SetSessionId(uint16_t sessionId)
            {
                 GBRequest_ID.Session_id = sessionId;
            }

            bool Message::IncrementSessionId() noexcept
            {
                const uint8_t SessionIdMin = 1;
                constexpr uint8_t SessionIdMax = std::numeric_limits<uint8_t>::max();

                if ( GBRequest_ID.Session_id == SessionIdMax)
                {
                    GBRequest_ID.Session_id= SessionIdMin;
                    return true;
                }
                else
                {
                    GBRequest_ID.Session_id++;
                    return false;
                }
            }
            
            uint8_t Message::ProtocolVersion() const noexcept
            {
                return GBprotocolversion;
            }

            uint8_t Message::InterfaceVersion() const noexcept
            {
                return GBinterface_version;
            }

            Message Message::MessageType() const noexcept
            {
                return GBMessageType;
            }

            ReturnCode Message::ReturnCode() const noexcept
            {
                return GBReturnCode;
            }

            std::vector<uint8_t> Message::Payload() const
            {
            }

        }
    }
}
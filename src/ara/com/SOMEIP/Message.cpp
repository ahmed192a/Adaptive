#include"Message.h"

namespace ara
{
    namespace com
    {
        namespace SOMEIP_MESSAGE
        {
            Message::Message(
                struct Message_ID mID,
                struct Request_ID rID,
                uint8_t protocol_version,
                uint8_t interface_version,
                enum MessageType Mtype,
                enum ReturnCode Rcode)noexcept:
            Header(mID,rID,protocol_version,interface_version,Mtype,Rcode)
            {}
            Message::Message(
                struct Message_ID mID,
                struct Request_ID rID,
                uint8_t protocol_version,
                uint8_t interface_version,
                enum MessageType Mtype)noexcept:
            Message( 
                mID, 
                rID, 
                protocol_version, 
                interface_version, 
                Mtype, 
                ReturnCode::E_OK)
            {
                 if ((Mtype != MessageType::REQUEST) &&
                    (Mtype != MessageType::NOTIFICATION))
                {
                    // E2E is not supported yet.
                    throw std::invalid_argument("Invalid message type.");
                }
            }

            Message::Message(
                struct Request_ID rID,
                struct Message_ID mID,
                uint8_t protocol_version,
                uint8_t interface_version,
                enum MessageType Mtype,
                enum ReturnCode Rcode)noexcept:
            Message( mID, rID, protocol_version, interface_version, Mtype, Rcode)
            {
                 if ((Mtype != MessageType::REQUEST) ||
                    (Mtype != MessageType::NOTIFICATION))
                {
                    // E2E is not supported yet.
                    throw std::invalid_argument("Invalid message type.");
                }
                else if ((Mtype != MessageType::ERROR) &&
                         (Rcode == ReturnCode::E_OK))
                {
                    // Error message cannot have OK return code.
                    throw std::invalid_argument("Invalid return code.");
                }

            }
            struct Message_ID Message::MessageId() const noexcept
            {
                return GBMessageID;
            }

            uint16_t Message::ClientId() const noexcept
            {
                return GBRequest_ID.client_id;
            }

            uint16_t Message::SessionId() const noexcept
            {
                return GBRequest_ID.session_id;
            }
            
            void Message::SetSessionId(uint16_t sessionId)
            {
                GBRequest_ID.session_id = sessionId;
            }

            bool Message::IncrementSessionId() noexcept
            {
                const uint8_t SessionIdMin = 1;
                constexpr uint8_t SessionIdMax = std::numeric_limits<uint8_t>::max();

                if ( GBRequest_ID.session_id == SessionIdMax)
                {
                    GBRequest_ID.session_id= SessionIdMin;
                    return true;
                }
                else
                {
                    GBRequest_ID.session_id++;
                    return false;
                }
            }
            
            uint8_t Message::ProtocolVersion() const noexcept
            {
                return GBProtocol_Version;
            }

            uint8_t Message::InterfaceVersion() const noexcept
            {
                return GBinterface_version;
            }

            MessageType Message::Messagetype() const noexcept
            {
                return GBMessageType;
            }

            ReturnCode Message::Returncode() const noexcept
            {
                return GBReturnCode;
            }

            std::vector<uint8_t> Message::Payload() 
            {
            }

        }
    }
}

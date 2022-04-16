/**
 * @file Message.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include"ara/com/SOMEIP/Message.hpp"

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
                /*
                 if ((Mtype != MessageType::REQUEST) &&
                    (Mtype != MessageType::NOTIFICATION))
                {
                    // E2E is not supported yet.
                    throw std::invalid_argument("Invalid message type.");
                }
                */
            }

            Message::Message(
                Request_ID rID,
                Message_ID mID,
                uint8_t protocol_version,
                uint8_t interface_version,
                ReturnCode Rcode,
                MessageType Mtype
                )noexcept:
            Message( mID, rID, protocol_version, interface_version, Mtype, Rcode)
            {
                //  if ((Mtype != MessageType::REQUEST) ||
                //     (Mtype != MessageType::NOTIFICATION))
                // {
                //     // E2E is not supported yet.
                //     throw std::invalid_argument("Invalid message type.");
                // }
                // else if ((Mtype != MessageType::ERROR) &&
                //          (Rcode == ReturnCode::E_OK))
                // {
                //     // Error message cannot have OK return code.
                //     throw std::invalid_argument("Invalid return code.");
                // }

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
                std::vector<uint8_t> result;
                Message_ID mid = MessageId();

                helper::Inject(result, mid.serivce_id);
                helper::Inject(result, mid.method_id);
                helper::Inject(result, Length());
                helper::Inject(result, ClientId());
                helper::Inject(result, SessionId());
                result.push_back(ProtocolVersion());
                result.push_back(InterfaceVersion());

                uint8_t messageType = static_cast<uint8_t>(MessageType());
                result.push_back(messageType);

                uint8_t returnCode = static_cast<uint8_t>(ReturnCode());
                result.push_back(returnCode);
                // concatenate result and payload and put them in the result
                result.insert(result.end(), payload.begin(), payload.end());

                return result;
            }
            void Message::SetPayload(std::vector<uint8_t>&data){
                payload = data;
                GBlength+=payload.size();
            }

            Message Message::Deserialize(const std::vector<uint8_t> &msg)
            {
                // if (payload.size() < Header::HeaderSize)
                // {
                //     throw std::invalid_argument("Invalid payload size.");
                // }
                 std::cout<<"fsdfsdfsdf\n";
                uint32_t offset = 0;
                Message_ID _mid;
                _mid.serivce_id = msg[offset]<<8 | msg[offset+1];
                _mid.method_id = msg[offset+2]<<8 | msg[offset+3];
                offset += 4;
                uint32_t length ;
                length = msg[offset] <<24 | msg[offset+1] << 16 | msg[offset+2] << 8 | msg[offset+3];
                offset += 4;
                Request_ID _rid;
                _rid.client_id = msg[offset]<<8 | msg[offset+1];
                _rid.session_id = msg[offset+2]<<8 | msg[offset+3];
                offset += 4;

                uint8_t GBProtocol_Version = msg[offset];
                uint8_t GBinterface_version = msg[offset+1];
                MessageType GBMessageType = static_cast<MessageType>(msg[offset+2]);
                ReturnCode GBReturnCode = static_cast<ReturnCode>(msg[offset+3]);
                offset += 4;

                std::cout<<"fsdfsdfsdf\n";
                Message m (_mid, _rid, GBProtocol_Version, GBinterface_version, GBMessageType, GBReturnCode);
                if(length > Header::HeaderSize){
                    cout<<"offset "<<offset<<" length "<<length<<"\n";
                    std::vector<uint8_t> pay = {msg.begin()+offset, msg.begin()+length};
                    std::cout<<"fsdfsdfsdf\n";
                    m.SetPayload(pay);
                }
                return m;
            }


            Message& Message::operator=(Message &msg){
                GBMessageID = msg.MessageId();
                GBlength = msg.Length();
                GBRequest_ID.client_id = msg.ClientId();
                GBRequest_ID.session_id = msg.SessionId();
                GBProtocol_Version = msg.ProtocolVersion();
                GBinterface_version = msg.InterfaceVersion();
                GBMessageType = msg.Messagetype();
                GBReturnCode = msg.Returncode();
                payload = msg.Payload();
                return *this;
            }

            std::vector<uint8_t> Message::getload(){
                return payload;
            }

        }
    }
}

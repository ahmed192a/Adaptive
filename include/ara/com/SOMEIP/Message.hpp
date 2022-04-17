/**
 * @file Message.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdint.h>
#include <vector>
#include <stdexcept>
#include <limits>
#include "ara/com/SOMEIP/helper/ipv4_address.hpp"
#include "ara/com/SOMEIP/helper/payload_helper.hpp"
#include "ara/com/SOMEIP/helper/ttl_timer.hpp"
#include <iostream>
using namespace std;
namespace ara
{
	namespace com
	{
		namespace SOMEIP_MESSAGE
		{
			enum class MessageType : uint8_t
			{
				REQUEST = 0x00,				 ///!< A request expecting a response (even void)
				REQUEST_NO_RETURN = 0x01,	 ///!< A fire&forget request
				NOTIFICATION = 0x02,		 ///!<A request of a notification/event callback expecting no response
				RESPONSE = 0x80,			 ///!<The response message
				ERROR = 0x81,				 ///!<The response containing an error
				TP_REQUEST = 0x20,			 ///!<A TP request expecting a response (even void)
				TP_REQUEST_NO_RETURN = 0x21, ///!<A TP fire & forget request
				TP_NOTIFICATION = 0x22,		 ///!<A TP request of a notification/event callback expecting no response
				TP_RESPONSE = 0x23,			 ///!<The TP response message
				TP_ERROR = 0x24				 ///!<The TP response containing an error
			};
			enum class ReturnCode : uint8_t
			{
				E_OK,					   ///!<No error occurred
				E_NOT_OK,				   ///!<An unspecified error occurred
				E_UNKNOWN_SERVICE,		   ///!<The requested Service ID is unknown
				E_UNKNOWN_METHOD,		   ///!<The requested Method ID is unknown. Service ID is known.
				E_NOT_READY,			   ///!<Service ID and Method ID are known. Application not running
				E_NOT_REACHABLE,		   ///!<System running the service is not reachable (proxy_skeleton error code only).
				E_TIMEOUT,				   ///!<A timeout occurred (proxy_skeleton error code only).
				E_WRONG_PROTOCOL_VERSION,  ///!<Version of SOME/IP protocol not supported
				E_WRONG_INTERFACE_VERSION, ///!<Interface version mismatch
				E_MALFORMED_MESSAGE,	   ///!<Deserialization error, so that payload cannot be deserialized.
				E_WRONG_MESSAGE_TYPE,	   //!< An unexpected message type was received (e.g. REQUEST_NO_RETURN for a method defined as REQUEST).
				E_E2E_REPEATED,			   ///!<Repeated E2E calculation error
				E_E2E_WRONG_SEQUENCE,	   ///!<Wrong E2E sequence error
				E_E2E,					   ///!<Not further specified E2E error
				E_E2E_NOT_AVAILABLE,	   ///!<E2E not available
				E_E2E_NO_NEW_DATA		   ///!<No new data for E2E calculation present
			};
			struct Message_ID
			{
				uint16_t serivce_id;
				uint16_t method_id = 0;
			};
			struct Request_ID
			{
				// Request_ID(uint16_t x, uint16_t y){
				// 	client_id = x;
				// 	session_id = y;
				// }
				uint16_t client_id;
				uint16_t session_id=1;
			};
			class Header
			{
			public:
				static const uint32_t HeaderSize = 16;
				struct Message_ID GBMessageID;
				uint32_t GBlength;
				struct Request_ID GBRequest_ID;
				uint8_t GBProtocol_Version;
				uint8_t GBinterface_version;
				MessageType GBMessageType;
				ReturnCode GBReturnCode;
				Header(struct Message_ID mID, struct Request_ID rID, uint8_t protocol_version, uint8_t interface_version,MessageType Mtype,ReturnCode Rcode)
				{
					GBMessageID.serivce_id = mID.serivce_id;
					GBMessageID.method_id = mID.method_id;
					GBlength = HeaderSize;
					GBRequest_ID.client_id = rID.client_id;
					GBRequest_ID.session_id = rID.session_id;
					GBProtocol_Version = protocol_version;
					GBinterface_version = interface_version;
					GBMessageType=Mtype;
					GBReturnCode=Rcode;
				}
			};

			class Message : public Header
			{
			private:
				std::vector<uint8_t> payload;

				
                Message(
					struct Message_ID mID,
					struct Request_ID rID,
					uint8_t protocol_version,
					uint8_t interface_version,
					MessageType Mtype,
					ReturnCode Rcode) noexcept;  
                    
            // protected:	
			public:
            Message(
					Message_ID mID,
					Request_ID rID,
					uint8_t protocol_version,
					uint8_t interface_version,
					MessageType Mtype
					) noexcept;
            Message(
					Request_ID rID,
					Message_ID mID,
					uint8_t protocol_version,
					uint8_t interface_version,
					ReturnCode Rcode,
					MessageType Mtype) noexcept;  



                virtual ~Message() noexcept = default;

                /// @brief Get message ID
                /// @returns Message ID consisting service and method/event ID
                struct Message_ID MessageId() const noexcept;

                /// @brief Get message payload
                /// @returns Byte array
                virtual std::vector<uint8_t> Serializer() ;

                /// @brief Get message length
                /// @returns Message length including the payload length
                virtual uint32_t Length() noexcept {
					return GBlength;
				}

                /// @brief Get client ID
                /// @returns Client ID including ID prefix
                uint16_t ClientId() const noexcept;

                /// @brief Get session ID
                /// @returns Active/non-active session ID
                uint16_t SessionId() const noexcept;

                /// @brief Set a new session ID
                /// @param sessionId New session ID
                virtual void SetSessionId(uint16_t sessionId);

                /// @brief Increment the session ID by one
                /// @returns True if the session ID is wrappered; otherwise false
                /// @note In the case of wrapping, session ID will start from 1
                virtual bool IncrementSessionId() noexcept;

                /// @brief Get protocol version
                /// @returns SOME/IP protocol header version
                uint8_t ProtocolVersion() const noexcept;

                /// @brief Get interface version
                /// @returns Service interface version
                uint8_t InterfaceVersion() const noexcept;

                /// @brief Get message type
                /// @returns SOME/IP message type
                MessageType Messagetype() const noexcept;

                /// @brief Get return code
                /// @returns SOME/IP message return code
                ReturnCode Returncode() const noexcept;



				/// @brief Set message payload
				/// @param data Byte array
				void SetPayload(std::vector<uint8_t> &data);

				/// @brief Deserialize message payload
				/// @param msg Byte array
				static Message Deserialize(const std::vector<uint8_t> &msg);


				// operator =(Message &msg);
				Message& operator=(Message &msg);

				std::vector<uint8_t> getload();
				
			};

		}
	}
}

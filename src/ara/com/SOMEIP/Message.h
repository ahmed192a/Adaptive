/**
 * @file Message.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_COM_SOMEIP_MESSAGE_HPP
#define ARA_COM_SOMEIP_MESSAGE_HPP
#include <stdint.h>
#include <vector>
#include <stdexcept>
#include <limits>
#include "ara/com/SOMEIP/helper/ipv4_address.h"
#include "ara/com/SOMEIP/helper/payload_helper.h"
#include "ara/com/SOMEIP/helper/ttl_timer.h"
#include <iostream>
using namespace std;
namespace ara
{
	namespace com
	{
		namespace SOMEIP_MESSAGE
		{
			/**
			 * @enum MessageType
			 * 
			 * @brief MessageType enumaration is used to identify the type of the message in SOME IP
			 * 
			 */
			enum class MessageType : uint8_t
			{
				REQUEST = 0x00,				 /**< A request expecting a response (even void)	*/
				REQUEST_NO_RETURN = 0x01,	 /**< A fire&forget request	*/
				NOTIFICATION = 0x02,		 /**< A request of a notification/event callback expecting no response	*/
				RESPONSE = 0x80,			 /**< The response message	*/			
				ERROR = 0x81,				 /**< The response containing an error	*/			
				TP_REQUEST = 0x20,			 /**< A TP request expecting a response (even void)	*/
				TP_REQUEST_NO_RETURN = 0x21, /**< A TP fire & forget request	*/
				TP_NOTIFICATION = 0x22,		 /**< A TP request of a notification/event callback expecting no response	*/
				TP_RESPONSE = 0x23,			 /**< The TP response message	*/			
				TP_ERROR = 0x24				 /**< The TP response containing an error	*/
			};
			/**
			 * @enum ReturnCode
			 * @brief ReturnCode enumaration is used to identify the return code of the response message SOME IP
			 * 
			 */
			enum class ReturnCode : uint8_t
			{
				E_OK,					   /**<No error occurred	*/
				E_NOT_OK,				   /**<An unspecified error occurred	*/
				E_UNKNOWN_SERVICE,		   /**<The requested Service ID is unknown	*/
				E_UNKNOWN_METHOD,		   /**<The requested Method ID is unknown. Service ID is known.	*/
				E_NOT_READY,			   /**<Service ID and Method ID are known. Application not running	*/					
				E_NOT_REACHABLE,		   /**<System running the service is not reachable (proxy_skeleton error code only).	*/
				E_TIMEOUT,				   /**<A timeout occurred (proxy_skeleton error code only).	*/
				E_WRONG_PROTOCOL_VERSION,  /**<Version of SOME/IP protocol not supported	*/
				E_WRONG_INTERFACE_VERSION, /**<Interface version mismatch	*/
				E_MALFORMED_MESSAGE,	   /**<Deserialization error, so that payload cannot be deserialized.	*/
				E_WRONG_MESSAGE_TYPE,	   /**< An unexpected message type was received (e.g. REQUEST_NO_RETURN for a method defined as REQUEST).	*/
				E_E2E_REPEATED,			   /**<Repeated E2E calculation error	*/
				E_E2E_WRONG_SEQUENCE,	   /**<Wrong E2E sequence error	*/
				E_E2E,					   /**<Not further specified E2E error	*/
				E_E2E_NOT_AVAILABLE,	   /**<E2E not available	*/
				E_E2E_NO_NEW_DATA		   /**<No new data for E2E calculation present */
			};
			/**
			 * @struct Message_ID
			 * @brief Message_ID struct is used to identify the service id and method id of the message
			 * @var Message_ID::service_id
			 * Member 'service_id' is used to identify the service id of the message
			 * @var Message_ID::method_id
			 * Member 'method_id' is used to identify the method id of the message
			 */
			struct Message_ID
			{
				uint16_t serivce_id;
				uint16_t method_id = 0;
			};
			/**
			 * @struct Request_ID
			 * @brief Request_ID struct is used to identify the client id and session id of the request message
			 * @var Request_ID::client_id
			 * Member 'client_id' is used to identify the client id of the request message
			 * @var Request_ID::session_id
			 * Member 'session_id' is used to identify the session id of the request message
			 */
			struct Request_ID
			{
				
				uint16_t client_id;
				uint16_t session_id=1;
			};

			/**
			 * @brief 
			 * 
			 */
			class Header
			{
			public:
				static const uint32_t HeaderSize = 16;	//!< Header size in bytes
				struct Message_ID GBMessageID;			//!< Message ID of the message	
				uint32_t GBlength;						//!< Length of the message in bytes
				struct Request_ID GBRequest_ID;			//!< Request ID of the message
				uint8_t GBProtocol_Version;				//!< Protocol version of the message
				uint8_t GBinterface_version;			//!< Interface version of the message
				MessageType GBMessageType;				//!< Message type of the message
				ReturnCode GBReturnCode;				//!< Return code of the message

				/**
				 * @brief Construct a new Header object
				 * 
				 * @param mID 				message ID 
				 * @param rID 				request ID
				 * @param protocol_version 	protocol version
				 * @param interface_version interface version
				 * @param Mtype 			message type
				 * @param Rcode 			return code
				 */
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


			/**
			 * @brief Class SOME IP Message
			 * 
			 */
			class Message : public Header
			{
			private:
				std::vector<uint8_t> payload;			//!< Payload of the message used to store the serialized message

				/**
				 * @brief Construct a new Message object
				 * 
				 * @param mID 						message ID
				 * @param rID 						request ID
				 * @param protocol_version 			protocol version
				 * @param interface_version 		interface version
				 * @param Mtype 					message type
				 * @param Rcode 					return code
				 */
                Message(
					struct Message_ID mID,
					struct Request_ID rID,
					uint8_t protocol_version,
					uint8_t interface_version,
					MessageType Mtype,
					ReturnCode Rcode) noexcept;  
                    
			public:
			/**
			 * @brief Construct a new Message object
			 * 
			 * @param mID 						message ID
			 * @param rID 						request ID
			 * @param protocol_version 			protocol version
			 * @param interface_version  		interface version
			 * @param Mtype 					message type
			 */
            Message(
					Message_ID mID,	
					Request_ID rID,
					uint8_t protocol_version,
					uint8_t interface_version,
					MessageType Mtype
					) noexcept;
			/**
			 * @brief Construct a new Message object
			 * 
			 * @param rID 						request ID
			 * @param mID 						message ID
			 * @param protocol_version 			protocol version
			 * @param interface_version 		interface version
			 * @param Rcode 					return code
			 * @param Mtype 					message type
			 */
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
                virtual uint32_t Length() noexcept ;

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

				/// @brief Get message data payload
				/// @returns Byte array
				std::vector<uint8_t> GetPayload();

				/// @brief Deserialize message payload
				/// @param msg Byte array
				static Message Deserialize(const std::vector<uint8_t> &msg);


				
				Message& operator=(Message &msg);

				std::vector<uint8_t> getload();

				bool  check_Methode_ID(){
					if((uint16_t)(this->GBMessageID.method_id&0x8000) == 0)
						return true;
					else
						return false;
				}
				
			};

		}
	}
}
#endif

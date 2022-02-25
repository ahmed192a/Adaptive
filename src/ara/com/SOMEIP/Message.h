#include <stdint.h>
#include<vector>
namespace ara
{
	namespace com
	{
		namespace SOMEIP_MESSAGE
		{
			enum class MessageType : uint8_t
			{
				REQUEST=0x00, ///!< A request expecting a response (even void)
				REQUEST_NO_RETURN=0x01,  ///!< A fire&forget request
				NOTIFICATION=0x02, ///!<A request of a notification/event callback expecting no response
                RESPONSE=0x80, ///!<The response message
				ERROR =0x81, ///!<The response containing an error
				TP_REQUEST=0x20, ///!<A TP request expecting a response (even void)
				TP_REQUEST_NO_RETURN=0x21,  ///!<A TP fire & forget request
				TP_NOTIFICATION =0x22, ///!<A TP request of a notification/event callback expecting no response
				TP_RESPONSE=0x23, ///!<The TP response message
				TP_ERROR=0x24 ///!<The TP response containing an error
			};
			enum class ReturnCode : uint8_t
			{
				E_OK, ///!<No error occurred
				E_NOT_OK, ///!<An unspecified error occurred
				E_UNKNOWN_SERVICE,///!<The requested Service ID is unknown
				E_UNKNOWN_METHOD,///!<The requested Method ID is unknown. Service ID is known.
				E_NOT_READY,///!<Service ID and Method ID are known. Application not running 
				E_NOT_REACHABLE,///!<System running the service is not reachable (proxy_skeleton error code only).
				E_TIMEOUT,///!<A timeout occurred (proxy_skeleton error code only).
				E_WRONG_PROTOCOL_VERSION,///!<Version of SOME/IP protocol not supported
				E_WRONG_INTERFACE_VERSION,///!<Interface version mismatch
				E_MALFORMED_MESSAGE,///!<Deserialization error, so that payload cannot be deserialized.
				E_WRONG_MESSAGE_TYPE,//!<An unexpected message type was received (e.g. REQUEST_NO_RETURN for a method defined as REQUEST).
				E_E2E_REPEATED,///!<Repeated E2E calculation error
				E_E2E_WRONG_SEQUENCE,///!<Wrong E2E sequence error
				E_E2E,///!<Not further specified E2E error
				E_E2E_NOT_AVAILABLE ,///!<E2E not available
				E_E2E_NO_NEW_DATA ///!<No new data for E2E calculation present
			};
			class Header
			{
              public:
			  struct Message_ID a;
			  uint32_t length;
			  struct Request_ID b;
			  uint8_t protocol_version;
			  uint8_t interface_version;
			  MessageType ab;
			  ReturnCode abc;
			  Header (struct Message_ID a,uint32_t length,struct Request_ID b,uint8_t protocol_version,uint8_t interface_version)
			  {
				  this->a.serivce_id=a.serivce_id;
				  this->a.method_id=a.method_id;
				  this->length=length;
				  this->b.client_id=b.client_id;
				  this->b.session_id=b.session_id;
				  this->protocol_version=protocol_version;
				  this->interface_version=interface_version;
			  }

			};
			class Message
			{
				Header l;
				std::vector<uint8_t>payload;
				Message(struct Message_ID a,uint32_t length,struct Request_ID b,uint8_t protocol_version,uint8_t interface_version):l(a,length,b,protocol_version,interface_version)
				{

				}
			};
			struct Message_ID
			{
				uint16_t serivce_id;
				uint16_t method_id=0;

			};
			struct Request_ID
			{
				uint16_t client_id;
				uint16_t session_id;

			};
		}
	}
}
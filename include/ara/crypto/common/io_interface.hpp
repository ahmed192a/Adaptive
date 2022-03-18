#ifndef IO_INTERFACE_HPP_
#define IO_INTERFACE_HPP_

#include <iostream>
#include <memory>
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.hpp"
#include "ara/crypto/keys/key_slot_content_props.hpp"
#include "ara/crypto/cryp/cryobj/crypto_object.hpp"
namespace ara
{
	namespace crypto
	{

			class IOInterface
			{
				public:


				using Uptr = std::unique_ptr<IOInterface>;

				using Uptrc = std::unique_ptr<const IOInterface>;

				virtual keys::KeySlotContentProps::AllowedUsageFlags GetAllowedUsage () const noexcept=0;

				virtual std::size_t GetCapacity () const noexcept=0;

				virtual cryp::CryptoObject::CryptoObjectType GetCryptoObjectType () const noexcept=0;

				virtual cryp::CryptoObject::CryptoObjectUid GetObjectId () const noexcept=0;

				virtual std::size_t GetPayloadSize () const noexcept=0;

				virtual cryp::CryptoPrimitiveId::CryptoAlgId GetPrimitiveId () const noexcept=0;

				virtual cryp::CryptoObject::CryptoObjectType GetTypeRestriction () const noexcept=0;

				virtual bool IsObjectSession () const noexcept=0;

				virtual bool IsVolatile () const noexcept=0;

				virtual ~IOInterface () noexcept=default;


			};

	}
}


#endif /* IO_INTERFACE_HPP_ */

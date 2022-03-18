#ifndef IO_INTERFACE_HPP_
#define IO_INTERFACE_HPP_

#include <iostream>
#include <memory>
#include "ara/crypto/cryp/cryobj/crypto_primitive_id.hpp"
#include "ara/crypto/keys/key_slot_content_props.hpp"
#include "ara/crypto/cryp/cryobj/crypto_object.hpp"
#include "ara/crypto/common/crypto_object_uid.hpp"

namespace ara
{
	namespace crypto
	{

			class IOInterface
			{
				public:


				using Uptr = std::unique_ptr<IOInterface>;

				using Uptrc = std::unique_ptr<const IOInterface>;

				virtual AllowedUsageFlags GetAllowedUsage () const noexcept=0;

				virtual std::size_t GetCapacity () const noexcept=0;

				virtual CryptoObjectType GetCryptoObjectType () const noexcept=0;

				virtual CryptoObjectUid GetObjectId () const noexcept=0;

				virtual std::size_t GetPayloadSize () const noexcept=0;

				virtual CryptoAlgId GetPrimitiveId () const noexcept=0;

				virtual CryptoObjectType GetTypeRestriction () const noexcept=0;

				virtual bool IsObjectSession () const noexcept=0;

				virtual bool IsVolatile () const noexcept=0;

				virtual ~IOInterface () noexcept=default;


			};

	}
}


#endif /* IO_INTERFACE_HPP_ */

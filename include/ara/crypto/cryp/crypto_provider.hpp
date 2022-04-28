#ifndef CRYPTO_PROVIDER_H_
#define CRYPTO_PROVIDER_H_

#include "ara/crypto/common/volatile_trusted_container.hpp"
#include "ara/crypto/cryp/HMAC.hpp"
#include "../common/vendor_specific_algorithm_identifier.hpp"
#include "ara/crypto/cryp/message_authn_code_ctx.hpp"
#include "ara/crypto/cryp/symmetric_key_wrapper_ctx.hpp"
#include "ara/crypto/cryp/key_derivation_function_ctx.hpp"
#include "ara/crypto/cryp/auth_cipher_ctx.hpp"
#include "ara/crypto/cryp/cryobj/signature.hpp"
#include "ara/crypto/cryp/random_generator_ctx.hpp"
#include "ara/crypto/cryp/hash_function_ctx.hpp"
#include "ara/crypto/cryp/symmetric_block_cipher_ctx.hpp"


/*
			///////////////////////////////////////////
			//			Dummy Definitions
			///////////////////////////////////////////

            class AuthCipherCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<AuthCipherCtx>;
            };
            class HashFunctionCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<HashFunctionCtx>;
            };
            class RandomGeneratorCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<RandomGeneratorCtx>;
            };

            class SymmetricBlockCipherCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;
            };
            class SymmetricKeyWrapperCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<SymmetricKeyWrapperCtx>;
            };
            class KeyDerivationFunctionCtx : public CryptoContext {
            public:
            	using Uptr = std::unique_ptr<KeyDerivationFunctionCtx>;
            };


			///////////////////////////////////////////
			///////////////////////////////////////////
			///////////////////////////////////////////
*/

#include <string>
namespace ara
{
	namespace crypto
	{
		namespace cryp
		{

			class CryptoProvider
			{
			public:

				using AlgId=CryptoPrimitiveId::AlgId;

				using Uptr = std::unique_ptr<CryptoProvider>;

				virtual VolatileTrustedContainer::Uptr AllocVolatileContainer (std::size_t capacity=0) noexcept=0;

				virtual VolatileTrustedContainer::Uptr AllocVolatileContainer (std::pair< AlgId, CryptoObjectType > theObjectDef) noexcept=0;

				virtual AlgId ConvertToAlgId (std::string primitiveName) const noexcept=0;

				virtual std::string ConvertToAlgName (AlgId algId) const noexcept=0;

				virtual AuthCipherCtx::Uptr CreateAuthCipherCtx (AlgId algId) noexcept=0;

				virtual Signature::Uptrc CreateHashDigest (AlgId hashAlgId, ReadOnlyMemRegion value) noexcept=0;

				virtual HashFunctionCtx::Uptr CreateHashFunctionCtx (AlgId algId) noexcept=0;

				virtual KeyDerivationFunctionCtx::Uptr CreateKeyDerivationFunctionCtx (AlgId algId) noexcept=0;

				virtual MessageAuthnCodeCtx::Uptr CreateMessageAuthCodeCtx (AlgId algId) noexcept=0;

				virtual RandomGeneratorCtx::Uptr CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept=0;

				virtual Signature::Uptrc CreateSignature (AlgId signAlgId, ReadOnlyMemRegion value, const RestrictedUseObject &key,AlgId hashAlgId=kAlgIdNone) noexcept=0;

				virtual SymmetricBlockCipherCtx::Uptr CreateSymmetricBlockCipherCtx (AlgId algId) noexcept=0;

				virtual SymmetricKeyWrapperCtx::Uptr CreateSymmetricKeyWrapperCtx (AlgId algId) noexcept=0;

				virtual ~CryptoProvider () noexcept=default;
			};
		}
	}
}




#endif /* CRYPTO_PROVIDER_H */

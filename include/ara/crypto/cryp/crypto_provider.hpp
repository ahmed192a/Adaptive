#ifndef CRYPTO_PROVIDER_H_
#define CRYPTO_PROVIDER_H_

#include "ara/crypto/common/volatile_trusted_container.hpp"
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

				virtual AlgId ConvertToAlgId (ara::core::StringView primitiveName) const noexcept=0;

				virtual ara::core::String ConvertToAlgName (AlgId algId) const noexcept=0;

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

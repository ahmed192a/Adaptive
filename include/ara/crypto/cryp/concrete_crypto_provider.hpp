

#ifndef ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_
#define ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_
#include "crypto_provider.hpp"
//#include "HMAC.hpp"
#include "../common/vendor_specific_algorithm_identifier.hpp"

namespace ara
{
    namespace crypto
	{

        namespace cryp
		{
        class ConcreteCryptoProvider : public CryptoProvider
		{
		public:
        	VolatileTrustedContainer::Uptr AllocVolatileContainer (std::size_t capacity=0) noexcept;
        	VolatileTrustedContainer::Uptr AllocVolatileContainer (std::pair< AlgId, CryptoObjectType > theObjectDef) noexcept;

        	AlgId ConvertToAlgId (std::string primitiveName) const noexcept;
        	std::string ConvertToAlgName (AlgId algId) const noexcept;

        	AuthCipherCtx::Uptr CreateAuthCipherCtx (AlgId algId) noexcept;

            Signature::Uptrc CreateHashDigest (AlgId hashAlgId, ReadOnlyMemRegion value) noexcept;

        	HashFunctionCtx::Uptr CreateHashFunctionCtx (AlgId algId) noexcept;

        	KeyDerivationFunctionCtx::Uptr CreateKeyDerivationFunctionCtx (AlgId algId) noexcept;

        	MessageAuthnCodeCtx::Uptr CreateMessageAuthCodeCtx (AlgId algId) noexcept;

        	RandomGeneratorCtx::Uptr CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept;

        	Signature::Uptrc CreateSignature (AlgId signAlgId, ReadOnlyMemRegion value, const RestrictedUseObject &key,AlgId hashAlgId=kAlgIdNone) noexcept;

        	SymmetricBlockCipherCtx::Uptr CreateSymmetricBlockCipherCtx (AlgId algId) noexcept;

        	SymmetricKeyWrapperCtx::Uptr CreateSymmetricKeyWrapperCtx (AlgId algId) noexcept;

        	~ConcreteCryptoProvider () noexcept=default;
		};
	  }
	}
}



#endif /*ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_ */

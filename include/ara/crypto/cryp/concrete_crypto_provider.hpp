
#pragma once
//#ifndef ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_
//#define ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_
#include "crypto_provider.hpp"
//#include "HMAC.hpp"
//#include "../common/vendor_specific_algorithm_identifier.hpp"

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
        	//VolatileTrustedContainer::Uptr AllocVolatileContainer (std::pair< AlgId, CryptoObjectType > theObjectDef) noexcept;

        	AlgId ConvertToAlgId (std::string primitiveName) const noexcept;
        	std::string ConvertToAlgName (AlgId algId) const noexcept;

        	AuthCipherCtx::Uptr CreateAuthCipherCtx (AlgId algId) noexcept;

            Signature::Uptrc CreateHashDigest (AlgId hashAlgId, ReadOnlyMemRegion value) noexcept;

        	HashFunctionCtx::Uptr CreateHashFunctionCtx (AlgId algId) noexcept;

        	//KeyDerivationFunctionCtx::Uptr CreateKeyDerivationFunctionCtx (AlgId algId) noexcept;

        	MessageAuthnCodeCtx::Uptr CreateMessageAuthCodeCtx (AlgId algId) noexcept;

        	RandomGeneratorCtx::Uptr CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept;

        	Signature::Uptrc CreateSignature (AlgId signAlgId, ReadOnlyMemRegion value, const RestrictedUseObject &key,AlgId hashAlgId=kAlgIdNone) noexcept;

        	SymmetricBlockCipherCtx::Uptr CreateSymmetricBlockCipherCtx (AlgId algId) noexcept;

        	Keywrapper::Uptr CreateSymmetricKeyWrapperCtx (AlgId algId) noexcept;
			void ImportPublicObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept;
			void ImportSecuredObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, SymmetricKeyWrapperCtx &transportContext, bool isExportable=false, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept;
			PRNG::Uptr CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept;
        	~ConcreteCryptoProvider () noexcept=default;

			SecSeed::Uptrc GenerateSeed (AlgId algId, SecretSeed::Usage allowedUsage, bool isSession, bool isExportable) noexcept;
			SymmetricKey::Uptrc GenerateSymmetricKey(AlgId algId, AllowedUsageFlags allowedUsage, bool isSession,bool isExportable) noexcept;
			SymmetricKey::Uptrc LoadSymmetricKey (const IOInterface &container) noexcept;

		 	std::vector<uint8_t>  ExportPublicObject (const ConcreteIOInterface &container) noexcept;

			std::vector<uint8_t>  ExportSecuredObject (const ConcreteIOInterface &container, SymmetricKeyWrapperCtx &transportContext) noexcept;
		};
	  }
	}
}



//#endif /*ARA_CRYPTO_CRYP_CONCRETE_CRYPTO_PROVIDER_HPP_ */

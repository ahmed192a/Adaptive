//#ifndef CRYPTO_PROVIDER_H_
//#define CRYPTO_PROVIDER_H_
#pragma once
#include "../common/concrete_io_interface.hpp"
#include "cryobj/symmetric_key.hpp"
//#include "volatile_trusted_container.hpp"
#include "HMAC.hpp"
#include "../common/vendor_specific_algorithm_identifier.hpp"
//#include "ara/crypto/cryp/message_authn_code_ctx.hpp"
#include "Keywrapper.hpp"
#include "ara/crypto/cryp/HKDF.hpp"
#include "authentication.hpp"
#include "cryobj/signature.hpp"
#include "PRNG.hpp"
#include "hash_function_ctx.hpp"
#include "symmetric_cipher.hpp"
//#include "cryobj/sec_seed.hpp"
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

				//virtual VolatileTrustedContainer::Uptr AllocVolatileContainer (std::pair< AlgId, CryptoObjectType > theObjectDef) noexcept=0;

				virtual AlgId ConvertToAlgId (std::string primitiveName) const noexcept=0;

				virtual std::string ConvertToAlgName (AlgId algId) const noexcept=0;

				virtual Authentication::Uptr CreateAuthCipherCtx (AlgId algId) noexcept=0;

				virtual Signature::Uptrc CreateHashDigest (AlgId hashAlgId, ReadOnlyMemRegion value) noexcept=0;

				virtual HashFunctionCtx::Uptr CreateHashFunctionCtx (AlgId algId) noexcept=0;

				virtual HKDF::Uptr CreateKeyDerivationFunctionCtx (AlgId algId) noexcept=0;

				virtual HMAC::Uptr CreateMessageAuthCodeCtx (AlgId algId) noexcept=0;

				virtual PRNG::Uptr CreateRandomGeneratorCtx (AlgId algId=kAlgIdDefault, bool initialize=true) noexcept=0;

				//virtual Signature::Uptrc CreateSignature (AlgId signAlgId, ReadOnlyMemRegion value, const RestrictedUseObject &key,AlgId hashAlgId=kAlgIdNone) noexcept=0;

				virtual SymmetricCipher::Uptr CreateSymmetricBlockCipherCtx (AlgId algId) noexcept=0;

				virtual Keywrapper::Uptr CreateSymmetricKeyWrapperCtx (AlgId algId) noexcept=0;

				virtual std::vector<uint8_t>  ExportPublicObject (const ConcreteIOInterface &container) noexcept=0;

				virtual std::vector<uint8_t>  ExportSecuredObject (const ConcreteIOInterface &container, SymmetricKeyWrapperCtx &transportContext) noexcept=0;

				virtual SecSeed::Uptrc GenerateSeed (AlgId algId, SecSeed::Usage allowedUsage, bool isSession=true, bool isExportable=false) noexcept=0;

				virtual SymmetricKey::Uptrc GenerateSymmetricKey(AlgId algId, AllowedUsageFlags allowedUsage, bool isSession=true,bool isExportable=false) noexcept=0;

				virtual std::size_t GetPayloadStorageSize (CryptoObjectType cryptoObjectType, AlgId algId) const noexcept=0;

				virtual std::size_t GetSerializedSize (CryptoObjectType cryptoObjectType, AlgId algId) const noexcept=0;

				virtual void ImportPublicObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept=0;

				virtual void ImportSecuredObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, SymmetricKeyWrapperCtx &transportContext, bool isExportable=false, CryptoObjectType expectedObject=CryptoObjectType::kUndefined) noexcept=0;

				virtual CryptoObject::Uptrc LoadObject (const ConcreteIOInterface &container) noexcept=0;

				virtual SecretSeed::Uptrc LoadSecretSeed (const ConcreteIOInterface &container) noexcept=0;

				virtual SymmetricKey::Uptrc LoadSymmetricKey (const ConcreteIOInterface &container) noexcept=0;

				virtual ~CryptoProvider () noexcept=default;
			};
		}
	}
}




//#endif /* CRYPTO_PROVIDER_H */

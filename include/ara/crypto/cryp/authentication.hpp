#ifndef  ARA_CRYPTO_AUTHENTICATION_H
#define  ARA_CRYPTO_AUTHENTICATION_H

#include "auth_cipher_ctx.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

			class Authentication : public AuthCipherCtx
			{
			public:
				// implementation of the CyrptoContext virtual functions
				// function to determine whether context is ready to use or not 
				bool IsInitialized();
				// function to return the CryptoPrimitivId instance containing instance identification 
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

				// implementation of auth_cipher_ctx inherited virtual functions
            public:
                
                bool Check(const Signature& expected) const noexcept;

                //virtual BlockService::Uptr GetBlockService() const noexcept = 0;

                CryptoTransform GetTransformation() const noexcept;

                /*template <typename Alloc = <implementation - defined>>
                ara::core::Result<ByteVector<Alloc> > GetDigest(std::size_t offset = 0) const noexcept;*/

                std::uint64_t GetMaxAssociatedDataSize() const noexcept;

                /*ara::core::Result<ara::core::Vector<ara::core::Byte> > Process
                    ConfidentialData(ReadOnlyMemRegion in, ReadOnlyMemRegion expected Tag = nullptr) noexcept;*/

                    //void ProcessConfidentialData(ReadWriteMemRegion inOut, ReadOnlyMemRegion expectedTag = nullptr) noexcept;

                void Reset() noexcept;

                void SetKey(const SymmetricKey& key, CryptoTransform transform = CryptoTransform::kEncrypt) noexcept;

                void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept;

                void Start(const SecretSeed& iv) noexcept;

                void UpdateAssociatedData(const RestrictedUseObject& in) noexcept;

                void UpdateAssociatedData(ReadOnlyMemRegion in) noexcept;

                void UpdateAssociatedData(std::uint8_t in) noexcept;





			

			};

        }
    }
}










#endif // ! ARA_CRYPTO_AUTHENTICATION_H

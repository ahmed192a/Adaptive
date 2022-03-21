#include <iostream>

// #ifndef ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
// #define ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H

// #include <iostream>
#include <memory>
#include <vector>

#include "ara/crypto/common/mem_region.hpp"
#include "ara/crypto/common/base_id_types.hpp"
// #include "ara/crypto/cryp/crypto_context.hpp"
#include "ara/crypto/cryp/HMAC_digest_service.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {
            //This partition is only used for testing

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            class CryptoContext{};
            class Signature {
                public:
                using Uptrc = std::unique_ptr<const Signature>;
            };
            class SymmetricKey {};
            class RestrictedUseObject{};
            class ReadOnlyMemRegion{};
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
            class SecretSeed{};
            ///////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////


            enum class MessageAuthnCodeCtx_Status : std::uint8_t {
                notInitialized = 0,
                initialized = 1,
                started = 2,

            };

            class MessageAuthnCodeCtx : public CryptoContext {
                
                public:
                using Uptr = std::unique_ptr<MessageAuthnCodeCtx>;  

                // this pointer will point to the resulting signature
                Signature::Uptrc signature_ptr;

                // The current status of the context
                MessageAuthnCodeCtx_Status status = MessageAuthnCodeCtx_Status::notInitialized;


                virtual void Reset() noexcept = 0;
                virtual void SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) noexcept = 0;
                virtual bool Check(const Signature &expected) const noexcept = 0;


                virtual void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept = 0;
                virtual void Start(const SecretSeed &iv) noexcept = 0;

                virtual void Update(const RestrictedUseObject &in) noexcept = 0;
                virtual void Update(ReadOnlyMemRegion in) noexcept = 0;
                virtual void Update(std::uint8_t in) noexcept = 0;

                virtual Signature::Uptrc Finish(bool makeSignatureObject = false) noexcept = 0;

                virtual DigestService::Uptr GetDigestService() const noexcept = 0;
                virtual std::vector<byte> GetDigest(std::size_t offset = 0) const noexcept = 0;
                // template <typename Alloc = <implementation-defined>>
                // ara::core::Result<ByteVector<Alloc> > GetDigest(std::size_t offset = 0) const noexcept;

            };





        } // namespace cryp
    } // namespace crypto
} // namespace ara

// #endif // ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
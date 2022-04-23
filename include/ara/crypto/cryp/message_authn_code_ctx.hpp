#include <iostream>

#ifndef ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
#define ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H

#include <memory>
#include <vector>
#include <boost/variant.hpp>

#include "ara/crypto/common/mem_region.hpp"
#include "ara/crypto/common/base_id_types.hpp"
#include "ara/crypto/cryp/crypto_context.hpp"
#include "ara/crypto/cryp/HMAC_digest_service.hpp"
#include "ara/crypto/cryp/cryobj/restricted_use_object.hpp"
#include "ara/crypto/cryp/cryobj/signature.hpp"
#include "ara/crypto/cryp/random_generator_ctx.hpp"
// #include "ara/crypto/cryp/cryobj/secret_seed.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            ///////////////////////////////////////////////////////
            class SymmetricKey {};
            class ReadOnlyMemRegion{};
            ///////////////////////////////////////////////////////////

            enum class MessageAuthnCodeCtx_Status : std::uint8_t {
                notInitialized = 0,
                initialized = 1,
                started = 2,
                updated = 3,
                finished = 4
            };

            class MessageAuthnCodeCtx : public CryptoContext {
                
                public:
                using Uptr = std::unique_ptr<MessageAuthnCodeCtx>; 

                protected: 

                Signature::Uptrc signature_ptr; // this pointer will point to the resulting signature

                MessageAuthnCodeCtx_Status status = MessageAuthnCodeCtx_Status::notInitialized; // // The current status of the context

                public:

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

#endif // ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
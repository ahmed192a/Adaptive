#ifndef ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
#define ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H

#include <iostream>
#include <memory>
#include <vector>

#include "../common/base_id_types.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {
            

            //This partition is only used for testing

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            class CryptoContext {};
            class Signature {
                public:
                using Uptrc = std::uint16_t;
            };
            class SymmetricKey {};
            class RestrictedUseObject{};
            class ReadOnlyMemRegion{};
            class SecretSeed{};
            class DigestService{ 
                public:
                using Uptr = std::uint16_t;
            };
            ///////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////


            class MessageAuthnCodeCtx : public CryptoContext {

                 using Uptr = std::unique_ptr<MessageAuthnCodeCtx>;  

                
                
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
                //virtual std::vector<ara::core::Byte> GetDigest(std::size_t offset = 0) const noexcept = 0;
                // template <typename Alloc = <implementation-defined>>
                // ara::core::Result<ByteVector<Alloc> > GetDigest(std::size_t offset = 0) const noexcept;
                

                

            };





        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_MESSAGE_AUTHN_CODE_CTX_H
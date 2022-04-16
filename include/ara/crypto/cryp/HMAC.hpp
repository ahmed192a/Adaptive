#ifndef ARA_CRYPTO_HMAC_H
#define ARA_CRYPTO_HMAC_H

#include "message_authn_code_ctx.hpp"


namespace ara {
    namespace crypto {
        namespace cryp {

        

            class HMAC : public MessageAuthnCodeCtx {

                // pointer to the hash function context used to implement this algorithm
                HashFunctionCtx::Uptr hashFunction;
                SymmetricKey key;

                CryptoProvider * myProvider;

                public:
                /// @brief constructor
                HMAC(CryptoProvider * provider);

                /** Inherited from CryptoContext class**/
                /// @brief destructor
                ~HMAC() noexcept = default;
                
                bool IsInitialized();

				/*Return CryptoPrimitivId instance containing instance identification */
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

				/* Get a reference to Crypto Provider of this context*/
				CryptoProvider& MyProvider() const noexcept;


            /** Inherited from MessageAuthnCode class**/


                void Reset() noexcept;
                void SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) noexcept;

                void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept;
                // void Start(const SecretSeed &iv) noexcept;

                // bool Check(const Signature &expected) const noexcept;

                // void Update(const RestrictedUseObject &in) noexcept;
                // void Update(ReadOnlyMemRegion in) noexcept;
                void Update(std::uint8_t in) noexcept;

                DigestService::Uptr GetDigestService() const noexcept;
                std::vector<ara::crypto::byte> GetDigest(std::size_t offset = 0) const noexcept;
    
                Signature::Uptrc Finish(bool makeSignatureObject = false) noexcept;
            };






        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_HMAC_H
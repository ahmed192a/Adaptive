//#ifndef ARA_CRYPTO_HMAC_H
//#define ARA_CRYPTO_HMAC_H
#pragma once
#include "message_authn_code_ctx.hpp"
#include "sha256.hpp" // temporariy till hash implementation is finished


namespace ara {
    namespace crypto {
        namespace cryp {
            class ConcreteCryptoProvider;
            class HMAC : public MessageAuthnCodeCtx {
                
                private:

                int B = 64;  // bytes ==> length of each block

                // constants to be XORed with the key to increase the hamming distance
                std::uint8_t iPad = 0x36;
                std::uint8_t oPad = 0x5C;

                // Keys after XORing the constants
                std::vector<byte> input_key;

                std::vector<byte> digest; // The resulting digest
                std::vector<byte> inputBuffer; // the input buttered

                //SymmetricKey& key;

                ConcreteCryptoProvider * myProvider;

                // hashing function
                void hash_sha256(std::vector<byte> input, std::vector<byte> &output);

                // hmac algorithm
                void hmac_digestion(std::vector<byte> &plainText, std::vector<byte> &output);

                public:
                /// @brief constructor
                HMAC(ConcreteCryptoProvider * provider);

                /** Inherited from CryptoContext class**/
                /// @brief destructor
              //  ~HMAC() noexcept = default;
                
                bool IsInitialized()const noexcept;

				/*Return CryptoPrimitivId instance containing instance identification */
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

				/* Get a reference to Crypto Provider of this context*/
				ConcreteCryptoProvider& MyProvider() const noexcept;


            /** Inherited from MessageAuthnCode class**/


                void Reset() noexcept;
                void SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) noexcept;

                void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept;
                // void Start(const SecretSeed &iv) noexcept;

                // bool Check(const Signature &expected) const noexcept;

                // void Update(const RestrictedUseObject &in) noexcept;
                // void Update(ReadOnlyMemRegion in) noexcept;
                void Update(std::uint8_t in) noexcept;

                //DigestService::Uptr GetDigestService() const noexcept;
                std::vector<ara::crypto::byte> GetDigest(std::size_t offset = 0) const noexcept;
    
                Sign::Uptrc Finish(bool makeSignatureObject = false) noexcept;
            };






        } // namespace cryp
    } // namespace crypto
} // namespace ara

//#endif // ARA_CRYPTO_HMAC_H


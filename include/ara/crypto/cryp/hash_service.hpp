/**
 * @file HMAC_digest_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::HashService class implementation
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_HASH_SERVICE_H
#define ARA_CRYPTO_HASH_SERVICE_H

#include "ara/crypto/cryp/hash_function_ctx.hpp"
#include "ara/crypto/common/base_id_types.hpp"


namespace ara {
    namespace crypto{
        namespace cryp{

            class HashService : public HashFunctionCtx
            {
            private:
                std::vector<byte> hashedValue; 
                std::vector<byte> vectorToBeHashed;
                std::string x;
                bool flagInit = 0;
                CryptoProvider * myProvider;


            public:

                /// @brief Unique smart pointer of HashService.
                using Uptr = std::unique_ptr<HashService>;

                HashService(CryptoProvider * myProvider);


                /************************* HASHFUNCTIONCTX METHODS ***********************************/

                /// @brief Finish the digest calculation and optionally produce the "signature" object. Only after call of this method the digest can be signed, verified, extracted or compared.
                /// @returns unique smart pointer to created signature object,
                std::vector<std::byte> Finish() noexcept;


                /// @brief Get DigestService instance.
                /// @returns DigestService::Uptr
                DigestService::Uptr GetDigestService() const noexcept;


                /// @brief Get requested part of calculated digest.
                /// @param[in] offset position of the first byte of digest that should be placed to the output buffer.
                /// @returns number of digest bytes really stored to the output buffer
                std::vector<std::byte> GetDigest (std::size_t offset=0) const noexcept;

                /// @brief Initialize the context for a new data stream processing or generation (depending on the primitive) without IV.
                /// @returns ara::core::Result<void>
                void Start() noexcept;

                /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                /// @param[in] in part of input message processed (byte value to br processed)
                void Update (std::uint8_t in) noexcept;

                /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                /// @param[in] in part of input message processed 
                void Update (ReadOnlyMemRegion in) noexcept;


                /****************************** CRYPTOCONTEXT METHODS ***************************/
                bool IsInitialized();

				/*Return CryptoPrimitivId instance containing instance identification */
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

				/* Get a reference to Crypto Provider of this context*/
				CryptoProvider& MyProvider() const noexcept;



                
                ~HashService();
            };
            

        }
    }
}












#endif // ARA_CRYPTO_HASH_SERVICE_H

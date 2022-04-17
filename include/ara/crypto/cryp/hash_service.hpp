/**
 * @file HMAC_digest_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::HashService class implementation
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_HASH_SERVICE_H
#define ARA_CRYPTO_HASH_SERVICE_H

#include "hash_function_ctx.hpp"


namespace ara {
    namespace crypto{
        namespace cryp{

            class HashService : public HashFunctionCtx
            {
            private:
                /* data */
            public:

                /// @brief Unique smart pointer of HashService.
                using Uptr = std::unique_ptr<HashService>;


                /************************* HASHFUNCTIONCTX METHODS ***********************************/
                /// @brief Create Hash Function Context as it implement hashing and store calculated hash
                /// @param[in] algID identifier of the target crypto algorithm
                /// @returns unique smart pointer to the created context
                ara::core::Result<HashFunctionCtx::Uptr> CreateHashFunctionCtx(AlgId algId) noexcept=0;


                /// @brief Finish the digest calculation and optionally produce the "signature" object. Only after call of this method the digest can be signed, verified, extracted or compared.
                /// @returns unique smart pointer to created signature object,
                ara::core::Result<ara::core::Vector<ara::core::Byte> > Finish() noexcept=0;


                /// @brief Get DigestService instance.
                /// @returns DigestService::Uptr
                DigestService::Uptr GetDigestService() const noexcept=0;


                /// @brief Get requested part of calculated digest.
                /// @param[in] offset position of the first byte of digest that should be placed to the output buffer.
                /// @returns number of digest bytes really stored to the output buffer
                ara::core::Result<ara::core::Vector<ara::core::Byte>> GetDigest (std::size_t offset=0) const noexcept=0;

                /// @brief Initialize the context for a new data stream processing or generation (depending on the primitive) without IV.
                /// @returns ara::core::Result<void>
                ara::core::Result<void> Start() noexcept=0;

                /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                /// @param[in] in part of input message processed (byte value to br processed)
                ara::core::Result<void> Update (std::uint8_t in) noexcept=0;

                /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                /// @param[in] in part of input message processed 
                ara::core::Result<void> Update (ReadOnlyMemRegion in) noexcept=0;


                /****************************** CRYPTOCONTEXT METHODS ***************************/
                bool IsInitialized();

				/*Return CryptoPrimitivId instance containing instance identification */
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

				/* Get a reference to Crypto Provider of this context*/
				CryptoProvider& MyProvider() const noexcept;



                HashService(/* args */);
                ~HashService();
            };
            

        }
    }
}












#endif // ARA_CRYPTO_HASH_SERVICE_H
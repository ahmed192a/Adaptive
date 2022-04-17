/**
 * @file hash_function_ctx.hpp
 * @author 
 * @brief  ara::crypto::cryp::HashFunctionCtx class interface
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_HASH_FUNCTION_CTX_H
#define ARA_CRYPTO_HASH_FUNCTION_CTX_H
#include "crypto_context.hpp"

namespace ara {
    namespace crypto{
        namespace cryp{

            class HashFunctionCtx : public CryptoContext {
                public:

                    /// @brief Unique smart pointer of the interface.
                    using Uptr = std::unique_ptr<HashFunctionCtx>;

                    /// @brief Create Hash Function Context as it implement hashing and store calculated hash
                    /// @param[in] algID identifier of the target crypto algorithm
                    /// @returns unique smart pointer to the created context
                    virtual ara::core::Result<HashFunctionCtx::Uptr> CreateHashFunctionCtx(AlgId algId) noexcept=0;


                    /// @brief Finish the digest calculation and optionally produce the "signature" object. Only after call of this method the digest can be signed, verified, extracted or compared.
                    /// @returns unique smart pointer to created signature object,
                    virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > Finish() noexcept=0;


                    /// @brief Get DigestService instance.
                    /// @returns DigestService::Uptr
                    virtual DigestService::Uptr GetDigestService() const noexcept=0;


                    /// @brief Get requested part of calculated digest.
                    /// @param[in] offset position of the first byte of digest that should be placed to the output buffer.
                    /// @returns number of digest bytes really stored to the output buffer
                    virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> GetDigest (std::size_t offset=0) const noexcept=0;

                    /// @brief Initialize the context for a new data stream processing or generation (depending on the primitive) without IV.
                    /// @returns ara::core::Result<void>
                    virtual ara::core::Result<void> Start() noexcept=0;

                    /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                    /// @param[in] in part of input message processed (byte value to br processed)
                    virtual ara::core::Result<void> Update (std::uint8_t in) noexcept=0;

                    /// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
                    /// @param[in] in part of input message processed 
                    virtual ara::core::Result<void> Update (ReadOnlyMemRegion in) noexcept=0;


            };
        }
    }
}





#endif // ARA_CRYPTO_HASH_FUNCTION_CTX_H
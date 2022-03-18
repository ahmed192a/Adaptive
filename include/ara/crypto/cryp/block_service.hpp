/**
 * @file block_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::BlockService class interface
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_BLOCK_SERVICE_H
#define ARA_CRYPTO_BLOCK_SERVICE_H

#include "extension_service.hpp"
#include <optional>

namespace ara {
    namespace crypto {
        namespace cryp {

            class BlockService : public ExtensionService {
                public:
                
                /// @brief Unique smart pointer of this interface => BlockService
                using Uptr = std::unique_ptr<BlockService>;


                /// @brief Get actual bit-length of an IV loaded to the context
                /// @param[in] ivUid 
                /// @returns actual length of the IV (now set to the algorithm context) in bits
                //virtual std::size_t GetActualIvBitLength(std::optional<CryptoObjectUid> ivUid) const noexcept = 0;


                /// @brief Get block (or internal buffer) size of the base algorithm
                /// @returns size of the block in bytes
                virtual std::size_t GetBlockSize() const noexcept = 0;
                
                
                /// @brief Get default expected size of the Initialization Vector (IV) or nonce
                /// @returns default expected size of IV in bytes
                virtual std::size_t GetIvSize() const noexcept = 0;


                /// @brief Verify validity of specific Initialization Vector (IV) length
                /// @param[in] ivSize is the length of the IV in bytes
                /// @returns true if provided IV length is supported by the algorithm, otherwise false
                virtual bool IsValidIvSize(std::size_t ivSize) const noexcept = 0;




            };

        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_BLOCK_SERVICE_H
/**
 * @file HMAC_digest_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::HMACDigestService class implementation
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_HMAC_DIGEST_SERVICE_H
#define ARA_CRYPTO_HMAC_DIGEST_SERVICE_H

#include "digest_service.hpp"
#include "ara/crypto/common/base_id_types.hpp"
#include <vector>

namespace ara {
    namespace crypto {
        namespace cryp {

            class HMACDigestService : public DigestService {
                

                // this data values should be initialized

                // HMAC Algorithm Meta-data
                std::size_t key_maxBitLength; // in bits
                std::size_t key_minBitLength; // in bits 
                
                std::size_t size = 0;
                std::vector<byte> digest;

                public:

                using Uptr = std::unique_ptr<HMACDigestService>;

                // ExtensionService
                // std::size_t GetActualKeyBitLength() const noexcept;
                // CryptoObjectUid GetActualKeyCOUID() const noexcept;
                // AllowedUsageFlags GetAllowedUsage() const noexcept;

                std::size_t GetMaxKeyBitLength() const noexcept;
                std::size_t GetMinKeyBitLength() const noexcept;

                bool IsKeyBitLengthSupported(std::size_t keyBitLength) const noexcept;
                // bool IsKeyAvailable() const noexcept;


                // BlockService Implementations
                //std::size_t GetActualIvBitLength(std::optional<CryptoObjectUid> ivUid) const noexcept;
                // std::size_t GetBlockSize() const noexcept;
                // std::size_t GetIvSize() const noexcept;
                // bool IsValidIvSize(std::size_t ivSize) const noexcept;



                // DigestService Implementations
                // bool Compare(ReadOnlyMemRegion expected, std::size_t offset = 0) const noexcept;
                std::size_t GetDigestSize() const noexcept;
                // bool IsFinished() const noexcept;
                // bool IsStarted() const noexcept;


            };

        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_HMAC_DIGEST_SERVICE_H
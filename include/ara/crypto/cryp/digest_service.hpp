/**
 * @file digest_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::DigestService class interface
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_DIGEST_SERVICE_H
#define ARA_CRYPTO_DIGEST_SERVICE_H

#include "block_service.hpp"
#include "ara/crypto/common/mem_region.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {


            class DigestService : public BlockService {
                public:

                /// @brief Unique smart pointer of this interface => DigestService
                using Uptr = std::unique_ptr<DigestService>;


                /// @brief Compare the calculated digest against an expected value
                /// @param[in] expected is the memory region containing an expected digest value
                /// @param offset is the position of the first byte in calculated digest for the comparison starting
                /// @returns true if the compared values are identical, otherwise false
                virtual bool Compare(ReadOnlyMemRegion expected, std::size_t offset = 0) const noexcept = 0;


                /// @brief Get the output digest size
                /// @returns size of the full output from this digest-function in bytes
                virtual std::size_t GetDigestSize() const noexcept = 0;


                /// @brief Check current status of the stream processing: finished or no
                /// @returns true if Finish() was called successfully, otherwise false
                virtual bool IsFinished() const noexcept = 0;


                /// @brief Check current status of the stream processing: started or no.
                /// @returns true if Start() was called successfully, otherwise false
                virtual bool IsStarted() const noexcept = 0;


            };

        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_DIGEST_SERVICE_H
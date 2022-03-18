/**
 * @file extension_service.hpp
 * @author 
 * @brief  ara::crypto::crpy::ExtensionSrevice class interface
 * @version R20-11
 *****************************************************************/

#ifndef ARA_CRYPTO_EXTENSION_SERVICE_H
#define ARA_CRYPTO_EXTENSION_SERVICE_H

#include <cstdint>
#include <memory>
#include "ara/crypto/common/crypto_object_uid.hpp"
#include "ara/crypto/common/base_id_types.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            class ExtensionService {
                
                public:
                
                using Uptr = std::unique_ptr<ExtensionService>;

                /// @brief Destructor
                virtual ~ExtensionService() noexcept = default;


                /// @brief Get actual bit-length of a key loaded to the context. If no key was set to the context yet then 0 is returned 
                /// @param 
                /// @returns the actual bit length of key, otherwise if no key it returns zero
                virtual std::size_t GetActualKeyBitLength() const noexcept = 0;

                /// @brief Get the COUID of the key deployed to the context this extension service is attached to. If no key was set to the context yet then an empty COUID (Nil) is returned.
                virtual CryptoObjectUid GetActualKeyCOUID() const noexcept = 0;
                virtual AllowedUsageFlags GetAllowedUsage() const noexcept = 0;

                virtual std::size_t GetMaxKeyBitLength() const noexcept = 0;
                virtual std::size_t GetMinKeyBitLength() const noexcept = 0;

                virtual bool IsKeyBitLengthSupported(std::size_t keyBitLength) const noexcept = 0;
                virtual bool IsKeyAvailable() const noexcept = 0;

                ExtensionService& operator=(const ExtensionService &other) = default;
                ExtensionService& operator=(ExtensionService &&other) = default;



            };

        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_EXTENSION_SERVICE_H
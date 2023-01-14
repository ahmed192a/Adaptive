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
#include "ara/crypto/common/crypto_object_uid.h"
#include "ara/crypto/common/base_id_types.h"

namespace ara {
    namespace crypto {
        namespace cryp {

            class ExtensionService {
                
                public:
                
                /// @brief Unique smart pointer of this interface => ExtensionService
                using Uptr = std::unique_ptr<ExtensionService>;


                /// @brief Destructor
                virtual ~ExtensionService() noexcept = default;


                /// @brief Get actual bit-length of a key loaded to the context
                /// @returns the actual bit length of key, otherwise if no key it returns zero
                virtual std::size_t GetActualKeyBitLength() const noexcept = 0;


                /// @brief Get the COUID of the key deployed to the context this extension service is attached to.
                /// @return the COUID of the CryptoObject(key). If no key return null
                virtual CryptoObjectUid GetActualKeyCOUID() const noexcept = 0;


                /// @brief 
                /// @return 
                virtual AllowedUsageFlags GetAllowedUsage() const noexcept = 0;


                /// @brief Get maximum supported key length in bits
                /// @return std::size_t
                virtual std::size_t GetMaxKeyBitLength() const noexcept = 0;


                /// @brief Get minimal supported key length in bits
                /// @return std::size_t
                virtual std::size_t GetMinKeyBitLength() const noexcept = 0;


                /// @brief Verify supportness of specific key length by the context
                /// @param[in] keyBitLength is the length of the key in bits
                /// @return true if provided value of the key length is supported                
                virtual bool IsKeyBitLengthSupported(std::size_t keyBitLength) const noexcept = 0;
                

                /// @brief Check if a key has been set to this context
                /// @return false if no key has been set
                virtual bool IsKeyAvailable() const noexcept = 0;


                /// @brief copy assignment operator
                ExtensionService& operator=(const ExtensionService &other) = default;


                /// @brief move assignment operator
                ExtensionService& operator=(ExtensionService &&other) = default;

            };

        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_EXTENSION_SERVICE_H
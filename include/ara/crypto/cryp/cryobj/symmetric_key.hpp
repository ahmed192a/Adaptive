//#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H
///#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H
#pragma once
#include "rest_use_obj.hpp"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            //class RestrictedUseObject;
            class SymmetricKey : public RestUseObj {
                
                public:
                using Uptrc = std::unique_ptr<const SymmetricKey>;

                //SWS_CRYPT_23002
                /**
                 * @brief Unique smart pointer of a volatile interface instance.
                 * 
                 */
                using Uptr = std::unique_ptr<SymmetricKey>;
                static const CryptoObjectType kObjectType = CryptoObjectType::kSymmetricKey;
                uint32_t Seed;
                std::vector<uint8_t> keyVal;
                using Usage = AllowedUsageFlags;
                Usage allowed;
                bool Volatile;
                bool session;
                bool exportable;
                /**
                 * @brief Construct a new Symmetric Key object
                 * 
                 */
                 SymmetricKey();
                /**
                 * @brief Construct a new Symmetric Key object
                 * 
                 * @param allowedVal 
                 * @param sessionVar 
                 * @param exportableVar 
                 */
                SymmetricKey(AllowedUsageFlags allowedVal,bool sessionVar,bool exportableVar);
               
               
               // ~SymmetricKey() noexcept;
            };
        }
    }
}

//#endif // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H
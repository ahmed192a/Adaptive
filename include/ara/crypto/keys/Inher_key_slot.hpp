#ifndef ARA_CRYPTO_KEYS_INH_KEYSLOT_H_
#define ARA_CRYPTO_KEYS_INH_KEYSLOT_H_

#include "ara/crypto/keys/keyslot.hpp"

namespace ara
{
    namespace crypto
    {
       namespace keys
        { 
            
            class InhKeySlot : public KeySlot 
            {
                public:
        
                /**
                * @brief Destroy the Key Slot object
                */
                
                ~InhKeySlot() noexcept=default;
               /**
               * @brief Get the Content Props object
               *
               * @return ara::core::Result<KeySlotContentProps>
               */
                ara::core::Result<KeySlotContentProps> GetContentProps ()const noexcept=0;
                /**
                *  @brief Retrieve an instance of the CryptoProvider that owns this KeySlot. Any key slot always has an
                *  associated default Crypto Provider that can serve this key slot. In the simplest case all key slots
                * can be served by a single Crypto Provider installed on the Adaptive Platform.
                * @return ara::core::Result<cryp::CryptoProvider::Uptr>
                */
                ara::core::Result<cryp::CryptoProvider::Uptr> MyProvider ()const noexcept=0;
             
                /**
                * @brief Clear the content of this key-slot.
                *
                **/
               ara::core::Result<void> Clear () noexcept=0;
            };
        }
    }
}

#endif


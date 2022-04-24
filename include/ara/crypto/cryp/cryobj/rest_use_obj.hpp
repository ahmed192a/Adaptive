#ifndef ARA_CRYPTO_CRYP_RESTUSEOBJ_H_
#define ARA_CRYPTO_CRYP_RESTUSEOBJ_H_

#include <iostream>
#include <memory>
//#include <ara/crypto/cryp/cryobj/crypto_object.hpp>
#include "ara/crypto/cryp/cryobj/restricted_use_object.hpp"
#include "ara/crypto/keys/key_slot_content_props.hpp"
namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            //SWS_CRYPT_24800
            /**
             * @brief A common interface for all objects supporting the usage restriction.
             * @file restricted_use_object
             */
            class RestUseObj : public RestrictedUseObject 
            {
                public:
                 
                //ara::crypto::keys::KeySlotContentProps *Key_prop_allow;
                 //
                /**
                 * @brief Alias to the container type for bit-flags of allowed usages of the object
                 * 
                 */
                using Usage = AllowedUsageFlags;
                //SWS_CRYPT_24802
                /**
                 * @brief Unique smart pointer of the interface.
                 * 
                 */
                using Uptrc = std::unique_ptr<RestrictedUseObject>;
                //SWS_CRYPT_24811]
                /**
                 * @brief Get the Allowed Usage object ,Get allowed usages of this object.
                 * 
                 * @return Usage 
                 */
                Usage GetAllowedUsage () const noexcept;

            };
        }
    }
}
#endif
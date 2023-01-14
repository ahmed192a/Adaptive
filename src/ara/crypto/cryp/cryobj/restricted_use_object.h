//#ifndef ARA_CRYPTO_CRYP_RESTRICTEDUSEOBJECT_H_
////#define ARA_CRYPTO_CRYP_RESTRICTEDUSEOBJECT_H_
#include <iostream>
#include <memory>
#include "crypto_obj.h"
#pragma once


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
            class RestrictedUseObject : public cryptoobj
            {
                public:
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
                /**
                 * @brief Construct a new Restricted Use Object object
                 * 
                 */
                RestrictedUseObject()=default;
                //SWS_CRYPT_24811]
                /**
                 * @brief Get the Allowed Usage object ,Get allowed usages of this object.
                 * 
                 * @return Usage 
                 */
                virtual Usage GetAllowedUsage () const noexcept=0;

            };
        }
    }
}
//#endif

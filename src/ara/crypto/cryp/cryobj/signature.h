#pragma once
#include <iostream>
#include <memory>
#include "rest_use_obj.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            //SWS_CRYPT_23300
            /**
             * @brief Signature container interface This interface is applicable for keeping the Digital Signature, Hash
             * Digest, (Hash-based) Message Authentication Code (MAC/HMAC). In case of a keyed
             * signature (Digital Signature or MAC/HMAC) a COUID of the signature verification key can be
             * obtained by a call of CryptoObject::HasDependence()!
             * 
             */
            class Signature : public RestUseObj
            {

                public:

                
                
                /**
                 * @brief Signature object initialized.
                 * 
                 */
                const CryptoObjectType kObjectType = CryptoObjectType::kSignature;

                //SWS_CRYPT_23301
                /**
                 * @brief Unique smart pointer of the interface.
                 * 
                 */
                using Uptrc = std::unique_ptr<const Signature>;

                //SWS_CRYPT_23311
                /**
                 * @brief Get the Hash Alg Id object
                 * 
                 * @return CryptoPrimitiveId::AlgId 
                 */
                virtual CryptoPrimitiveId::AlgId GetHashAlgId () const noexcept=0;

                //SWS_CRYPT_23312
                /**
                 * @brief Get the Required Hash Size object
                 * Get the hash size required by current signature algorithm
                 * 
                 * @return std::size_t 
                 */
                virtual std::size_t GetRequiredHashSize () const noexcept=0;
                

            };
        }
    }
}

#ifndef ARA_CRYPTO_CRYP_CRYBOBJ_
#define ARA_CRYPTO_CRYP_CRYBOBJ_
#include <memory>
#include <iostream>
#include "../../../core/StringView.h"
#include "../../common/base_id_types.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /*
            * SWS_CRYPT_20600
            *Common interface for identification of all Crypto Primitives and their keys & parameters
            */
           class CryptoPrId;
            class CryptoPrimitiveId 
            {
                public:
                
                /** 
                 * SWS_CRYPT_10808
                 * @brief Destroy the Crypto Primitive Id object
                 * 
                 */
                virtual ~CryptoPrimitiveId () noexcept=default;
                /**
                 * SWS_CRYPT_20641
                 * @brief 
                 * Type definition of vendor specific binary Crypto Primitive ID.
                 */
                using AlgId = CryptoAlgId; 
                /**
                 * @brief Construct a new Crypto Primitive Id object
                 * 
                 */
                CryptoPrimitiveId()=default;
                /*
                * SWS_CRYPT_20644
                * Unique smart pointer of the constant interface.
                */
                using Uptrc = std::unique_ptr<const CryptoPrimitiveId>;
                /*
                * SWS_CRYPT_20643
                * Unique smart pointer of the interface.
                * smart pointer to allocate and free in memory automatically 
                * and cant make a copy from it
                */
                using Uptr = std::unique_ptr<CryptoPrimitiveId>;
                /**
                 * @brief Get the Crypto Primitive Id object
                 * 
                 * @return CryptoPrimitiveId::Uptr 
                 */
                //virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId () const noexcept=0;*/
                /**
                 * SWS_CRYPT_20652
                 * @brief Get the Primitive Id object
                 * Get vendor specific ID of the primitive.
                 * @return AlgId 
                 */
                virtual AlgId GetPrimitiveId () const noexcept=0;
                /**
                 * SWS_CRYPT_20651
                 * @brief Get the Primitive Name object
                 * Get a unified name of the primitive. The crypto primitive name can be fully or partially specified
                 * (see "Crypto Primitives Naming Convention" for more details). The life-time of the returned
                 * StringView instance should not exceed the life-time of this CryptoPrimitiveId instance!
                 * @return const ara::core::StringView 
                 */
                virtual const std::string GetPrimitiveName () const noexcept=0;
                /**
                 * SWS_CRYPT_30212
                 * @brief 
                 * Copy-assign another CryptoPrimitiveId to this instance.
                 * @param other 
                 * @return CryptoPrimitiveId& 
                 */
                CryptoPrimitiveId& operator= (const CryptoPrId &other);
                /**
                 * SWS_CRYPT_30213
                 * @brief 
                 * Move-assign another CryptoPrimitiveId to this instance.
                 * @param other 
                 * @return CryptoPrimitiveId& 
                 */
                CryptoPrimitiveId& operator= (CryptoPrId &&other);
                /**
                 * SWS_CRYPT_23311
                 *  @brief Get the Hash Alg Id object
                 * Get an ID of hash algorithm used for this signature object production.
                 * @return CryptoPrimitiveId::AlgId 
                 */
                //virtual AlgId GetHashAlgId () const noexcept=0;
                /**
                 * @brief Get the Required Hash Alg Id object
                 * Get an ID of hash algorithm required by current signature algorithm.
                 * @return CryptoPrimitiveId::AlgId 
                 */
                //virtual AlgId GetRequiredHashAlgId () const noexcept=0;

            };
        }
    }
}
#endif

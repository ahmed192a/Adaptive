#pragma once
#include <memory>
#include <iostream>
#include "../../common/base_id_types.hpp"
#include "crypto_primitive_id.hpp"
#include "ara/crypto/common/vendor_specific_algorithm_identifier.hpp"
//#include "../concrete_crypto_provider.hpp"


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
            class CryptoPrId : public CryptoPrimitiveId
            {
                CryptoPrimitiveId::AlgId id;
                std::string name;
                public:

                //const ara::core::StringView Sv ;
                const std::string Sv2 ;
                

                /*
                * SWS_CRYPT_20644
                * Unique smart pointer of the constant interface.
                */
                using Uptrc = std::unique_ptr<const CryptoPrId>;
                /*
                * SWS_CRYPT_20643
                * Unique smart pointer of the interface.
                * smart pointer to allocate and free in memory automatically 
                * and cant make a copy from it
                */
                using Uptr = std::unique_ptr<CryptoPrId>;
                /**
                 * @brief Construct a new Convert To Alg Id object
                 * 
                 * @param primitiveName 
                 */
                int ConvertToAlgId (std::string primitiveName);
                /**
                 * @brief Construct a new Crypto Pr Id object
                 * 
                 * @param Sv 
                 */
                CryptoPrId(const std::string &Sv);
                /**
                 * SWS_CRYPT_20652
                 * @brief Get the Primitive Id object
                 * Get vendor specific ID of the primitive.
                 * @return AlgId 
                 */
                
                AlgId GetPrimitiveId () const noexcept;
                /**
                 * SWS_CRYPT_20651
                 * @brief Get the Primitive Name object
                 * Get a unified name of the primitive. The crypto primitive name can be fully or partially specified
                 * (see "Crypto Primitives Naming Convention" for more details). The life-time of the returned
                 * StringView instance should not exceed the life-time of this CryptoPrimitiveId instance!
                 * @return const ara::core::StringView 
                 */
                const std::string GetPrimitiveName () const noexcept;
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
                virtual AlgId GetHashAlgId () const noexcept;
                /**
                 * @brief Get the Required Hash Alg Id object
                 * Get an ID of hash algorithm required by current signature algorithm.
                 * @return CryptoPrimitiveId::AlgId 
                 */
                virtual AlgId GetRequiredHashAlgId () const noexcept;

            };
        }
    }
}

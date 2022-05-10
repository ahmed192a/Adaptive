//#ifndef ARA_CRYPTO_CRYP_SECRETKEY_H_
//#define ARA_CRYPTO_CRYP_SECRETKEY_H_
#pragma once
#include "rest_use_obj.hpp"
#include "../../../core/result.hpp"
#include "../../common/mem_region.hpp"
//#include "crypto_obj.hpp"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {   class SecSeed;
            class SecretSeed : public RestUseObj
            {
                public:
                std::int64_t seed_len;
                //std::int64_t Seed_val;
                /**
                 * @brief Construct a new Secret Seed object
                 * 
                 */
                SecretSeed()=default;

                //SWS_CRYPT_23001
                /**
                 * @brief Unique smart pointer of a constant interface instance.
                 * 
                 */
                using Uptrc = std::unique_ptr<const SecretSeed>;

                //SWS_CRYPT_23002
                /**
                 * @brief Unique smart pointer of a volatile interface instance.
                 * 
                 */
                using Uptr = std::unique_ptr<SecretSeed>;

                //SWS_CRYPT_23003
                /**
                 * @brief Static mapping of this interface to specific value of CryptoObjectType enumeration.
                 * 
                 */
                const CryptoObjectType kObjectType = CryptoObjectType::kSecretSeed;
                
                //SWS_CRYPT_23011
                /**
                 * @brief Clone this Secret Seed object to new session object. Created object instance is session and 
                 * non-exportable, AllowedUsageFlags attribute of the "cloned" object is identical to this attribute
                 * of the source object! If size of the xorDelta argument is less than the value size of this seed
                 * then only correspondent number of leading bytes of the original seed should be XOR-ed, but
                 * the rest should be copied without change. If size of the xorDelta argument is larger than the
                 * value size of this seed then extra bytes of the xorDelta should be ignored.
                 * 
                 * @return ara::core::Result<SecretSeed::Uptr> 
                 */
                virtual SecretSeed::Uptr Clone (ReadOnlyMemRegion xorDelta) const noexcept=0;

                //SWS_CRYPT_23012
                /**
                 * @brief Set value of this seed object as a "jump" from an initial state to specified number of steps,
                 * according to "counting" expression defined by a cryptographic algorithm associated with this object.
                 *  steps may have positive and negative values that correspond to forward and backward
                 * direction of the "jump" respectively, but 0 value means only copy from value to this seed object.
                 * @param from 
                 * @param steps 
                 * @return ara::core::Result<void> 
                 */
                virtual void JumpFrom (const SecSeed &from,std::int64_t steps) noexcept=0;

                //SWS_CRYPT_23014
                /**
                 * @brief Set value of this seed object as a "jump" from it’s current state to specified number of steps,
                 * according to "counting" expression defined by a cryptographic algorithm associated with this
                 * object. steps may have positive and negative values that correspond to forward and backward
                 * direction of the "jump" respectively, but 0 value means no changes of the current seed value.
                 * 
                 * @param steps 
                 * @return SecretSeed& 
                 */
                virtual SecretSeed& Jump (std::int64_t steps) noexcept=0;


                //SWS_CRYPT_23013
                /**
                 * @brief Set next value of the secret seed according to "counting" expression defined by a cryptographic algorithm associated with this object.
                 * 
                 * @return SecretSeed& 
                 */
                virtual SecretSeed& Next () noexcept=0;

                //SWS_CRYPT_23015
                /**
                 * @brief XOR value of this seed object with another one and save result to this object. If seed sizes in
                 * this object and in the source argument are different then only correspondent number of leading
                 * bytes in this seed object should be updated.
                 * 
                 * @param source 
                 * @return SecretSeed& 
                 */
                virtual SecretSeed& operator^= (const SecSeed &source) noexcept=0;
                
                //SWS_CRYPT_23016
                /**
                 * @brief XOR value of this seed object with provided memory region and save result to this object. If
                 * seed sizes in this object and in the source argument are different then only correspondent
                 * number of leading bytes of this seed object should be updated
                 * 
                 * @param source 
                 * @return SecretSeed& 
                 */
               virtual SecretSeed& operator^= (ReadOnlyMemRegion source) noexcept=0;

            };

        }
    }
}

//#endif

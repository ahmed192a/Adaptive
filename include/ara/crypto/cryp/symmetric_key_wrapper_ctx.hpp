#ifndef ARA_CRYPTO_SYMMETRIC_KEY_WRAPPER_CTX_H
#define ARA_CRYPTO_SYMMETRIC_KEY_WRAPPER_CTX_H

#include "cryobj/secret_seed.hpp"
#include "cryobj/symmetric_key.hpp"
#include "../common/mem_region.hpp"
#include "../common/base_id_types.hpp"
#include "../../core/result.hpp"
#include "crypto_context.hpp"
#include "cryobj/restricted_use_object.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {
            
            class SymmetricKeyWrapperCtx : public CryptoContext
            { 
            public:
                /*Unique smart pointer of the interface*/
                using Uptr = std::unique_ptr<SymmetricKeyWrapperCtx>;
                
                /*Calculate size of the wrapped key in bytes from original key length in bits. This method can be
                 *useful for some implementations different from RFC3394/RFC5649*/
                virtual std::size_t CalculateWrappedKeySize (std::size_t keyLength) const noexcept=0;
                
                /*Get maximum length of the target key supported by the implementation. This method can be
                 *useful for some implementations different from RFC3394/RFC5649*/
                virtual std::size_t GetMaxTargetKeyLength () const noexcept=0;
                
                /*Get expected granularity of the target key (block size). If the class implements RFC3394 
                 *(KW without padding) then this method should return 8 (i.e. 8 octets = 64 bits). If the class
                 *implements RFC5649 (KW with padding) then this method should return 1 (i.e. 1 octet = 8 bits)*/
                virtual std::size_t GetTargetKeyGranularity () const noexcept=0;
                
                /*Clear the crypto context*/
                virtual ara::core::Result<void> Reset () noexcept=0;
                
                /*Set (deploy) a key to the symmetric key wrapper algorithm context*/
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform) noexcept=0;
                
                /*Execute the "key unwrap" operation for provided BLOB and produce a Key object of expected type*/
                template <typename ExpectedKey>ara::core::Result<typename ExpectedKey::Uptrc> UnwrapConcreteKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) noexcept;
                
                /*Execute the "key unwrap" operation for provided BLOB and produce Key object. This method should be 
                 *compliant to RFC3394 or RFC5649, if implementation is based on the AES block cipher and applied to 
                 *an AES key. The created Key object has following attributes: session and non-exportable (because it 
                 *was imported without meta-information)! SymmetricKey may be unwrapped in following way: 
                 *SymmetricKey::Uptrc key = SymmetricKey::Cast(UnwrapKey(wrappedKey, ...)); PrivateKey may be unwrapped 
                 *in following way: PrivateKey::Uptrc key = PrivateKey::Cast(UnwrapKey(wrappedKey, ...)); 
                 *In both examples the Cast() method may additionally throw the BadObjectTypeException if an actual type 
                 *of the unwrapped key differs from the target one!*/
                virtual ara::core::Result<RestrictedUseObject::Uptrc> UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) const noexcept=0;
                
                /*Execute the "key unwrap" operation for provided BLOB and produce SecretSeed object. This method should 
                 *be compliant to RFC3394 or RFC5649, if implementation is based on the AES block cipher and applied to 
                 *an AES key material. The created SecretSeed object has following attributes: session and non-exportable 
                 *(because it was imported without meta-information)*/
                virtual ara::core::Result<SecretSeed::Uptrc> UnwrapSeed (ReadOnlyMemRegion wrappedSeed, AlgId targetAlgId, SecretSeed::Usage allowedUsage) const noexcept=0;
                
                /*Execute the "key wrap" operation for the provided key material. This method should be compliant to 
                 *RFC3394 or RFC5649, if an implementation is based on the AES block cipher and applied to an AES key. 
                 *Method CalculateWrappedKeySize() can be used for size calculation of the required output buffer*/
                virtual std::vector<byte> WrapKeyMaterial (const RestrictedUseObject &key) const noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> WrapKeyMaterial (const RestrictedUseObject &key) const noexcept=0;
            };
        }
    }
}


#endif

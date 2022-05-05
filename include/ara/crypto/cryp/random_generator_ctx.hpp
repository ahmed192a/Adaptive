#ifndef ARA_CRYPTO_RANDOM_GENERATOR_CTX_H
#define ARA_CRYPTO_RANDOM_GENERATOR_CTX_H

#include "crypto_context.hpp"
#include "../common/base_id_types.hpp"
#include "ara/crypto/cryp/cryobj/secret_seed.hpp"
#include "ara/crypto/common/mem_region.hpp"
#include "ara/core/result.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {
            enum class RandomGeneratorCtx_Status : std::uint8_t 
            {
                notInitialized ,   
                initialized ,
                Seeded        //if seed() or setkey has been called
            };
            
            class RandomGeneratorCtx : public CryptoContext
            {
            public:
                /*Shared smart pointer of the interface*/
                using Uptr = std::unique_ptr<RandomGeneratorCtx>;
                
                /*Update the internal state of the RNG by mixing it with the provided additional entropy. This
                 *method is optional for implementation. An implementation of this method may "accumulate"
                 *provided entropy for future use*/
                virtual bool AddEntropy (ReadOnlyMemRegion entropy) noexcept=0;
                
                /*Return an allocated buffer with a generated random sequence of the requested size*/
                virtual std::vector<ara::crypto::byte> Generate (std::uint32_t count) noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> Generate (std::uint32_t count) noexcept=0;
                
                /*Set the internal state of the RNG using the provided seed*/
                virtual bool Seed (ReadOnlyMemRegion seed) noexcept=0;
                
                /*Set the internal state of the RNG using the provided seed*/
                virtual bool Seed (const SecretSeed &seed) noexcept=0;
                
                /**/
                virtual bool SetKey (const SymmetricKey &key) noexcept=0;
            };
        }
    }
}


#endif

#ifndef ARA_CRYPTO_PRNG_H
#define ARA_CRYPTO_PRNG_H

#include "ara/crypto/cryp/random_generator_ctx.hpp"
#include <random>
#include <vector>

namespace ara {
    namespace crypto {
        namespace cryp {

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            class SecretSeed {
            public:
                uint32_t Seed;

            };
            class SymmetricKey {
            public:
                uint32_t Seed;
            };

            class ReadOnlyMemRegion {};

            //////////////////////////////////////////////////////////////

            class PRNG : public RandomGeneratorCtx {
            private:
                std::default_random_engine RNG;
                //SecretSeed Seed;
            public:
                PRNG();
                bool AddEntropy(ReadOnlyMemRegion entropy);
                std::vector<byte> Generate(std::uint32_t count);
                //bool Seed (ReadOnlyMemRegion seed) noexcept=0;
                bool Seed(const SecretSeed& seed);
                bool SetKey(const SymmetricKey& key);
            };
        } // namespace cryp
    } // namespace crypto 
} // namespace ara

#endif // ARA_CRYPTO_PRNG_H

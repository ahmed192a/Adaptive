#ifndef ARA_CRYPTO_PRNG_H
#define ARA_CRYPTO_PRNG_H

#include "random_generator_ctx.hpp"
#include <random>
#include <vector>

namespace ara {
    namespace crypto {
        namespace cryp {

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            /*
            class SecretSeed {
            public:
                uint32_t Seed;

            };
            class SymmetricKey {
            public:
                uint32_t Seed;
            };

            class ReadOnlyMemRegion {};
            */
            //////////////////////////////////////////////////////////////
            class ConcreteCryptoProvider;
            class PRNG : public RandomGeneratorCtx {
            private:
                std::default_random_engine RNG;
                //SecretSeed Seed;
                ConcreteCryptoProvider* myprovider;
            public:
                /*
                 * PRNG Constructor
                 */
                PRNG(ConcreteCryptoProvider* a);
                PRNG();
                /***********************************************************************/
                /*****          inherited CyrptoContext virtual functions          *****/
                /***********************************************************************/

		///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
                ///@return: true if initialized and false if not 
		bool IsInitialized()const noexcept;

		///@brief: inherited from CryptoContext,references the CryptoPrimitivId instance containing instance identification 
                ///@param[in]: none
                ///@return: pointer references the CryptoPrimitivId instance of the context
		CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

                ///@brief: inherited from CryptoContext, references the CryptoProvider instance containing instance identification 
                ///@param[in]: none
                ///@return: pointer references the cryptoProvider instance of the context
                ConcreteCryptoProvider& MyProvider() const noexcept;
                
                /*************************************************************************/
                /*****         RandomGeneratorCtx inherited virtual functions        *****/
                /*************************************************************************/
                
                /*Update the internal state of the RNG by mixing it with the provided additional entropy. This
                 *method is optional for implementation. An implementation of this method may "accumulate"
                 *provided entropy for future use*/
                bool AddEntropy(ReadOnlyMemRegion entropy) noexcept;
                
                /*Return an allocated buffer with a generated random sequence of the requested size*/
                std::vector<byte> Generate(std::uint32_t count) noexcept;
                //bool Seed (ReadOnlyMemRegion seed) noexcept;
                /*Set the internal state of the RNG using the provided seed*/
                bool Seed(const SecSeed& seed) noexcept;
                
                bool SetKey(const SymmetricKey& key) noexcept;
            };
        } // namespace cryp
    } // namespace crypto 
} // namespace ara

#endif // ARA_CRYPTO_PRNG_H

#ifndef ARA_CRYPTO_HMAC_H
#define ARA_CRYPTO_HMAC_H

#include "message_authn_code_ctx.hpp"


namespace ara {
    namespace crypto {
        namespace cryp {

            
            //This partition is only used for testing

            ///////////////////////////////////////////////////////
            // dummy definitions that will be removed later
            class HashFunctionCtx {
                public:
                using Uptr = std::unique_ptr<HashFunctionCtx>;
            };

            //////////////////////////////////////////////////////////////

            class HMAC : public MessageAuthnCodeCtx {

                private:
                // pointer to the hash function context used to implement this algorithm
                HashFunctionCtx::Uptr hashFunction;


                public:
                // implementation of the CyrptoContext virtual function
                bool IsInitialized();

                void Reset() noexcept;
                //void SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) noexcept;



                Signature::Uptrc Finish(bool makeSignatureObject = false) noexcept;
            };






        } // namespace cryp
    } // namespace crypto
} // namespace ara

#endif // ARA_CRYPTO_HMAC_H
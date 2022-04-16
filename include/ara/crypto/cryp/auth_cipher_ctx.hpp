#ifndef ARA_CRYPTO_HMAC_H
#define ARA_CRYPTO_HMAC_H

#include "crypto_context.hpp"
#include"message_authn_code_ctx.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            enum class AuthCipherCtx_Status : std::uint8_t {
                notInitialized = 0,
                initialized = 1,
                started = 2,

            };
            class AuthCipherCtx : public CryptoContext
            {
                using Uptr = std::unique_ptr<AuthCipherCtx>;
            protected:
                // this pointer will point to the resulting mac context of the data
                MessageAuthnCodeCtx::Uptr mac_ptr;
            public:


            };
        }
    }
}


#endif
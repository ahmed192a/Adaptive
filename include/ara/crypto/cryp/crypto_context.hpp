#ifndef ARA_CRYPTO_CRYPTO_CONTEXT_H
#define ARA_CRYPTO_CRYPTO_CONTEXT_H

#include <iostream>
#include <memory>

#include "../cryp/cryobj/crypto_primitive_id.hpp"
#include "../cryp/cryobj/crypto_pr_id.hpp"
#include "../cryp/crypto_provider.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            class CryptoContext
            {
            public:
				using AlgId = CryptoAlgId;
				/* Destructor */
				virtual ~CryptoContext() noexcept = default;

				/*Return CryptoPrimitivId instance containing instance identification */
				virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept = 0;

				/*Check if the crypto context is already initializedand ready to use */
				virtual bool IsInitialized() const noexcept = 0;

				/* Copy - assign another CryptoContext to this instance */
				CryptoContext& operator= (const CryptoContext & other) = default;

				/*/Move - assign another CryptoContext to this instance */
				CryptoContext& operator= (CryptoContext && other) = default;

				/* Get a reference to Crypto Provider of this context*/
				virtual CryptoProvider& MyProvider() const noexcept = 0;

            };

        }
    }
}

#endif

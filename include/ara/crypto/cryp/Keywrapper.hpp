#ifndef ARA_CRYPTO_KEY_WRAPPER_H
#define ARA_CRYPTO_KEY_WRAPPER_H

#include <string>
#include "include/ara/crypto/cryp/symmetric_key_wrapper_ctx.hpp"
#include "include/ara/crypto/cryp/PRNG.hpp"

namespace ara {
	namespace crypto {
		namespace cryp {
			class Keywrapper : public SymmetricKeyWrapperCtx
			{
			private :
				byte x;
				uint32_t key_length;
				uint32_t wrapped_key_size;
				uint32_t Max_KEKLength = 256; //Max key length supported by the AES (in bits) 
				uint32_t KEK_Length = 128;
				SymmetricKey Key;
				std::string decToHexa(int n);
			public :
				Keywrapper();
				std::size_t CalculateWrappedKeySize(std::size_t keyLength);
				std::size_t GetMaxTargetKeyLength();
				std::size_t GetTargetKeyGranularity();
				ara::core::Result<void> Reset();
				//void SetKey(const SymmetricKey& key, CryptoTransform transform);
			};
		}
	}
}

#endif //ARA_CRYPTO_KEY_WRAPPER_H
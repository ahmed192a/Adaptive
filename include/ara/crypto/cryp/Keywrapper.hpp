#ifndef ARA_CRYPTO_KEY_WRAPPER_H
#define ARA_CRYPTO_KEY_WRAPPER_H

/*
	Cryptopp Header files for downloading the library use the following commands "ubuntu terminal":
	sudo apt-get update 
	 sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
*/
#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/cryptlib.h>
#include <crypto++/rijndael.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>

#include <vector>
#include <string>
#include "include/ara/crypto/cryp/symmetric_key_wrapper_ctx.hpp"
#include "include/ara/crypto/cryp/PRNG.hpp"


using namespace std;
using namespace CryptoPP;

namespace ara {
	namespace crypto {
		namespace cryp {
			enum class AES_Wrapper_Status : std::uint8_t 
			{
				notInitialized = 0,
                		initialized = 1
			};
			
			class Keywrapper : public SymmetricKeyWrapperCtx
			{
			private :
			size_t key_length = 128;
			size_t wrapped_key_size;
			size_t Max_KEY_Length = 128;//Max input key length(AKA plaintext) supported by the AES (in bits)
			size_t KEK_Length = 128; // in bits
			size_t Block_size = 16;
			SymmetricKey Key;
			vector<byte> hexToASCII(string hex);
			//std::string decToHexa(int n);
			public :
			Keywrapper();
			std::size_t CalculateWrappedKeySize(std::size_t keyLength);
			std::size_t GetMaxTargetKeyLength();
			std::size_t GetTargetKeyGranularity();
			ara::core::Result<void> Reset();
			void SetKey(const SymmetricKey& key, CryptoTransform transform);
			vector<byte>  WrapKeyMaterial (const RestrictedUseObject &key);
			RestrictedUseObject::Uptrc UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage);
			};
		}
	}
}

#endif //ARA_CRYPTO_KEY_WRAPPER_H

#ifndef ARA_CRYPTO_KEY_WRAPPER_H
#define ARA_CRYPTO_KEY_WRAPPER_H

/*
	Cryptopp Header files for downloading the library use the following commands "ubuntu terminal":
	sudo apt-get update 
	 sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils
*/
#include "cryptopp/aes.h"
#include <modes.h> // crypto++
#include <cryptlib.h> // crypto++
#include <rijndael.h> // crypto++
#include <files.h> // crypto++
#include <hex.h> // crypto++

#include <vector>
#include <string>
#include "symmetric_key_wrapper_ctx.hpp"
#include "PRNG.hpp"


using namespace std;
using namespace CryptoPP;

namespace ara {
	namespace crypto {
		namespace cryp {
			
			class Keywrapper : public SymmetricKeyWrapperCtx
			{
			private :
			size_t key_length = 128;
			size_t wrapped_key_size;
			size_t Max_KEY_Length = 128;//Max input key length(AKA plaintext) supported by the AES (in bits)
			size_t KEK_Length = 128; // in bits
			size_t Block_size = 16;
			SymmetricKey Key;
			vector<byte> hexToASCII(string hex) const;
			//std::string decToHexa(int n);
			public :
			Keywrapper();
			/***********************************************************************/
			/*****          inherited CyrptoContext virtual functions          *****/
			/***********************************************************************/

			///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
			///@return: true if initialized and false if not 
			bool IsInitialized() const noexcept;

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
			std::size_t CalculateWrappedKeySize(std::size_t keyLength)const noexcept;
			//std::size_t GetMaxTargetKeyLength() noexcept;
			//std::size_t GetTargetKeyGranularity() noexcept;
			void Reset() noexcept;
			void SetKey(const SymmetricKey& key, CryptoTransform transform) noexcept;
			vector<byte>  WrapKeyMaterial (const SymmetricKey &key) const noexcept;
			SymmetricKey::Uptr UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) const noexcept;
			};
		}
	}
}

#endif //ARA_CRYPTO_KEY_WRAPPER_H

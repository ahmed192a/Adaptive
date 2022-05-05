#ifndef ARA_CRYPTO_SYMMETRIC_CIPHER_H
#define ARA_CRYPTO_SYMMETRIC_CIPHER_H

#include "symmetric_block_cipher_ctx.hpp"
#include "cryptlib.h"
#include "rijndael.h"
#include "modes.h"
#include "files.h"
#include "hex.h"
#include <iostream>
#include <string>

namespace ara {
    namespace crypto {
        namespace cryp {

            class SymmetricCipher : public SymmetricBlockCipherCtx
            { 
            private:
                ///@brief a pointer stores the instance of the crypto provider of the authentication context
                CryptoProvider *myProvider;

                ///@breif: the transformation to be implemented in the Algorithm (encryption/decryption)
                CryptoTransform Alg_transformation;
                
                ///@breif: the key to be used in the Algorithm to encrypt/decrypt the provided data
                SymmetricKey Alg_key;

                ///@breif: a flag to indicate whether Set_Key has been called or not yet
                bool Key_is_Set;
            
            public:
                ///@brief constructor
                SymmetricCipher(CryptoProvider *Provider);
                
                ///@brief destructor
                ~SymmetricCipher() noexcept = default;

                /***********************************************************************/
                /************** inherited CyrptoContext virtual functions **************/
                /***********************************************************************/

				///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
                ///@return: true if initialized and false if not 
				bool IsInitialized();

				///@brief: inherited from CryptoContext,references the CryptoPrimitivId instance containing instance identification 
                ///@param[in]: none
                ///@return: pointer references the CryptoPrimitivId instance of the context
				CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept;

                ///@brief: inherited from CryptoContext, references the CryptoProvider instance containing instance identification 
                ///@param[in]: none
                ///@return: pointer references the cryptoProvider instance of the context
                CryptoProvider& MyProvider() const noexcept;
                
                /*************************************************************************/
                /***** symmetric_block_cipher_ctx inherited virtual functions *****/
                /*************************************************************************/
                
                /*Get the kind of transformation configured for this context: kEncrypt or kDecrypt*/
                CryptoTransform GetTransformation () const noexcept;
                
                /*Process (encrypt / decrypt) an input block according to the cryptor configuration*/
                std::vector<byte> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept;
                //ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;
                
                /*Processe provided blocks without padding. The in and out buffers must have same size and
                 *this size must be divisible by the block size (see GetBlockSize()). Pointers to the input and
                 *output buffers must be aligned to the block-size boundary!*/
                std::vector<byte> Process_Blocks (ReadOnlyMemRegion in) const noexcept;
                //ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlocks (ReadOnlyMemRegion in) const noexcept=0;
                
                /*Clear the crypto context*/
                void Reset () noexcept;
                
                /*Set (deploy) a key to the symmetric algorithm context*/
                void SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept;
                //ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept;
            };
        }
    }
}
#endif
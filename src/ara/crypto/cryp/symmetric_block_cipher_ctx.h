#ifndef ARA_CRYPTO_SYMMETRIC_BLOCK_CIPHER_CTX_H
#define ARA_CRYPTO_SYMMETRIC_BLOCK_CIPHER_CTX_H

#include "crypto_context.h"
#include <vector>
#include "cryobj/symmetric_key.h"
#include "../common/mem_region.h"
//#include "../common/base_id_types.h"
//#include "../common/vendor_specific_algorithm_identifier.h"

namespace ara {
namespace crypto {
        namespace cryp {

            ///@brief: enumeration representing the state of the Symmetric Block Cipher context
            enum class SymmetricBlockCipher_Status : std::uint8_t {
                notInitialized,   
                initialized
            };

            class SymmetricBlockCipherCtx: public CryptoContext
            { 
            protected:
                ///@brief: the current status of the Symmetric Block Cipher context
                SymmetricBlockCipher_Status status;
            
            public:
                /*Unique smart pointer of the interface*/
                using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;
                
                /*Get the kind of transformation configured for this context: kEncrypt or kDecrypt*/
                virtual CryptoTransform GetTransformation () const noexcept=0;
                
                /*Indicate that the currently configured transformation accepts only complete blocks of input data*/
                bool IsMaxInputOnly () const noexcept;
                //ara::core::Result<bool> IsMaxInputOnly () const noexcept;
                
                /*Indicate that the currently configured transformation can produce only complete blocks of output data*/
                bool IsMaxOutputOnly () const noexcept;
                //ara::core::Result<bool> IsMaxOutputOnly () const noexcept;
                
                /*Process (encrypt / decrypt) an input block according to the cryptor configuration*/
                virtual std::vector<uint8_t> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;
                
                /*Processe provided blocks without padding. The in and out buffers must have same size and
                 *this size must be divisible by the block size (see GetBlockSize()). Pointers to the input and
                 *output buffers must be aligned to the block-size boundary!*/
                //virtual std::vector<uint8_t> Process_Blocks (ReadOnlyMemRegion in) const noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlocks (ReadOnlyMemRegion in) const noexcept=0;
                
                /*Clear the crypto context*/
                virtual void Reset () noexcept=0;
                
                /*Set (deploy) a key to the symmetric algorithm context*/
                virtual void SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0;
                //virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0;
            };
        }
    }
}
#endif
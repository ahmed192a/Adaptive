#ifndef ARA_CRYPTO_SYMMETRIC_BLOCK_CIPHER_CTX_H
#define ARA_CRYPTO_SYMMETRIC_BLOCK_CIPHER_CTX_H

#include "crypto_context.hpp"
//#include "crypto_service.hpp"

#include "../common/mem_region.hpp"
#include "../../core/result.hpp"

//#include "ara/crypto/common/mem_region.hpp"
//#include "ara/core/result.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            class SymmetricBlockCipherCtx : public CryptoContext
            { 
            public:
                /*Unique smart pointer of the interface*/
                using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;
                
                /*Get CryptoService instance*/
                //virtual CryptoService::Uptr GetCryptoService () const noexcept=0;
                
                /*Get the kind of transformation configured for this context: kEncrypt or kDecrypt*/
                virtual CryptoTransform GetTransformation () const noexcept=0;
                
                /*Indicate that the currently configured transformation accepts only complete blocks of input data*/
                ara::core::Result<bool> IsMaxInputOnly () const noexcept;
                
                /*Indicate that the currently configured transformation can produce only complete blocks of output data*/
                ara::core::Result<bool> IsMaxOutputOnly () const noexcept;
                
                /*Process (encrypt / decrypt) an input block according to the cryptor configuration*/
                virtual std::vector<byte> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte>> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;
                
                /*Process (encrypt / decrypt) an input block according to the cryptor configuration. This method
                 *sets the size of the output container according to actually saved value! Encryption with
                 *(suppressPadding == true) expects what: in.size() == GetMaxInputSize(true) && out.capacity() >= GetMaxOutputSize(true). 
                 *Encryption with (suppressPadding == false) expects what:
                 *in.size() <= GetMaxInputSize(false) && in.size() > 0 && out.capacity() >= GetMaxOutput
                 *Size(false). Decryption expects what: in.size() == GetMaxInputSize() && out.capacity() >= GetMaxOutputSize(suppressPadding).
                 *The case (out.capacity() < GetMaxOutputSize()) should be used with caution, only if you are strictly 
                 *certain about the size of the output data! In case of (suppressPadding == true) the actual size of 
                 *plain text should be equal to full size of the plain data block (defined by the algorithm)!*/
                virtual std::vector<byte> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept;
                //template <typename Alloc = <implementation-defined>> ara::core::Result<ByteVector<Alloc>> ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept;
                
                /*Processe provided blocks without padding. The in and out buffers must have same size and
                 *this size must be divisible by the block size (see GetBlockSize()). Pointers to the input and
                 *output buffers must be aligned to the block-size boundary!*/
                virtual std::vector<byte> Process_Blocks (ReadOnlyMemRegion in) const noexcept=0;
                //virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlocks (ReadOnlyMemRegion in) const noexcept=0;
                
                /*Clear the crypto context*/
                virtual void Reset () noexcept=0;
                
                /*Set (deploy) a key to the symmetric algorithm context*/
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0;
            };
        }
    }
}


#endif
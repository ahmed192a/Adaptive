/**
 * @file auth_cipher_ctx.hpp
 * @author
 * @brief  ara::crypto::cryp::AuthCiphetCtx class interface
 * @version R20-11
 *****************************************************************/


#ifndef ARA_CRYPTO_AUTH_CIPHER_CTX_H
#define ARA_CRYPTO_AUTH_CIPHER_CTX_H

#include "crypto_context.hpp"
#include"message_authn_code_ctx.hpp"
#include "symmetric_block_cipher_ctx.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {

            /// @brief: enumeration represents the state of the Authentication Cipher context
            enum class AuthCipherCtx_Status : std::uint8_t {
                notInitialized = 0,
                initialized = 1,
                started = 2,

            };
            class AuthCipherCtx : public CryptoContext
            {
            protected:

                /// @brief: the current status of the authentication context
                AuthCipherCtx_Status status = AuthCipherCtx_Status::notInitialized;
                
                //@brief a pointer stores the instance of the crypto provider of the authentication context
                CryptoProvider* myCryptoProvider;

            public:


                /// @brief: Unique smart pointer of this interface => AuthCipherCtx
                using Uptr = std::unique_ptr<AuthCipherCtx>;
                
                /// @brief: Compare the calculated digest against an expected signature object
                /// @param[in]: expected => the signature object containing an expected digest value
                /// @return: true if the compared values are identical, otherwise false
                virtual bool Check(const Signature& expected) const noexcept = 0;

                //virtual BlockService::Uptr GetBlockService() const noexcept = 0;
                
                /// @brief: Get the kind of transformation configured for this context whether kEncrypt or kDecrypt
                /// @param[in]: none
                /// @return: CryptoTransform => represents the types of the cryptographic transformations 
                virtual CryptoTransform GetTransformation() const noexcept = 0;

                /*template <typename Alloc = <implementation - defined>>
                ara::core::Result<ByteVector<Alloc> > GetDigest(std::size_t offset = 0) const noexcept;*/

                ///@brief: Get maximal supported size of associated public data
                ///@param[in]: none
                ///@return: std::uint64_t => the maximal supported size of associated public data in bytes
                virtual std::uint64_t GetMaxAssociatedDataSize() const noexcept = 0;

                ///@brief:The input buffer will be overwritten by the processed message. This function is the final 
                //call, i.e.all associated data must have been already provided. The function will check 
                //the authentication tag and only return the processed data if the tag is valid
                ///@param[in]: in => the input buffer containing the full message
                //             expectedTag => pointer to read only mem region
                virtual std:: vector<byte>  ProcessConfidentialData(ReadOnlyMemRegion in, ReadOnlyMemRegion expectedTag = nullptr) noexcept = 0;

                ///@breif:The input buffer will be overwritten by the processed message After this method is called 
                //no additional associated data may be updated
                //@param[in]:inOut=> the input buffer containing the full message
                //          expectedTag => pointer to read only mem region
                virtual void ProcessConfidentialData(ReadWriteMemRegion inOut, ReadOnlyMemRegion expectedTag = nullptr) noexcept = 0;

                /// @brief: resets the context
                virtual void Reset() noexcept = 0;

                ///@brief: Set a key to the authenticated cipher symmetric algorithm context
                ///@param[in]: key =>the source key object to be set
                virtual void SetKey(const SymmetricKey& key,CryptoTransform transform = CryptoTransform::kEncrypt) noexcept = 0;

                ///@brief: Initialize the context for a new data processing or generation
                ///@param[in]: iv => an optional Initialization Vector (IV) or "nonce" value
                virtual void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept = 0;

                ///@brief: Initialize the context for a new data processing or generation
                ///@param[in]: iv => an optional Initialization Vector (IV) or "nonce" value
                virtual void Start(const SecretSeed& iv) noexcept = 0;

                ///@brief: Update the digest calculation by the specified RestrictedUseObject.
                ///@param[in]: in => the part of input message that should be processed
                virtual void UpdateAssociatedData(const RestrictedUseObject& in) noexcept = 0;

                ///@brief: Update the digest calculation by a new chunk of associated data
                ///@param[in]: in => the part of input message that should be processed
                virtual void UpdateAssociatedData(ReadOnlyMemRegion in) noexcept = 0;

                ///@brief: Update the digest calculation by the specified Byte
                ///@param[in]: a byte value that is a part of input message
                virtual void UpdateAssociatedData(std::uint8_t in) noexcept = 0;



            };
        }
    }
}


#endif
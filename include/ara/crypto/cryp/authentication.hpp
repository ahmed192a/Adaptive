//#ifndef  ARA_CRYPTO_AUTHENTICATION_H
//#define  ARA_CRYPTO_AUTHENTICATION_H
#pragma once
#include "auth_cipher_ctx.hpp"
#include "HMAC.hpp"
#include "symmetric_cipher.hpp"

namespace ara {
    namespace crypto {
        namespace cryp {


			class Authentication : public AuthCipherCtx
			{
            private:

                ///@brief: pointer references the used mac context to authenticate the data
                MessageAuthnCodeCtx::Uptr macPtr = std::make_unique<HMAC>();

                ///@brief: pointer refetences the used symmetric block cipher context to encrypt the data
                SymmetricBlockCipherCtx::Uptr blockCipherPtr = std::make_unique<SymmetricCipher>();

                ///@breif: a flag to state whether ara::crypto::cryp::AuthCipherCtx::SetKey has been called before or not
                int Key_is_Set;

                //@breif: configured transformation direction of AuthCipherCtx
                CryptoTransform Transform_set;

			public:
                
                /// @brief constructor
                Authentication(CryptoProvider* myProvider, CryptoTransform direction);
                
                /// @brief destructor
                ~Authentication() noexcept = default;

                           /***********************************************************************/
				           /***** implementation of inherited CyrptoContext virtual functions *****/
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
                          /***** implementation of auth_cipher_ctx inherited virtual functions *****/
                          /*************************************************************************/

                //virtual BlockService::Uptr GetBlockService() const noexcept = 0;

                /// @brief: Get the kind of transformation configured for this context whether kEncrypt or kDecrypt
                /// @param[in]: none
                /// @return: CryptoTransform => represents the types of the cryptographic transformations 
                CryptoTransform GetTransformation() const noexcept;

                //template <typename Alloc = <implementation - defined>>
                std::vector <byte> GetDigest(std::size_t offset = 0) const noexcept;

                ///@brief: Get maximal supported size of associated public data
                ///@param[in]: none
                ///@return: std::uint64_t => the maximal supported size of associated public data in bytes
                //std::uint64_t GetMaxAssociatedDataSize() const noexcept;

                ///@brief:The input buffer will be overwritten by the processed message. This function is the final 
                //call, i.e.all associated data must have been already provided. The function will check 
                //the authentication tag and only return the processed data if the tag is valid
                ///@param[in]: in => the input buffer containing the full message
                //             expectedTag => pointer to read only mem region
                std::vector<byte>  ProcessConfidentialData (ReadOnlyMemRegion in, ReadOnlyMemRegion expectedTag) noexcept;

                ///@breif:The input buffer will be overwritten by the processed message After this method is called 
                //no additional associated data may be updated
                //@param[in]:inOut=> the input buffer containing the full message
                //          expectedTag => pointer to read only mem region
                void ProcessConfidentialData(ReadWriteMemRegion inOut, ReadOnlyMemRegion expectedTag) noexcept;

                /// @brief: resets the context
                void Reset() noexcept;

                ///@brief: Set a key to the authenticated cipher symmetric algorithm context
                ///@param[in]: key =>the source key object to be set
                void SetKey(const SymmetricKey& key, CryptoTransform transform = CryptoTransform::kEncrypt) noexcept;

                ///@brief: Initialize the context for a new data processing or generation
                ///@param[in]: iv => an optional Initialization Vector (IV) or "nonce" value
                void Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept;

                ///@brief: Initialize the context for a new data processing or generation
                ///@param[in]: iv => an optional Initialization Vector (IV) or "nonce" value
                void Start(const SecretSeed& iv) noexcept;

                ///@brief: Update the digest calculation by the specified RestrictedUseObject.
                ///@param[in]: in => the part of input message that should be processed
                void UpdateAssociatedData(const RestrictedUseObject& in) noexcept;

                ///@brief: Update the digest calculation by a new chunk of associated data
                ///@param[in]: in => the part of input message that should be processed
                void UpdateAssociatedData(ReadOnlyMemRegion in) noexcept;

                ///@brief: Update the digest calculation by the specified Byte
                ///@param[in]: a byte value that is a part of input message
                void UpdateAssociatedData(std::uint8_t in) noexcept;


			};

        }
    }
}










//#endif // ! ARA_CRYPTO_AUTHENTICATION_H

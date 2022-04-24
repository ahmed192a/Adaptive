#include "../../../../include/ara/crypto/cryp/authentication.hpp"

using namespace ara:: crypto;
using namespace ara::crypto::cryp;

///@brief: a constructor saves the instance of the crypto provider of the Authentication context
Authentication::Authentication(CryptoProvider* myProvider,CryptoTransform direction)
{
	//@ stores the crypto provider instance of the context in the member "myCryptoProvider" inherited from auth_cipher_ctx
	this-> myCryptoProvider = myProvider;

	//@ stored the transformation direction of the context in the member "Transform_set"
	this->Transform_set = direction;

	//@ set the status of the context as notInitialized
	this->status = AuthCipherCtx_Status::notInitialized;
}

                /***********************************************************************/
				/***** implementation of inherited CyrptoContext virtual functions *****/
				/***********************************************************************/

///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
bool Authentication :: IsInitialized()
{
	//@ return false if the context is not initialized
	if (this-> status == AuthCipherCtx_Status::notInitialized)
	{
		return false;
	}
	//@ return true if the context is initialized 
	else 
	{
		// It checks all required values, including: key value
		if (Key_is_Set)
			return true;
		else
			return false;
	}
}

///@brief: inherited function from CryptoContext, gets a reference to CryptoPrimitivId instance of this CryptoContext
CryptoPrimitiveId::Uptr Authentication:: GetCryptoPrimitiveId() const noexcept
{

}

///@brief: inherited function from CryptoContext, gets a reference to Crypto Provider instance of this CryptoContext
CryptoProvider&  Authentication:: MyProvider() const noexcept
{
	//@return pointer references the Crypto Provider instance of the context
	//return this-> (*myCryptoProvider) ;
	return *myCryptoProvider;
}
                /*************************************************************************/
                /***** implementation of auth_cipher_ctx inherited virtual functions *****/
                /*************************************************************************/

///@brief: Initialize the mac context of this authentication instance for a new data processing 
void Authentication:: Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept
{
	/*Initialize the context for a new data processing or generation (depending from the primitive iv)*/
	if ((this->status == AuthCipherCtx_Status::initialized) && (Key_is_Set)) {
		this->status == AuthCipherCtx_Status::started;
	}
}

///@brief: Initialize the mac context of this authentication instance  for a new data processing
void Authentication::Start(const SecretSeed& iv) noexcept
{
	/*Initialize the context for a new data processing or generation (depending from the primitive iv)*/
	if ((this->status == AuthCipherCtx_Status::initialized) && (Key_is_Set)) {
		this->status == AuthCipherCtx_Status::started;
	}
}

///@brief: Update the mac digest calculation by the specified RestrictedUseObject.
void Authentication::UpdateAssociatedData(const RestrictedUseObject& in) noexcept
{
	// UpdateAssociatedData raises kProcessingNotStarted error if digest calculation is not initiated by calling Start() method
	if (this->status == AuthCipherCtx_Status::started)
	{
		// update the digest through the Update function of the mac context in this authentication instance
		this->macPtr->Update(in);

		this->status == AuthCipherCtx_Status::updated;
	}
	
	//// UpdateAssociatedData raises error if ProcessConfedentialData has been already called 
	//if (this->status != AuthCipherCtx_Status:: processedData)
	//{
	//	// update the digest through the Update function of the mac context in this authentication instance
	//	this->macPtr->Update(in);
	//}

}

///@brief: Update the mac digest calculation by a new chunk of associated data
void Authentication::UpdateAssociatedData(ReadOnlyMemRegion in) noexcept
{
	// UpdateAssociatedData raises kProcessingNotStarted error if digest calculation is not initiated by calling Start() method
	if (this->status == AuthCipherCtx_Status::started)
	{
		// update the digest through the Update function of the mac context in this authentication instance
		this->macPtr->Update(in);

		this->status == AuthCipherCtx_Status::updated;
	}

	//// UpdateAssociatedData raises error if ProcessConfedentialData has been already called 
	//if (this->status != AuthCipherCtx_Status:: processedData)
	//{
	//	// update the mac digest through the Update function of the mac context in this authentication instance
	//	this->macPtr->Update(in);
	//}
}

///@brief: Update the mac digest calculation by the specified Byte
void Authentication:: UpdateAssociatedData(std::uint8_t in) noexcept
{
	// UpdateAssociatedData raises kProcessingNotStarted error if digest calculation is not initiated by calling Start() method
	if (this->status == AuthCipherCtx_Status::started)
	{
		// update the digest through the Update function of the mac context in this authentication instance
		this->macPtr->Update(in);

		this->status == AuthCipherCtx_Status::updated;
	}

	//// UpdateAssociatedData raises error if ProcessConfedentialData has been already called 
	//if (this->status != AuthCipherCtx_Status::processedData)
	//{
	//	// update the digest through the Update function of the mac context in this authentication instance
	//	this->macPtr->Update(in);
	//}
}

//Set (deploy) the same key to the authenticated cipher symmetric algorithm context as well as the Mac context
void Authentication::SetKey(const SymmetricKey & key, CryptoTransform transform = CryptoTransform::kEncrypt) noexcept
{
	if (((transform == CryptoTransform::kEncrypt) && (kAllowDataEncryption != NULL)) || ((transform == CryptoTransform::kDecrypt) && (kAllowDataDecryption != NULL)))
	{
		Key_is_Set = 1;
		Transform_set = transform;
		if (transform == CryptoTransform::kEncrypt) {
			this->macPtr->SetKey(key, CryptoTransform::kMacGenerate);
		}
		else if (transform == CryptoTransform::kDecrypt)
		{
			this->macPtr->SetKey(key, CryptoTransform::kMacVerify);
		}
		//@ set the status of the context as initialized
		this->status = AuthCipherCtx_Status::initialized;
	}

}
CryptoTransform Authentication::GetTransformation() const noexcept
{
	if (Key_is_Set) {
		return Transform_set;
	}
}
///@brief:The input buffer will be overwritten by the processed message. This function is the final 
//call, i.e.all associated data must have been already provided. The function will check 
//the authentication tag and only return the processed data if the tag is valid
std::vector<byte> Authentication:: ProcessConfidentialData(ReadOnlyMemRegion in, ReadOnlyMemRegion expectedTag = nullptr) noexcept
{
	// ProcessConfidentialData raises kProcessingNotStarted error if data processing is not initiated by calling Start() method
	if ((this->status == AuthCipherCtx_Status::started)|| (this->status == AuthCipherCtx_Status::updated))
	{
		/* If the transformation direction is kEncrypt, ProcessConfidentialData shall encrypt the provided plaintext data 
		and return the ciphertext */
		if (GetTransformation() == CryptoTransform::kEncrypt)
		{
			// vector of bytes to store the data after encryption 
			std::vector<byte> encryptedData;
			// encrypt the confidential data 
			encryptedData= this->blockCipherPtr->Process_Blocks(in);
			// Mac calculation should be updated by the confedential data
			this->macPtr->Update(in);
			//This function is the final call,all associated data must have been already provided, so finish the Mac context
			this->macPtr->Finish();
			//Update the stats of the auth_cipher context
			this->status = AuthCipherCtx_Status::processedData;
			// return the ciphertext
			return encryptedData;
		}
		/* If the transformation direction is kDecrypt,ProcessConfidentialData shall also decrypt the provided plaintext data
		and return the plaintext, only if the calculated MAC matches the provided expectedTag.*/ 
		else if (GetTransformation() == CryptoTransform::kDecrypt)
		{
			uint8_t counter=0;
			bool matching = true;
			std::vector<byte> DecreptedData;     // vector of bytes to store the data after decryption 
			std::vector<byte> calculatedDataMac; // vector of bytes to store the calculated MAC of the received data
			
			DecreptedData = this->blockCipherPtr->Process_Blocks(in);
			//Mac calculation should be updated by the confedential data
			this->macPtr->Update(DecreptedData);
			//This function is the final call,all associated data must have been already provided, so finish the Mac context
			macPtr->Finish();
			/* If the calculated MAC does not match the provided expectedTag, kAuthTagNotValid error shall be returned*/
			calculatedDataMac= this->macPtr->GetDigest();
			for (counter = 0; counter < calculatedDataMac.size(); counter++)
			{
				if (calculatedDataMac[counter] != expectedTag[counter])
				{
					matching = false;
					break;
				}
			}
			if (matching == true)
			{
				this->status == AuthCipherCtx_Status::processedData;
				return DecreptedData;
			}
			else
			{
				this->status == AuthCipherCtx_Status::processedData;
				return ;
			}
		}
	}
}

///@breif:The input buffer will be overwritten by the processed message After this method is called 
				//no additional associated data may be updated
void Authentication:: ProcessConfidentialData(ReadWriteMemRegion inOut, ReadOnlyMemRegion expectedTag = nullptr) noexcept
{
	// ProcessConfidentialData raises kProcessingNotStarted error if data processing is not initiated by calling Start() method
	if ((this->status == AuthCipherCtx_Status::started) || (this->status == AuthCipherCtx_Status::updated))
	{
		/* If the transformation direction is kEncrypt, ProcessConfidentialData shall encrypt the provided plaintext data
		and return the ciphertext */
		if (GetTransformation() == CryptoTransform::kEncrypt)
		{
			// vector of bytes to store the data after encryption 
			std::vector<byte> encryptedData;
			// encrypt the confidential data 
			encryptedData = this->blockCipherPtr->Process_Blocks(inOut);
			// Mac calculation should be updated by the confedential data
			this->macPtr->Update(inOut);
			//This function is the final call,all associated data must have been already provided, so finish the Mac context
			this->macPtr->Finish();
			//Update the state of the auth_cipher context
			this->status = AuthCipherCtx_Status::processedData;
			// overwrite the message buffer with the encrypted data
			inOut=encryptedData;
		}
		/* If the transformation direction is kDecrypt,ProcessConfidentialData shall also decrypt the provided plaintext data
		and return the plaintext, only if the calculated MAC matches the provided expectedTag.*/
		else if (GetTransformation() == CryptoTransform::kDecrypt)
		{
			uint8_t counter = 0;
			bool matching = true;
			std::vector<byte> DecreptedData;      // vector of bytes to store the data after decryption 
			std::vector<byte> calculatedDataMac;  // vector of bytes to store the calculated MAC of the received data

			DecreptedData = this->blockCipherPtr->Process_Blocks(inOut);
			//Mac calculation should be updated by the confedential data
			this->macPtr->Update(DecreptedData);
			//This function is the final call,all associated data must have been already provided, so finish the Mac context
			macPtr->Finish();
			/* If the calculated MAC does not match the provided expectedTag, kAuthTagNotValid error shall be returned*/
			calculatedDataMac = this->macPtr->GetDigest();
			for (counter = 0; counter < calculatedDataMac.size(); counter++)
			{
				if (calculatedDataMac[counter] != expectedTag[counter])
				{
					matching = false;
					break;
				}
			}
			if (matching == true)
			{
				this->status == AuthCipherCtx_Status::processedData;
				// overwrite the message buffer with the decrypted data
				inOut= DecreptedData;
			}
			else
			{
				this->status == AuthCipherCtx_Status::processedData;
			}
		}
	}

}

/// @brief: resets the context
void Authentication:: Reset() noexcept
{
  	/*Clear the crypto context*/
	this->macPtr->Reset();
	this->blockCipherPtr->Reset();
	// set the status of the context as notInitialized
	this->status= AuthCipherCtx_Status::notInitialized;
	// clear the flag of setting the key
	Key_is_Set = 0;
}

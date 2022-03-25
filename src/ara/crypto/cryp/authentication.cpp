#include "../../../../include/ara/crypto/cryp/authentication.hpp"

using namespace ara:: crypto;
using namespace ara::crypto::cryp;

///@brief: a constructor saves the instance of the crypto provider of the Authentication context
Authentication::Authentication(CryptoProvider* myProvider)
{
	//@ stores the crypto provider instance of the context in the member "myCryptoProvider" inherited from auth_cipher_ctx
	this-> myCryptoProvider = myProvider;

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
		return true;
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

///@brief: Compare the calculated digest from MAC against an expected signature object
bool Authentication:: Check(const Signature& expected) const noexcept
{
	/* call the function Check of the mac context of this authentication instanceand return a bool that is the same value
	returned from Check of the mac context */
	return this->macPtr->Check(expected);
}

///@brief: Initialize the mac context of this authentication instance for a new data processing 
void Authentication:: Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) noexcept
{
	this->macPtr->Start(iv);
}

///@brief: Initialize the mac context of this authentication instance  for a new data processing
void Authentication::Start(const SecretSeed& iv) noexcept
{
	this->macPtr->Start(iv);
}

///@brief: Update the mac digest calculation by the specified RestrictedUseObject.
void Authentication::UpdateAssociatedData(const RestrictedUseObject& in) noexcept
{
	// update the digest through the Update function of the mac context in this authentication instance
	this->macPtr->Update(in);
}

///@brief: Update the mac digest calculation by a new chunk of associated data
void Authentication::UpdateAssociatedData(ReadOnlyMemRegion in) noexcept
{
	// update the mac digest through the Update function of the mac context in this authentication instance
	this->macPtr->Update(in);
}

///@brief: Update the mac digest calculation by the specified Byte
void Authentication:: UpdateAssociatedData(std::uint8_t in) noexcept
{
	// update the digest through the Update function of the mac context in this authentication instance
	this->macPtr->Update(in);
}

CryptoTransform Authentication::GetTransformation() const noexcept
{
	/* get the Transformation Type from the Symmetric Block cipher context of this authentication instance,
	and return the same value returned from it */ 
	return this->blockCipherPtr->GetTransformation();
}

/// @brief: resets the context
void Authentication:: Reset() noexcept
{
	this->macPtr->Reset();
	this->blockCipherPtr->Reset();
	this->status= AuthCipherCtx_status::notInitialized;
}

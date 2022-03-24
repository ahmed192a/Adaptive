#include "../../../../include/ara/crypto/cryp/authentication.hpp"

using namespace ara::crypto::cryp;

//@brief: a constructor saves the instance of the crypto provider of the Authentication context
Authentication::Authentication(CryptoProvider* myProvider)
{
	//@ stores the crypto provider instance of the context in the member "myCryptoProvider" inherited from auth_cipher_ctx
	this-> myCryptoProvider = myProvider;

	//@ set the status of the context as notInitialized
	this->status = AuthCipherCtx_Status::notInitialized;
}

//@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
bool Authentication :: IsInitialized()
{
	//@ return false if the context is not initialized
	if (status == AuthCipherCtx_Status::notInitialized)
	{
		return false;
	}
	//@ return true if the context is initialized 
	else
	{
		return true;
	}
}

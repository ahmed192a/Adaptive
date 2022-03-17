
#include "CryptoContext.h"

using namespace ara::crypto::cryp;

class CryptoContext {

	virtual ~CryptoContext() noexcept = default;
	//Return CryptoPrimitivId instance containing instance identification.//
	virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept = 0;
	//Check if the crypto context is already initialized and ready to use. It checks all required values//
        //including: key value, IV / seed, etc...//
	virtual bool IsInitialized() const noexcept = 0;
	//Copy-assign another CryptoContext to this instance//
	CryptoContext& operator= (const CryptoContext& other) = default;
	//Move-assign another CryptoContext to this instance.//
	CryptoContext& operator= (CryptoContext&& other) = default;
	//Get a reference to Crypto Provider of this context.//
	virtual CryptoProvider& MyProvider() const noexcept = 0;



};


#include "ara/crypto/cryp/crypto_context.hpp"

using namespace ara::crypto::cryp;

/* Destructor */
virtual CryptoContext:: ~CryptoContext() noexcept = default
{

}
/*Return CryptoPrimitivId instance containing instance identification */
virtual CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const noexcept = 0
{

}
/* Check if the crypto context is already initializedand ready to use */
virtual bool CryptoContext:: IsInitialized() const noexcept = 0
{

}
/* Copy constructor */
CryptoContext:: CryptoContext& operator= (const CryptoContext& other) = default
{

}
/* Move constructor */
CryptoContext:: CryptoContext& operator= (CryptoContext&& other) = default
{

}
/* Get a reference to Crypto Provider of this context */
virtual CryptoContext:: CryptoProvider& MyProvider() const noexcept = 0
{

}



#include "ara/crypto/cryp/PRNG.hpp"

using namespace ara::crypto;
using namespace ara::crypto::cryp;


RandomGeneratorCtx_Status status1;

/*
 * implementation of inherited CyrptoContext virtual functions 
 */

///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
bool PRNG::IsInitialized() const noexcept
{
	//@ return false if the context is not initialized
	if (status1 == RandomGeneratorCtx_Status::initialized || status1 == RandomGeneratorCtx_Status::Seeded)
	{
		return true;
	}
	//@ return true if the context is initialized 
	else 
	{
		return false;
	}
}

///@brief: inherited function from CryptoContext, gets a reference to CryptoPrimitivId instance of this CryptoContext
CryptoPrimitiveId::Uptr PRNG::GetCryptoPrimitiveId() const noexcept
{
	//AlgId myAlgorithmId = myCryptoProvider->ConvertToAlgId("PRNG");
	//CryptoPrimitiveId::Uptr myPrimitiveId = std::make_unique<CryptoPrId>("Auth_Encrption");
	//return myPrimitiveId;
}
PRNG::PRNG(ConcreteCryptoProvider* a)
{
    this->myprovider=a;
}

///@brief: inherited function from CryptoContext, gets a reference to Crypto Provider instance of this CryptoContext
ConcreteCryptoProvider&  PRNG::MyProvider() const noexcept
{
	//@return pointer references the Crypto Provider instance of the context
	//return this-> (*myCryptoProvider) ;
	return (*myprovider);
}

/*
 * implementation of RandomGeneratorCtx inherited virtual functions
 */

/* Constructor of PRNG */
PRNG::PRNG()
{
    status1 = RandomGeneratorCtx_Status::initialized;
}


bool PRNG::AddEntropy(ReadOnlyMemRegion entropy) noexcept
{
    /*
        A deterministic random number generator (PRNG) has entropy zero.
        So the function is empty
    */
    return true;
}

std::vector<ara::crypto::byte> PRNG::Generate(std::uint32_t count) noexcept
{
    std::vector<byte> Returned_Buffer{};
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t n = RNG() % 256;
        Returned_Buffer.push_back(n);
    }

    return Returned_Buffer;
}

/*
 * ara::crypto::cryp::RandomGeneratorCtx::Seed, ara::crypto::cryp::RandomGeneratorCtx::Seed, and ara::crypto::cryp::RandomGeneratorCtx::SetKey shall 
 * return false without modifying the global state, if they are called with a SymmetricKey or a SecretSeed without the allowed usage flag 
 * kAllowRngInit (RS_CRYPTO_02206)
 */

bool PRNG::Seed(const SecSeed& seed) noexcept
{
    if(seed.allowed == kAllowRngInit)
    {
        uint32_t n = seed.Seed;
        RNG.seed(n);
        status1 = RandomGeneratorCtx_Status::Seeded;
        return true;
    }
    return false;
}

bool PRNG::SetKey(const SymmetricKey& key) noexcept
{
    if(key.allowed == kAllowRngInit)
    {
        uint32_t n = key.Seed;
        RNG.seed(n);
        status1 = RandomGeneratorCtx_Status::Seeded;
        return true;
    }
    return false;
}

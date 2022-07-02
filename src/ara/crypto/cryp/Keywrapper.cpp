#include "ara/crypto/cryp/Keywrapper.hpp"

using namespace ara::crypto::cryp;


//variables of cryptoPP will be used in both encryption and decryption
uint8_t KEK[AES::DEFAULT_KEYLENGTH];
uint8_t iv[AES::BLOCKSIZE];

//for testing
uint32_t AES_Alg = 1;
SymmetricKeyWrapperCtx_Status Status;

/*
 * implementation of inherited CyrptoContext virtual functions 
 */

///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
bool Keywrapper :: IsInitialized() const noexcept
{
	//@ return false if the context is not initialized
	if (Status == SymmetricKeyWrapperCtx_Status::initialized)
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
CryptoPrimitiveId::Uptr Keywrapper:: GetCryptoPrimitiveId() const noexcept
{
	//AlgId myAlgorithmId = myCryptoProvider->ConvertToAlgId("CBC/AES_128");
	//CryptoPrimitiveId::Uptr myPrimitiveId = std::make_unique<CryptoPrId>("Auth_Encrption");
	//return myPrimitiveId;
}

///@brief: inherited function from CryptoContext, gets a reference to Crypto Provider instance of this CryptoContext
ConcreteCryptoProvider&  Keywrapper:: MyProvider() const noexcept
{
	//@return pointer references the Crypto Provider instance of the context
	//return this-> (*myCryptoProvider) ;
    ConcreteCryptoProvider& a=this->MyProvider();
	return a;
}

/*
 * implementation of SymmetricKeyWrapperCtx inherited virtual functions
 */



/*
 * Private functions for Keywrapping Algorithm
 */


//Private function that is used in WrapKeyMaterial() and unwrapkey() functions 
vector<uint8_t> Keywrapper::hexToASCII(string hex) const
{
    // initialize the ASCII code string as empty.
    std::vector<byte> ascii;
    for (size_t i = 0; i < hex.length(); i++)
    {
        ascii.push_back(hex[i]);
    }
    return ascii;
}

// Generates the iv that will be used in AES in CBC mode 

Keywrapper::Keywrapper()
{
    RandomGeneratorCtx::Uptr R = std::make_unique<PRNG>();
    SecSeed S_iv(0xffff,true,true);
    S_iv.Seed = 19;
    PRNG R2;
    R2.Seed(S_iv);
    vector<byte> y = R2.Generate((Block_size));
    for(int i = 0 ; i < Block_size; i++)
    {
        iv[i] = y.at(i);
    }
}

std::size_t Keywrapper::CalculateWrappedKeySize(std::size_t keylength)const noexcept
{
    /*This equation used for Calculating the size of the wrapped key in bytes from original key length in bits.*/
    std::size_t a = (keylength/8) + (Block_size - ((keylength/8) % Block_size));
    return a;
}


/*
 * The interface ara::crypto::cryp::SymmetricKeyWrapperCtx::GetMaxTargetKeyLength shall return the maximum bit length of the payload (key-material) 
 * that can be protected by the algorithm specified during context creation.c(RS_CRYPTO_02208)
 */

//std::size_t Keywrapper::GetMaxTargetKeyLength() noexcept
//{
//    return this->Max_KEY_Length;
//}

void Keywrapper::SetKey(const SymmetricKey& key, CryptoTransform transform) noexcept
{
    if(transform == CryptoTransform::kEncrypt || transform == CryptoTransform::kDecrypt)
    {
        Status = SymmetricKeyWrapperCtx_Status::initialized;
        //cout << AES_Wrapper_Status::initialized;
        this->Key = key;
   
    }
    else
    {
        /*errors*/
    }

}

/*
std::size_t Keywrapper::GetTargetKeyGranularity()
{
    return KEK_Length / 8;
}
*/
void Keywrapper::Reset() noexcept
{
}


vector<uint8_t> Keywrapper::WrapKeyMaterial(const SymmetricKey &key) const noexcept
{
    if(Status == SymmetricKeyWrapperCtx_Status::initialized && (key.keyVal).size()== 16 && key.allowed== ara::crypto::kAllowKeyExporting)
    {
        vector <byte> WrappedKey;
        std::string plain = ""; 
        string cipher, recovered;
        uint32_t size = (key.keyVal).size();

        for(int i = 0; i < size; i++)
        {
            plain += key.keyVal.at(i);
        }
 
 
        try
        {
            CBC_Mode< AES >::Encryption e;
            e.SetKeyWithIV(KEK, sizeof(KEK)/sizeof(KEK[0]), iv);

            StringSource s(plain, true, 
                new StreamTransformationFilter(e,
                    new StringSink(cipher)
                ) // StreamTransformationFilter
            ); // StringSource
        }
        catch(const Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        /* For testing 
        std::cout << "key: ";
        std::cout << KEK <<endl;
        std::cout << "iv: ";
        std::cout << iv << endl;
        std::cout << "cipher text: ";
        std::cout << cipher << endl;
        */
        std::string x = cipher;
        WrappedKey = hexToASCII(x);
        return WrappedKey;
    }
    else
    {
        /*
         * WrapKeyMaterial shall return a CryptoErrorDomain::kInvalidInputSize error, if the length of the provided ara::crypto::RestrictedUseObject 
         * is unsupported by the algorithm specified during context creation. >> Therefore we check on the size of the key
         * WrapKeyMaterial shall return a CryptoErrorDomain::kUninitializedContext error, if SymmetricKeyWrapperCtx::SetKey was never called. >> Therefore we check on the status
         * WrapKeyMaterial shall return a CryptoErrorDomain::kUsageViolation error, if the kAllowExport flag is not set in the ara::crypto::AllowedUsageFlags of 
         * the provided ara::crypto::RestrictedUseObject, or if the kAllowKeyExporting flag of the ara::crypto::AllowedUsageFlags 
         * is not set for the SymmetricKey specified in the SetKey call -> Therefoore we check on key.Usage 
         */
    }
}

/*
 * The interface ara::crypto::cryp::SymmetricKeyWrapperCtx::UnwrapKey shall execute the key-unwrap operation on the provided ara::crypto::ReadOnlyMemRegion (vector of bytes)
 * and return a unique smart pointer to the instantiated ara::crypto::RestrictedUseObject. UnwrapKey shall also apply the provided ara::crypto::AllowedUsageFlags 
 * and ara::crypto::CryptoAlgId to the created RestrictedUseObject (RS_CRYPTO_02208)
 */
SymmetricKey::Uptr Keywrapper::UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) const noexcept
{
    size_t a=key_length;
    int x = CalculateWrappedKeySize(a);
 
    if(algId == AES_Alg && allowedUsage == kAllowKeyImporting && Status == SymmetricKeyWrapperCtx_Status::initialized && wrappedKey.size() == x)
    {
        string recovered, cipher_txt = "";
        SymmetricKey::Uptr R = std::make_unique<SymmetricKey>();
        uint32_t size = wrappedKey.size();
        for(int i = 0; i < size; i++)
        {
            cipher_txt += wrappedKey.at(i);
        }
        try
        {
            CBC_Mode< AES >::Decryption d;
            d.SetKeyWithIV(KEK, sizeof(KEK)/sizeof(KEK[0]), iv);

            StringSource s(cipher_txt, true, 
                new StreamTransformationFilter(d,
                    new StringSink(recovered)
                ) // StreamTransformationFilter
            ); // StringSource

            
        }
        catch(const Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        R->keyVal = hexToASCII(recovered);
        R ->allowed = ara::crypto::kAllowKeyImporting;
        return R;
    }
    else
    {
        /*
         * SymmetricKeyWrapperCtx::UnwrapKey shall return a CryptoErrorDomain::kInvalidInputSize error, if the length of the provided ara::crypto::ReadOnlyMemRegion 
         * is unsupported by the algorithm specified during context creation. >> Check on size of the vector 
         * return a CryptoErrorDomain::kUninitializedContext error, if SymmetricKeyWrapperCtx::SetKey was never called. >> Check on Status
         */
    }
    
}

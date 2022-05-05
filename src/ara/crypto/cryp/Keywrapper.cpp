#include "ara/crypto/cryp/Keywrapper.hpp"

using namespace ara::crypto::cryp;


//variables of cryptoPP will be used in both encryption and decryption
byte KEK[AES::DEFAULT_KEYLENGTH];
byte iv[AES::BLOCKSIZE];

uint32_t AES_Alg = 1;
SymmetricKeyWrapperCtx_Status Status;

/*
 * Private functions for Keywrsapping Algorithm
 */


//Private function that is used in WrapKeyMaterial() and unwrapkey() functions 
vector<byte>Keywrapper::hexToASCII(string hex)
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
    //ara::crypto::cryp::PRNG R;
    SecretSeed S1;
    S1.Seed = 15;
    // Also we can write R->Seed(S1)
    (*R).Seed(S1);
    std::vector <byte> x = (*R).Generate((KEK_Length / 4));
    std::string KEK = "";
    for (int i = 0; i < (KEK_Length / 4); i++)
    {
        int b = x[i];
        std::string y = decToHexa(b);
        KEK += y;
    }
}

std::size_t Keywrapper::CalculateWrappedKeySize(std::size_t keylength)
{
    /*This equation used for Calculating the size of the wrapped key in bytes from original key length in bits.*/
    wrapped_key_size = (keylength/8) + (Block_size - ((keylength/8) % Block_size));
    return wrapped_key_size;
}


/*
 * The interface ara::crypto::cryp::SymmetricKeyWrapperCtx::GetMaxTargetKeyLength shall return the maximum bit length of the payload (key-material) 
 * that can be protected by the algorithm specified during context creation.c(RS_CRYPTO_02208)
 */

std::size_t Keywrapper::GetMaxTargetKeyLength()
{
    return Max_KEKLength;
}

void Keywrapper::SetKey(const SymmetricKey& key, CryptoTransform transform)
{
    if(transform == CryptoTransform::kEncrypt || transform == CryptoTransform::kDecrypt)
    {
        Status = AES_Wrapper_Status::initialized;
        //cout << AES_Wrapper_Status::initialized;
        this->Key = key;
        for(int i = 0 ; i < Block_size; i++)
        {
            KEK[i] = Key.key.at(i);
            cout << KEK[i] << " " << Key.key.at(i) << "\t";
        }
        cout << endl;
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

void Keywrapper::Reset()
{
}
*/

vector<byte> Keywrapper::WrapKeyMaterial(const RestrictedUseObject &key)
{
    if(Status == SymmetricKeyWrapperCtx_Status::initialized && (key.Key).size()== 16)
    {
        vector <byte> WrappedKey;
        std::string plain = ""; 
        string cipher, recovered;
        uint32_t size = (key.Key).size();

        for(int i = 0; i < size; i++)
        {
            plain += key.Key.at(i);
        }
        std::cout << plain.size() << endl;
        std::cout << "plain text: " << plain << std::endl;
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
        
        WrappedKey = hexToASCII(cipher);
        return WrappedKey;
    }
    else
    {
        /*
         * WrapKeyMaterial shall return a CryptoErrorDomain::kInvalidInputSize error, if the length of the provided ara::crypto::RestrictedUseObject 
         * is unsupported by the algorithm specified during context creation. >> Therefore we check on the size of the key
         * WrapKeyMaterial shall return a CryptoErrorDomain::kUninitializedContext error, if SymmetricKeyWrapperCtx::SetKey was never called. >> Therefore we check on the status
         */
    }
}

RestrictedUseObject::Uptrc Keywrapper::UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage)
{
    int x = CalculateWrappedKeySize(key_length);
    cout << x << "\t" << wrappedKey.size() << endl;
    if(algId == AES_Alg && allowedUsage == kAllowDataDecryption && Status == SymmetricKeyWrapperCtx_Status::initialized && wrappedKey.size() == x)
    {
        string recovered, cipher_txt = "";
        RestrictedUseObject::Uptrc R = std::make_unique<RestrictedUseObject>();
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

            //std::cout << "recovered text: " << recovered << std::endl;
        }
        catch(const Exception& e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
        R->Key = hexToASCII(recovered);
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

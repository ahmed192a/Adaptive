#include "ara/crypto/cryp/Keywrapper.hpp"

using namespace ara::crypto::cryp;


/*
 * Private function for KEK Generation
 */
std::string Keywrapper::decToHexa(int n)
{
    char hexaDeciNum[100];
    std::string Returned_str;
    int i = 0;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        }
        else {
            hexaDeciNum[i] = temp + 55;
            i++;
        }
        n = n / 16;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        Returned_str += hexaDeciNum[j];

    }
    return Returned_str;
}


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
    return wrapped_key_size;
}

std::size_t Keywrapper::GetMaxTargetKeyLength()
{
    return Max_KEKLength;
}

/*
void SymmetricKeyWrapperCtx::SetKey(const SymmetricKey& key, CryptoTransform transform)
{
    this->key = key;
}
*/
std::size_t Keywrapper::GetTargetKeyGranularity()
{
    return KEK_Length / 8;
}

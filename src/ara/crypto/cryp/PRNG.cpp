#include "ara/crypto/cryp/PRNG.hpp"

using namespace ara::crypto::cryp;

PRNG::PRNG()
{

}

bool PRNG::AddEntropy(ReadOnlyMemRegion entropy)
{
    /*
        A deterministic random number generator (PRNG) has entropy zero.
        So the function is empty
    */
    return true;
}

std::vector<ara::crypto::byte> PRNG::Generate(std::uint32_t count)
{
    std::vector<byte> Returned_Buffer{};
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t n = RNG() % 256;
        Returned_Buffer.push_back(n);
    }

    return Returned_Buffer;
}

bool PRNG::Seed(const SecretSeed& seed)
{
    uint32_t n = seed.Seed;
    RNG.seed(n);
    return true;
}

bool PRNG::SetKey(const SymmetricKey& key)
{
    uint32_t n = key.Seed;
    RNG.seed(n);
    return true;
}

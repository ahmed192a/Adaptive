#include "../../../../include/ara/crypto/common/entry_point.hpp"

using namespace ara::crypto;
EntryPoint a;
cryp::CryptoProvider::Uptr LoadCryptoProvider (const ara::core::InstanceSpecifier &iSpecify) noexcept
{   
    //we only have one crypto provider so the instancespecifier input doesn't matter
    cryp::ConcreteCryptoProvider::Uptr CryptoProviderPtr = a.DefaultCryptoProvider;
    return CryptoProviderPtr;
}

keys::KeyStorageProvider::Uptr LoadKeyStorageProvider () noexcept
{
    
}
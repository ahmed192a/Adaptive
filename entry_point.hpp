#ifndef ARA_CRYPTO_ENTRY_POINT_H
#define ARA_CRYPTO_ENTRY_POINT_H
#include "../../core/instance_specifier.hpp"
#include "cryp/concrete_crypto_provider.hpp"
#include <vector>
namespace ara
{
    namespace crypto
    {
         class EntryPoint
         {  
             
             public:
             const cryp::ConcreteCryptoProvider::Uptr DefaultCryptoProvider = std::make_unique<ara::crypto::cryp::ConcreteCryptoProvider>();
             cryp::CryptoProvider::Uptr LoadCryptoProvider (const ara::core::InstanceSpecifier &iSpecify) noexcept;
             keys::KeyStorageProvider::Uptr LoadKeyStorageProvider () noexcept;

         };
    }
}
#endif






#endif
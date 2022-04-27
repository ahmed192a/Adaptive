#ifndef ARA_CRYPTO_KEYS_KEYSLOT_H_
#define ARA_CRYPTO_KEYS_KEYSLOT_H_

namespace ara
{
    namespace crypto
    {
        class KeySlot 
        {
        public:
            using Uptr = std::unique_ptr<KeySlot>;
        };

    }
}
#endif
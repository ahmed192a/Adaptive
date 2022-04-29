#ifndef ARA_CRYPTO_KEYS_KEYSLOT_H_
#define ARA_CRYPTO_KEYS_KEYSLOT_H_

#include "../common/concrete_io_interface.hpp"
namespace ara
{
    namespace crypto
    {

        enum class SlotState : std::uint8_t
            {
                closed,
                opened,
                commited
            };

        class KeySlot 
        {
            

        public:
            using Uptr = std::unique_ptr<KeySlot>;

            SlotState state = SlotState::closed;

            virtual IOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) const noexcept = 0;
            
            virtual ara::core::Result<void> Clear () noexcept=0;
            
            virtual ara::core::Result<KeySlotContentProps> GetContentProps () const noexcept=0;
            
            virtual ara::core::Result<cryp::CryptoProvider::Uptr> MyProvider () const noexcept=0;
            
            ~KeySlot () noexcept=default;

        };

        class InheritedKeySlot:KeySlot
        {
        public:
            IOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) const noexcept;

        };
    }
}
#endif

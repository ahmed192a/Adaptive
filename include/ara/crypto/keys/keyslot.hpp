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

            /********** variables needed by KeyStorageProvider using the keySlot *********/
            SlotState state = SlotState::closed;
            IOInterface::Uptr IOInterfacePtr;
            /****************************************************************************/

            virtual IOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) const noexcept = 0;
            
            virtual void Clear () noexcept=0;
            
            virtual KeySlotContentProps GetContentProps () const noexcept=0;
            
            virtual cryp::CryptoProvider::Uptr MyProvider () const noexcept=0;
            
            virtual void SaveCopy(const IOInterface& container) noexcept = 0;

            ~KeySlot () noexcept=default;

        };

        class InheritedKeySlot:public KeySlot
        {
        public:
            IOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) const noexcept;

            void SaveCopy(const IOInterface& container) noexcept;
        };
    }
}
#endif

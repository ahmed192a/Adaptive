// #ifndef ARA_CRYPTO_KEYS_KEYSLOT_H_
// #define ARA_CRYPTO_KEYS_KEYSLOT_H_

// #include "ara/core/result.h"
// #include "ara/crypto/keys/key_slot_content_props.h"
// #include "ara/crypto/keys/key_slot_prototype_props.h"
// #include "ara/crypto/cryp/crypto_provider.h"
// #include "ara/crypto/cryp/cryobj/crypto_object.h"
// #include "ara/crypto/common/concrete_io_interface.h"

// namespace ara
// {
//     namespace crypto
//     {
//         namespace keys
//         {
//             enum class SlotState : std::uint8_t
//             {
//                 closed,
//                 opened,
//                 commited
//             };

//             class KeySlot 
//             {
//                 public:
//                  using Uptr = std::unique_ptr<KeySlot>;

//                 /********** variables needed by KeyStorageProvider using the keySlot *********/
//                 SlotState state = SlotState::closed;
//                 //IOInterface::Uptr IOInterfacePtr;
//                 /****************************************************************************/
//                 KeySlotContentProps KSCP ;
//                 KeySlotPrototypeProps KSPP;
//                 bool Empty_State =0;//If the key slot is empty put 1 else put 0//
//                 ara::crypto::cryp::CryptoProvider* myCryptoProvider;
//                 std::unique_ptr<cryp::CryptoProvider> Myprov;
//                 /**
//                  * @brief Destroy the Key Slot object
//                  * 
//                  */
//                 virtual ~KeySlot () noexcept=default;
//                 /**
//                  * @brief 
//                  * 
//                  * @param subscribeForUpdates 
//                  * @param writeable 
//                  * @return IOInterface::Uptr 
//                  */
//                 virtual ConcreteIOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) const noexcept = 0;
//                 /**
//                  * @brief 
//                  * 
//                  * @return true 
//                  * @return false 
//                  */
//                 virtual bool IsEmpty() const noexcept = 0;
//                 /**
//                  * @brief 
//                  * 
//                  * @param container 
//                  */
//                 virtual void SaveCopy(const ConcreteIOInterface& container) noexcept = 0;
//                 /**
//                  * @brief Get the Content Props object
//                  * 
//                  * @return ara::core::Result<KeySlotContentProps> 
//                  */
//                 virtual KeySlotContentProps GetContentProps ()const noexcept=0;
//                 /**
//                  * @brief Retrieve an instance of the CryptoProvider that owns this KeySlot. Any key slot always has an
//                  * associated default Crypto Provider that can serve this key slot. In the simplest case all key slots
//                  * can be served by a single Crypto Provider installed on the Adaptive Platform.
//                  * 
//                  * @return ara::core::Result<cryp::CryptoProvider::Uptr> 
//                  */
//                 virtual cryp::CryptoProvider::Uptr MyProvider ()const noexcept=0;
//                 /**
//                  * @brief Get the Prototyped Props object
//                  * 
//                  * @return ara::core::Result<KeySlotPrototypeProps> 
//                  */
//                 virtual KeySlotPrototypeProps GetPrototypedProps ()const noexcept=0;
//                 /**
//                  * @brief 
//                  * 
//                  * @return ara::core::Result<void> 
//                  */
//                 virtual void Clear () noexcept=0;
//                 /**
//                  * @brief Copy-assign another KeySlot to this instanc
//                  * 
//                  * @param other 
//                  * @return KeySlot& 
//                  */
//                 KeySlot& operator= (const KeySlot &other)=default;
//                 /**
//                  * @brief Move-assign another KeySlot to this instance
//                  * 
//                  * @param other 
//                  * @return KeySlot& 
//                  */
//                 KeySlot& operator= (KeySlot &&other)=default;


//             };
//         }

//     }
// }
// #endif

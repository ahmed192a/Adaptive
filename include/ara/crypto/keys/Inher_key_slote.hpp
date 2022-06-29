 #ifndef ARA_CRYPTO_KEYS_INH_KEYSLOT_H_
 #define ARA_CRYPTO_KEYS_INH_KEYSLOT_H_

 #include "ara/crypto/keys/keyslot.hpp"
  namespace ara
 {
     namespace crypto
     {
         namespace keys
         {
              class InhKeySlot:public KeySlot 
             {
                 std::string path;
                 public:
                 /**
                  * @brief Construct a new Inh Key Slot object
                  * 
                  * @param file_name 
                  */
                 InhKeySlot (std::string file_name);

                 /**
                  * @brief Construct a new Inh Key Slot object
                  * 
                  */
                 InhKeySlot ();
                 /**
                  * @brief Destroy the Key Slot object
                  * 
                  */
                 ~InhKeySlot () noexcept=default;
                 /**
                  * @brief 
                  * 
                  * @return true 
                  * @return false 
                  */
                 bool IsEmpty() noexcept;
                 /**
                  * @brief 
                  * 
                  * @param container 
                  */
                 void SaveCopy(const ConcreteIOInterface& container) noexcept;
                 /**
                  * @brief 
                  * 
                  * @param subscribeForUpdates 
                  * @param writeable 
                  * @return IOInterface::Uptr 
                  */
                
                 ConcreteIOInterface::Uptr Open(bool subscribeForUpdates = false, bool writeable = false) noexcept;
                 /**
                  * @brief Get the Content Props object
                  * 
                  * @return ara::core::Result<KeySlotContentProps> 
                  */
                 KeySlotContentProps GetContentProps ()const noexcept;
                 /**
                  * @brief Retrieve an instance of the CryptoProvider that owns this KeySlot. Any key slot always has an
                  * associated default Crypto Provider that can serve this key slot. In the simplest case all key slots
                  * can be served by a single Crypto Provider installed on the Adaptive Platform.
                  * 
                  * @return ara::core::Result<cryp::CryptoProvider::Uptr> 
                  */
                  cryp::CryptoProvider::Uptr MyProvider ()const noexcept;
                 /**
                  * @brief Get the Prototyped Props object
                  * 
                  * @return ara::core::Result<KeySlotPrototypeProps> 
                  */
                 KeySlotPrototypeProps GetPrototypedProps ()const noexcept;
                 /**
                  * @brief 
                  * 
                  * @return ara::core::Result<void> 
                  */
                 void Clear () noexcept=0;
                 /**
                  * @brief Copy-assign another KeySlot to this instanc
                  * 
                  * @param other 
                  * @return KeySlot& 
                  */
                 //InhKeySlot& operator= (const InhKeySlot& other) = default;
                 /**
                  * @brief Move-assign another KeySlot to this instance
                  * 
                  * @param other 
                  * @return KeySlot& 
                  */
                 //InhKeySlot& operator= (InhKeySlot&& other) = default;
             };
         }
     }
 }
#endif

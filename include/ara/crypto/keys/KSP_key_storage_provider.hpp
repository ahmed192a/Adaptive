 #include "key_storage_provider.hpp"
#include <filesystem>
#include <fstream>


 namespace ara
 {
 	namespace crypto
 	{
 		namespace keys
 		{
			enum TextVariables {
				KSCP_mAlgId,
				KSCP_mObjectType,
				KSCP_mObjectUid_mGeneratorUid_mQwordLs,
				KSCP_mObjectUid_mGeneratorUid_mQwordMs,
				KSCP_mObjectUid_mVersionStamp,
				KSCP_mContentAllowedUsage,
				KSCP_mObjectSize,
				KSPP_mSlotCapacity,
				KSPP_mSlotType,
				KSPP_mAlgId,
				KSPP_mAllocateSpareSlot,
				KSPP_mAllowContentTypeChange,
				KSPP_mMaxUpdateAllowed,
				KSPP_mExportAllowed,
				KSPP_mContentAllowedUsage,
				KSPP_mObjectType
				};

 			class KSPKeyStorageProvider :public KeyStorageProvider
 			{
			private:
				//bool check_text(char * a, std::string b);
				TextVariables String_to_enum(std::string a);
				//variable contains the path of keyslots
				std::string my_path = "ara/crypto/keys/KeySlot/";

 			public:
 				//@breif: Begin new transaction for key slots update
 				TransactionId BeginTransaction( TransactionScope& targetSlots) noexcept;

 				//@breif: Commit changes of the transaction to Key Storage
 				void CommitTransaction(TransactionId id) noexcept ;

 				//@breif: Load a key slot
 				// The function loads the information associated with a KeySlot into a KeySlot object
                InhKeySlot::Uptr LoadKeySlot(std::string KeySlotName) noexcept;

 				//@breif: Rollback all changes executed during the transaction in Key Storage.
 				// The rollback command permanently cancels all changes made during the transaction in Key Storage.
 				// A rolled back transaction is completely invisible for all applications.
 				void RollbackTransaction(TransactionId id) noexcept;

                /******************************* Not in SWS *********************************/
 				//@breif: Get a vector of IOInterface from a Transaction id.
 				std::vector<ConcreteIOInterface::Uptr> GetIOInterfaceFromid(TransactionId id) noexcept;

                InhKeySlot::Uptr CreateNewKeySlot(std::string name);
 			};
 		}
 	}
 }

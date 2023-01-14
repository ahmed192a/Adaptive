// #include "key_storage_provider.h"

// namespace ara
// {
// 	namespace crypto
// 	{
// 		namespace keys
// 		{
// 			class KSPKeyStorageProvider :KeyStorageProvider
// 			{
// 			public:
// 				//@brief: Begin new transaction for key slots update
// 				TransactionId BeginTransaction(const TransactionScope& targetSlots) noexcept;

// 				//@brief: Commit changes of the transaction to Key Storage
// 				void CommitTransaction(TransactionId id) noexcept ;

// 				//@brief: Load a key slot
// 				// The function loads the information associated with a KeySlot into a KeySlot object
// 				KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept ;

// 				//@brief: Rollback all changes executed during the transaction in Key Storage.
// 				// The rollback command permanently cancels all changes made during the transaction in Key Storage.
// 				// A rolled back transaction is completely invisible for all applications.
// 				void RollbackTransaction(TransactionId id) noexcept;

// 				//@brief: Get a vector of IOInterface from a Transaction id.
// 				std::vector<IOInterface::Uptr> GetIOInterfaceFromid(TransactionId id) noexcept;
// 			};
// 		}
// 	}
// }

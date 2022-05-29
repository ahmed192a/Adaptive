 #ifndef ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_HPP
 #define ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_HPP

 //#include <memory>
 #include <vector>
 #include "elementary_types.hpp"
 //#include "../../core/instance_specifier.hpp"
 #include "Inher_key_slote.hpp"

 namespace ara
 {
 	namespace crypto
 	{
 		namespace keys
 		{
 			class KeyStorageProvider
 			{
 			protected:
				
 				//@breif: vector to keep track of opened TransactionScopes which are ready to be commited with changes
 				std::vector < TransactionScopeWithIdAndState> transactionIdState;

 				//@breif: vector to keep a copy of original data of opened Transactions
 				std::vector <TransactionScopeWithIdAndState> spareOpenedTransactions;

 				//@breif: vector to save IOInterfaces of key slots in a transaction
 				std::vector<std::vector <ConcreteIOInterface::Uptr>> TransactionIOInterfaces;

 				/*std::vector < TransactionScope> openedTransactions;
 				std::vector < TransactionId> openedTransactionIds;*/

 				// incremental variable to carry the next TransactionId to be assigned to opened transaction
 				TransactionId nextId = 1;

 			public:
 				using Uptr = std::unique_ptr<KeyStorageProvider>;
				
 				//@breif: destructor
 				virtual ~KeyStorageProvider() noexcept = default;
				
 				//@breif: Begin new transaction for key slots update
 				virtual TransactionId BeginTransaction(const TransactionScope& targetSlots) noexcept = 0;

 				//@breif: Commit changes of the transaction to Key Storage
 				virtual void CommitTransaction(TransactionId id) noexcept = 0;

 				//@breif: Load a key slot
 				// The function loads the information associated with a KeySlot into a KeySlot object
 				//virtual KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept = 0;

 				//@breif: Rollback all changes executed during the transaction in Key Storage.
 				// The rollback command permanently cancels all changes made during the transaction in Key Storage.
 				// A rolled back transaction is completely invisible for all applications.
 				virtual void RollbackTransaction(TransactionId id) noexcept = 0;

 				//@breif: Get a vector of IOInterface from a Transaction id.
 				virtual std::vector<IOInterface::Uptr> GetIOInterfaceFromid(TransactionId id) noexcept = 0;

 				//@breif: Copy-assign another KeyStorageProvider to this instance.
 				KeyStorageProvider& operator= (const KeyStorageProvider& other) = default;

 				//@breif: Move-assign another KeyStorageProvider to this instance.
 				KeyStorageProvider& operator= (KeyStorageProvider&& other) = default;
 			};

 		}
 	}
 }


 #endif

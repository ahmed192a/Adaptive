#ifndef ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_HPP
#define ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_HPP

#include <memory>
#include <vector>
#include "elementary_types.hpp"
#include "updates_observer.hpp"
#include "../../core/instance_specifier.hpp"

namespace ara
{
	namespace crypto
	{
		namespace keys
		{
			class KeyStorageProvider
			{
			protected:
				//@breif: vectors to keep track of opened TransactionScopes which are ready to be commited with changes
				
				std::vector < OpenedTransactionScopeWithIdPair> openedTransactionsWithIds;
				/*std::vector < TransactionScope> openedTransactions;
				std::vector < TransactionId> openedTransactionIds;*/

				// incremental variable to carry the next TransactionId to be assigned to opened transaction
				TransactionId nextId = 0;

			public:
				using Uptr = std::unique_ptr<KeyStorageProvider>;
				
				//@breif: destructor
				virtual ~KeyStorageProvider() noexcept = default;
				
				//@breif: Begin new transaction for key slots update
				virtual TransactionId BeginTransaction(const TransactionScope& targetSlots) noexcept = 0;

				//@breif: Commit changes of the transaction to Key Storage
				virtual void CommitTransaction(TransactionId id) noexcept = 0;

				//@breif: Get pointer of registered Updates Observer
				// The method returns nullptr if no observers have been registered yet!
				virtual UpdatesObserver::Uptr GetRegisteredObserver() const noexcept = 0;

				//@breif: Load a key slot
				// The function loads the information associated with a KeySlot into a KeySlot object
				virtual KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept = 0;

				//@breif: Register consumer Updates Observer. 
				// Only one instance of the UpdatesObserver may be registered by an application process, 
				// therefore this method always unregister previous observer and return its unique pointer
				virtual UpdatesObserver::Uptr RegisterObserver(UpdatesObserver::Uptr observer = nullptr) noexcept = 0;

				//@breif: Rollback all changes executed during the transaction in Key Storage.
				// The rollback command permanently cancels all changes made during the transaction in Key Storage.
				// A rolled back transaction is completely invisible for all applications.
				virtual void RollbackTransaction(TransactionId id) noexcept = 0;


			};

		}
	}
}


#endif

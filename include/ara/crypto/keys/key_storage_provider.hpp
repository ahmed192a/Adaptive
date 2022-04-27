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
				//@breif: a vector to keep track of opened TransactionScopes which are ready to be commited with changes
				std::vector < OpenedTransactionScopeWithIdPair> openedTransactions;

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


			};

		}
	}
}


#endif

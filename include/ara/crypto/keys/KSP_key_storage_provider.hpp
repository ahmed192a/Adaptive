#include "key_storage_provider.hpp"

namespace ara
{
	namespace crypto
	{
		namespace keys
		{
			class KSPKeyStorageProvider :KeyStorageProvider
			{
			public:
				//@breif: Begin new transaction for key slots update
				TransactionId BeginTransaction(const TransactionScope& targetSlots) noexcept;

				//@breif: Commit changes of the transaction to Key Storage
				void CommitTransaction(TransactionId id) noexcept ;

				//@breif: Get pointer of registered Updates Observer
				// The method returns nullptr if no observers have been registered yet!
				UpdatesObserver::Uptr GetRegisteredObserver() const noexcept ;

				//@breif: Load a key slot
				// The function loads the information associated with a KeySlot into a KeySlot object
				KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept ;

				//@breif: Register consumer Updates Observer. 
				// Only one instance of the UpdatesObserver may be registered by an application process, 
				// therefore this method always unregister previous observer and return its unique pointer
				UpdatesObserver::Uptr RegisterObserver(UpdatesObserver::Uptr observer = nullptr) noexcept ;

				//@breif: Rollback all changes executed during the transaction in Key Storage.
				// The rollback command permanently cancels all changes made during the transaction in Key Storage.
				// A rolled back transaction is completely invisible for all applications.
				void RollbackTransaction(TransactionId id) noexcept ;



			};
		}
	}
}

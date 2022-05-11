#ifndef ARA_CRYPTO_KEYS_UPDATES_OBSERVER_HPP
#define ARA_CRYPTO_KEYS_UPDATES_OBSERVER_HPP

#include <memory>

namespace ara
{
	namespace crypto
	{
		namespace keys
		{
			class UpdatesObserver
			{
			public:
				using Uptr = std::unique_ptr<UpdatesObserver>;

				virtual ~UpdatesObserver() noexcept = default;

				virtual void OnUpdate(const TransactionScope& updatedSlots) noexcept = 0;

				UpdatesObserver& operator= (const UpdatesObserver& other) = default;

				UpdatesObserver& operator= (UpdatesObserver&& other) = default;


			};


		}
	}
}


#endif
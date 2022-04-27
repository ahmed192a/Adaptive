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

			};


		}
	}
}


#endif
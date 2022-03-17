#ifndef VOLATILE_TRUSTED_CONTAINER_HPP_
#define VOLATILE_TRUSTED_CONTAINER_HPP_
#include "ara/crypto/common/io_interface.hpp"
namespace ara
{
	namespace crypto
	{
		namespace cryp
		{

			class VolatileTrustedContainer
			{
				public:


				using Uptr = std::unique_ptr<VolatileTrustedContainer>;

				virtual IOInterface& GetIOInterface () const noexcept=0;

				virtual ~VolatileTrustedContainer () noexcept=default;


			};
		}
	}
}

#endif /* VOLATILE_TRUSTED_CONTAINER_HPP_ */

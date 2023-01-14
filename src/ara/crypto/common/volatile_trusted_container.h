//#ifndef VOLATILE_TRUSTED_CONTAINER_HPP_
//#define VOLATILE_TRUSTED_CONTAINER_HPP_
#pragma once
#include "io_interface.h"
namespace ara
{
	namespace crypto
	{
			class ConcreteIOInterface;
			class VolatileTrustedContainer
			{
				public:


				using Uptr = std::unique_ptr<VolatileTrustedContainer>;

				 ConcreteIOInterface& GetIOInterface () const;

				//virtual ~VolatileTrustedContainer () noexcept=default;


			};
	}
}

//#endif /* VOLATILE_TRUSTED_CONTAINER_HPP_ */

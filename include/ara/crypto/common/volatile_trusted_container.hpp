//#ifndef VOLATILE_TRUSTED_CONTAINER_HPP_
//#define VOLATILE_TRUSTED_CONTAINER_HPP_
#pragma once
#include "io_interface.hpp"
namespace ara
{
	namespace crypto
	{
			class ConcreteIOInterface;
			class VolatileTrustedContainer
			{
				public:


				using Uptr = std::unique_ptr<VolatileTrustedContainer>;

				virtual ConcreteIOInterface& GetIOInterface () const noexcept;

				virtual ~VolatileTrustedContainer () noexcept=default;


			};
	}
}

//#endif /* VOLATILE_TRUSTED_CONTAINER_HPP_ */

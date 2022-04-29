#ifndef ARA_CRYPTO_CONCRETE_VOLATILE_CONTAINER_HPP_
#define ARA_CRYPTO_CONCRETE_VOLATILE_CONTAINER_HPP_
#include "volatile_trusted_container.hpp"
#include "concrete_io_interface.hpp"

namespace ara
{
    namespace crypto
	{
        class ConcreteVolatileTrustedContainer : public VolatileTrustedContainer
		{
            
		public:
        static ConcreteIOInterface myinterface;
            std::vector<uint8_t> buffer;
            ConcreteVolatileTrustedContainer(std::size_t capacity,IOInterface& instance);

             IOInterface& GetIOInterface () const noexcept;

			 ~ConcreteVolatileTrustedContainer () noexcept=default;


        };
    }
}



#endif

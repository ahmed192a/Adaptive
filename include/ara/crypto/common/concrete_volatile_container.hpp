//#ifndef ARA_CRYPTO_CONCRETE_VOLATILE_CONTAINER_HPP_
//#define ARA_CRYPTO_CONCRETE_VOLATILE_CONTAINER_HPP_
#pragma once

#include "volatile_trusted_container.hpp"
//#include "concrete_io_interface.hpp"
#include <vector>

namespace ara
{
    namespace crypto
	{
	    //class VolatileTrustedContainer{};
        class ConcreteIOInterface;
	    //class ConcreteIOInterface{};
        class ConcreteVolatileTrustedContainer : public VolatileTrustedContainer
		{
            
		public:
        static ConcreteIOInterface* myinterface;
            std::vector<uint8_t> buffer;
            ConcreteVolatileTrustedContainer(std::size_t capacity,ConcreteIOInterface* instance);

             ConcreteIOInterface& GetIOInterface () const noexcept;

			 ~ConcreteVolatileTrustedContainer () noexcept=default;


        };
    }
}



//#endif

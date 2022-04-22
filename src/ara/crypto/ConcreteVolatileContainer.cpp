


#include "../../../../include/ara/crypto/common/concrete_volatile_container.hpp"

using namespace ara::crypto;

    ConcreteVolatileTrustedContainer::ConcreteVolatileTrustedContainer(std::size_t capacity,IOInterface& instance)
    {
        ConcreteVolatileTrustedContainer::myinterface=instance;
       buffer.resize(capacity+5);        
    }

    IOInterface& ConcreteVolatileTrustedContainer::GetIOInterface () const noexcept
    {
        return ConcreteVolatileTrustedContainer::myinterface;
    }




#include "../../../../include/ara/crypto/common/concrete_volatile_container.hpp"

using namespace ara::crypto;

    ConcreteVolatileTrustedContainer::ConcreteVolatileTrustedContainer(std::size_t capacity,ConcreteIOInterface* instance)
    {
        ConcreteVolatileTrustedContainer::myinterface=instance;
       buffer.resize(capacity+5);        
    }

    ConcreteIOInterface& ConcreteVolatileTrustedContainer::GetIOInterface () const
    {
        return *ConcreteVolatileTrustedContainer::myinterface;
    }

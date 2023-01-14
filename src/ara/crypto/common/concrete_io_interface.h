//#ifndef ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
//#define ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
#pragma once

#include "concrete_volatile_container.h"
//#include "../cryp/concrete_crypto_provider.h"

namespace ara
{
    namespace crypto
	{
        //class cryp::ConcreteCryptoProvider;
        class ConcreteIOInterface : public IOInterface
		{
            //friend class cryp::ConcreteCryptoProvider;
        

        
      
		public:
        bool Volatile;
        bool session;
        AllowedUsageFlags AllowedUsage;
        CryptoObjectType objectType;
        CryptoObjectUid objectId;
        std::size_t capacity;
        std::size_t payloadSize;
        ara::crypto::CryptoAlgId algid;
        ara::crypto::CryptoObjectType objectTypeRestiction;
        std::vector<uint8_t> payload;
        ara::crypto::VolatileTrustedContainer::Uptr CreateVolatileContainer(std::size_t capacity);
        using Uptr = std::unique_ptr<ConcreteIOInterface>;       
        ConcreteIOInterface(bool, bool, ara::crypto::AllowedUsageFlags, ara::crypto::CryptoObjectType, ara::crypto::CryptoObjectUid, std::size_t, std::size_t, ara::crypto::CryptoAlgId, ara::crypto::CryptoObjectType);
        ConcreteIOInterface();
             AllowedUsageFlags GetAllowedUsage () const noexcept;

				 std::size_t GetCapacity () const noexcept;

				 CryptoObjectType GetCryptoObjectType () const noexcept;

				 CryptoObjectUid GetObjectId () const noexcept;

				 std::size_t GetPayloadSize () const noexcept;

				 CryptoAlgId GetPrimitiveId () const noexcept;

				 CryptoObjectType GetTypeRestriction () const noexcept;

				 bool IsObjectSession () const noexcept;

				 bool IsVolatile () const noexcept;

				 //~ConcreteIOInterface () noexcept;


        };
    }
}



//#endif
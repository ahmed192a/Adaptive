#ifndef ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
#define ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
#include "io_interface.hpp"
#include "../cryp/concrete_crypto_provider.hpp"

namespace ara
{
    namespace crypto
	{
        class ConcreteIOInterface : public IOInterface
		{
            friend class ara::crypto::cryp::ConcreteCryptoProvider
        bool Volatile;
        bool session;
        AllowedUsageFlags AllowedUsage;
        CryptoObjectType objectType;
        CryptoObjectUid objectId;
        std::size_t capacity;
        std::size_t payloadSize;

        ConcreteIOInterface(bool Volatilevar ,bool sessionvar,AllowedUsageFlags AllowedUsagevar,CryptoObjectType objectTypevar,CryptoObjectUid objectIdvar,std::size_t capacityvar,std::size_t payloadSizevar)
        {
            Volatile=Volatilevar;
            session=sessionvar;
            AllowedUsage=AllowedUsagevar;
            objectType=objectTypevar;
            objectId=objectIdvar;
            capacity=capacityvar;
            payloadSize=payloadSizevar;
        }
        VolatileTrustedContainer::Uptr CreateVolatileContainer(std::size_t capacity=0);
      
		public:
             AllowedUsageFlags GetAllowedUsage () const noexcept=0;

				 std::size_t GetCapacity () const noexcept=0;

				 CryptoObjectType GetCryptoObjectType () const noexcept=0;

				 CryptoObjectUid GetObjectId () const noexcept=0;

				 std::size_t GetPayloadSize () const noexcept=0;

				 CryptoAlgId GetPrimitiveId () const noexcept=0;

				 CryptoObjectType GetTypeRestriction () const noexcept=0;

				 bool IsObjectSession () const noexcept=0;

				 bool IsVolatile () const noexcept=0;

				 ~ConcreteIOInterface () noexcept=default;


        }
    }
}



#endif
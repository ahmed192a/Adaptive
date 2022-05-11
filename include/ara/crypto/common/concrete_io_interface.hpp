//#ifndef ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
//#define ARA_CRYPTO_CONCRETE_IO_INTERFACE_HPP_
#pragma once

#include "concrete_volatile_container.hpp"
//#include "../cryp/concrete_crypto_provider.hpp"

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
	bool ExportAllowed_t;
        bool AllowContentTypeChange_t;
        bool AllocateSpareSlot_t;
        bool IOInterface_State_Empty;
        std::int32_t MaxUpdateAllowed_t;
        KeySlotType Slot_Type;
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
        ConcreteIOInterface(ara::crypto::KeySlotType,std::int32_t,bool  , bool ,bool ,bool,bool,bool,AllowedUsageFlags,CryptoObjectType,CryptoObjectUid,std::size_t,std::size_t,CryptoAlgId,CryptoObjectType);
       // ConcreteIOInterface();
             AllowedUsageFlags GetAllowedUsage () const noexcept;

				 std::size_t GetCapacity () const noexcept;

				 CryptoObjectType GetCryptoObjectType () const noexcept;

				 CryptoObjectUid GetObjectId () const noexcept;

				 std::size_t GetPayloadSize () const noexcept;

				 CryptoAlgId GetPrimitiveId () const noexcept;

				 CryptoObjectType GetTypeRestriction () const noexcept;

				 bool IsObjectSession () const noexcept;

				 bool IsVolatile () const noexcept;
				 bool IsExportAllowed() const noexcept;
                 		 bool IsAllowContentTypeChange() const noexcept;
                 		 bool IsAllocateSpareSlot() const noexcept;
                 		 bool IsIOInterface_State_Empty() const noexcept;
                 		 std::int32_t GetMaxUpdateAllowed() const noexcept;
                 		 KeySlotType GetSlotType() const noexcept;

				 ~ConcreteIOInterface () noexcept;


        };
    }
}



//#endif

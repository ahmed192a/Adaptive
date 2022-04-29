#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_HPP
#define ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_HPP
#include <iostream>
#include <memory>
#include <vector>
#include "../cryp/cryobj/crypto_object.hpp"

namespace ara
{
	namespace crypto
	{
		namespace keys
		{

		/* 
		@brief: Structure contain a Prototyped Properties of a Key Slot.
		*/

		struct KeySlotPrototypeProps {
		    
		    /*
		    @brief: Cryptoalgorithm restriction (kAlgIdAny means without restriction). The algorithm can be specified partially: family & length, mode, padding.
		    */
		    CryptoAlgId mAlgId;
		    
		    /*
		    @brief: Indicates whether FC Crypto shall allocate sufficient storage space for a shadow copy of this KeySlot.
		    */
		    bool mAllocateSpareSlot;
		    
		    /*
		    @brief: Indicates whether the content of this key-slot may be changed.
		    */
		    bool mAllowContentTypeChange;
		    
		    /*
		    @brief: Indicates how the content may be used.
		    */
		    AllowedUsageFlags mContentAllowedUsage;
		    
		    /*
		    @brief: Indicates whether the key-slot content may be exported.
		    */
		    bool mExportAllowed;
		    
		    /*
		    @brief: Specifies how many times this key-slot may be updated.
		    */
		    std::int32_t mMaxUpdateAllowed;
		    
		    /*
		    @brief: Key-slot type configuration. 
		    */
		    KeySlotType mSlotType;
		    
		    /*
		    @brief: Capacity of the slot in bytes.
		    */
		    std::size_t mSlotCapacity;
		    
		    /*
		    @brief: Restriction of an object type that can be stored the slot. If this field contains CryptoObjectType::kUnknown then without restriction of the type.
		    */
		    CryptoObjectType mObjectType;
		    

		};
		
		using Uptr = std::unique_ptr<KeySlotPrototypeProps>;
		
		}
	}
}




#endif /* ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_HPP */

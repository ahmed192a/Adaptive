#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_HPP
#define ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_HPP
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

		//## A structure contains all the properties of the key slot.
		struct KeySlotContentProps {
			
			//Cryptoalgorithm of actual object stored to the slot.
				CryptoAlgId mAlgId;

			//Actual size of an object currently stored to the slot.
				std::size_t mObjectSize;

			//Actual type of an object stored to the slot.
				CryptoObjectType mObjectType;

			//UID of a Crypto Object stored to the slot.
				CryptoObjectUid mObjectUid;

			//Actual usage restriction flags of an object stored to the slot for the current "Actor".
				AllowedUsageFlags mContentAllowedUsage;
				/**
				 * @brief unique pointer
				 * 
				 */
			using Uptr = std::unique_ptr<KeySlotContentProps>;
			/**
			 * @brief Construct a new Key Slot Content Props object
			 * 
			 */
			KeySlotContentProps ()=default;
			/**
			 * @brief Comparison operator "equal" for KeySlotContentProps operands.
			 * 
			 * @param lhs 
			 * @param rhs 
			 * @return true 
			 * @return false 
			 */
			friend bool operator== (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept;
			
			/**
			 * @brief Comparison operator "not equal" for KeySlotContentProps operands.
			 * 
			 * @param lhs 
			 * @param rhs 
			 * @return true 
			 * @return false 
			 */
			friend bool operator!= (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept;




			};
		
		}
	}
}




#endif /* ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_HPP */
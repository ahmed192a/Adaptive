#include"ara/crypto/keys/key_slot_content_props.hpp"


#include <iostream>
namespace ara
{ 
    namespace crypto
    {
        namespace keys
        {
            /**
			 * @brief Comparison operator "equal" for KeySlotContentProps operands.
			 * 
			 * @param lhs 
			 * @param rhs 
			 * @return true 
			 * @return false 
			 */
			bool operator== (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept
            {
                if
                (
                    lhs.mAlgId == rhs.mAlgId &&
                    lhs.mContentAllowedUsage==rhs.mContentAllowedUsage &&
                    lhs.mObjectSize == rhs.mObjectSize &&
                    lhs.mObjectType == rhs.mObjectType&&
                    lhs.mObjectUid.mGeneratorUid.mQwordLs == rhs.mObjectUid.mGeneratorUid.mQwordLs &&
                    lhs.mObjectUid.mGeneratorUid .mQwordMs== rhs.mObjectUid.mGeneratorUid.mQwordMs &&
                    lhs.mObjectUid.mVersionStamp == rhs.mObjectUid.mVersionStamp
                )
                {
                    return true;
                }
                else
                {
                    return false ;
                }
            }
			
			/**
			 * @brief Comparison operator "not equal" for KeySlotContentProps operands.
			 * 
			 * @param lhs 
			 * @param rhs 
			 * @return true 
			 * @return false 
			 */
			bool operator!= (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept
            {
                if
                (
                    lhs.mAlgId == rhs.mAlgId &&
                    lhs.mContentAllowedUsage==rhs.mContentAllowedUsage &&
                    lhs.mObjectSize == rhs.mObjectSize &&
                    lhs.mObjectType == rhs.mObjectType&&
                    lhs.mObjectUid.mGeneratorUid.mQwordLs == rhs.mObjectUid.mGeneratorUid.mQwordLs &&
                    lhs.mObjectUid.mGeneratorUid .mQwordMs== rhs.mObjectUid.mGeneratorUid.mQwordMs &&
                    lhs.mObjectUid.mVersionStamp == rhs.mObjectUid.mVersionStamp
                )
                {
                    return false;
                }
                else
                {
                    return true ;
                }
            }
        }
    }
}

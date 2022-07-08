#include "ara/crypto/keys/key_slot_prototype_props.hpp"
#include <iostream>

 namespace ara
 { 
     namespace crypto
     {
         namespace keys
         {
             /**
 		         	 * @brief Comparison operator "equal" for KeySlotPrototypeProps operands.
 	         		 * 
 	         		 * @param lhs 
          			 * @param rhs 
          			 * @return true 
          			 * @return false 
 	         		 */
             bool operator== (const KeySlotPrototypeProps &lhs, const KeySlotPrototypeProps &rhs) noexcept
             {
                 if
                 (
                     lhs.mAlgId == rhs.mAlgId &&
                     lhs.mAllocateSpareSlot == rhs.mAllocateSpareSlot &&
                     lhs.mAllowContentTypeChange == rhs.mAllowContentTypeChange &&
                     lhs.mContentAllowedUsage == rhs.mContentAllowedUsage &&
                     lhs.mExportAllowed == rhs.mExportAllowed &&
                     lhs.mMaxUpdateAllowed == rhs.mMaxUpdateAllowed &&
                     lhs.mObjectType == rhs.mObjectType &&
                     lhs.mSlotCapacity == rhs.mSlotCapacity &&
                     lhs.mSlotType == rhs.mSlotType
                 )
                 {
                    return true;
                 }
                 else
                 {
                     return false;
                 }
             }
             /**
 			 * @brief Comparison operator "not equal" for KeySlotPrototypeProps operands.
 			 * 
 			 * @param lhs 
 			 * @param rhs 
 			 * @return true 
 			 * @return false 
 			 */
             bool operator!= (const KeySlotPrototypeProps &lhs, const KeySlotPrototypeProps &rhs) noexcept
             {
                 if
                 (
                     lhs.mAlgId == rhs.mAlgId &&
                     lhs.mAllocateSpareSlot == rhs.mAllocateSpareSlot &&
                     lhs.mAllowContentTypeChange == rhs.mAllowContentTypeChange &&
                     lhs.mContentAllowedUsage == rhs.mContentAllowedUsage &&
                     lhs.mExportAllowed == rhs.mExportAllowed &&
                     lhs.mMaxUpdateAllowed == rhs.mMaxUpdateAllowed &&
                     lhs.mObjectType == rhs.mObjectType &&
                     lhs.mSlotCapacity == rhs.mSlotCapacity &&
                     lhs.mSlotType == rhs.mSlotType
                 )
                 {
                     return false;
                 }
                 else
                 {
                     return true;
                 }

             }
         }
     }
 }

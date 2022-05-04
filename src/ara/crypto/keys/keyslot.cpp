#include "ara/crypto/keys/keyslot.hpp"

#include <iostream>
namespace ara
{
    namespace crypto
    {
        /*Save the content of a provided source IOInterface to this key - slot*/
        void keys::SaveCopy(const IOInterface& container) noexcept
        { 
            //Key Slot Content Properties Struct variables //
           KeyContent.mAlgId = container.GetPrimitiveId();
           KeyContent.mObjectType = container.GetCryptoObjectType();
           KeyContent.mObjectUid = container.GetObjectId();
           KeyContent.mContentAllowedUsage = container.GetAllowedUsage();
           KeyContent.mObjectSize = container.GetCapacity();//shall return capacity of the underlying resource in bytes//
           //Key Slot Prototypes Struct variables//
           KeySlotProps.mSlotCapacity= container.GetCapacity();//shall return capacity of the underlying resource in bytes//
           KeySlotProps.mSlotType = container.Slot_Type;
           KeySlotProps.mAlgId = container.GetPrimitiveId();
           KeySlotProps.mAllocateSpareSlot = container.AllocateSpareSlot_t;
           KeySlotProps.mAllowContentTypeChange = container.AllowContentTypeChange_t;
           KeySlotProps.mMaxUpdateAllowed = container.MaxUpdateAllowed_t;
           KeySlotProps.mExportAllowed=container.ExportAllowed_t;
           KeySlotProps.mContentAllowedUsage=container.GetAllowedUsage();
           KeySlotProps.mObjectType = container.GetTypeRestriction();


        //the slot will be updated only after correspondent call of CommitTransaction()//
            KeyStorageProvider::CommitTransaction();

        
        }
    }
}

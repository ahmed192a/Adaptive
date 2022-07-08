 #include "../../../../include/ara/crypto/keys/KSP_key_storage_provider.hpp"

 using namespace ara::crypto;
 using namespace ara::crypto::keys;

 ///@breif: Begin new transaction for key slots update
 TransactionId KSPKeyStorageProvider::BeginTransaction( TransactionScope& targetSlots) noexcept
 {
     //
 	 //define a flag which states wheter an error raised or not
     bool error = false;
     //define a counter to use it in the for loop
 	 uint8_t counter = 0;

     //a vector stores all IOInterfaces of this transactionScope
     std::vector < ConcreteIOInterface::Uptr> thisScopeInterfaces;

 	 //loop on every key slot in the Transactionscope to be sure that it has not already been opened before
 	 for (counter = 0; counter < targetSlots.size(); counter++)
 	 {
         if (targetSlots[counter].state != SlotState::opened)
         {
             //Open each key slot for updates
             thisScopeInterfaces.push_back(std::move((targetSlots[counter]).Open(1, 1)));
             

         }
         else
         {
             //raise CryptoErrorDomain::kBusyResource error
             error = true;
             break;
         }
		
 	 }

     if (error == false)
     {
	    //add the vector of IOInterfaces of this transactionScope to the vector of IOInterfaces of all scopes
         (this->TransactionIOInterfaces).push_back(std::move(thisScopeInterfaces));
	     
         //Assign the Id of this transaction 
         TransactionId TransId = this->nextId;

         //increment nextId for the next assignment
         (this->nextId)++;

         //Push this opened transaction to the vector of opened transactions
         this->transactionIdState.push_back({ std::move(targetSlots),TransId,TransactionScopeState::opened });

         return TransId;
     }
     else
     {
         //an error
         return 0;
     }
         
 }



 //@breif: Commit changes of the transaction to Key Storage
 void KSPKeyStorageProvider::CommitTransaction(TransactionId id) noexcept
 {
     //define an error flag
     uint8_t error = 0;

     //define a counter to use it in the foor loop
     uint8_t Transactionscounter = 0;
     uint8_t TransactionScopecounter = 0;

     // loop on every key slot in the TransactionScope to be sure that it has been opened 
     for (Transactionscounter = 0; Transactionscounter < this->transactionIdState.size(); Transactionscounter++)
     {
         // find the selected TransactionScope correspondant to the provided transactionId
         if (transactionIdState[Transactionscounter].transactionId == id)
         {
             //check that the TransactionScope correspondant to the provided transactionId is ready to be commited
             if (transactionIdState[Transactionscounter].transactionState != TransactionScopeState::opened)
             {
                 error = 1;
             }
             // required id found so break from searching loop
             break;
         }
     }
     if (error == 0)
     {
         // exract the selected TransactionScope correspondant to the provided transactionId
         TransactionScope TransactionsToBeCommited = std::move(this->transactionIdState[Transactionscounter].transaction);

         // save the changes to the correspondant key slot
         for (TransactionScopecounter = 0; TransactionScopecounter < TransactionsToBeCommited.size(); TransactionScopecounter++)
         {
             TransactionsToBeCommited[TransactionScopecounter].SaveCopy(*(this->TransactionIOInterfaces[Transactionscounter][TransactionScopecounter]));
         }

         // change the state of the committed transaction from opened to committed
         transactionIdState[Transactionscounter].transactionState = TransactionScopeState::commited;
     }
     else
     {
         /* Misra */
     }
     
 }


//////@breif: Load a key slot
////// The function loads the information associated with a KeySlot into a KeySlot object
KeySlot::Uptr KSPKeyStorageProvider::LoadKeySlot(ara::core::InstanceSpecifier &iSpecify) noexcept
{
    //first checking if the input is already existing or not 

     //struct dirent *d;
     //struct stat dst;
    std::string temp = iSpecify.stringview;
    std::string given_type = temp + ".txt";

    //DIR *dr;
    bool FOUND_FLAG = 0;

    std::cout << my_path << std::endl;
    //dr = opendir(my_path.c_str());
    std::string file_location;
    file_location = my_path + given_type;

    //reading the text file 
    KeySlot::Uptr returned_KeySlot = std::make_unique<InhKeySlot>();

    std::ifstream infile(file_location);

    if (infile.is_open())
    {
        std::string line;
        while (std::getline(infile, line))
        {
            size_t found = line.find("=");
            size_t length = line.length();
            if (found != std::string::npos)
            {
                std::string z;
                std::string tempp;
                std::string a = line.substr(0, found);
                std::cout << a << "   " << length << std::endl;
                TextVariables x = String_to_enum(a);
                std::string b = line.substr(found + 1, 1);
                std::cout << found << "\t";
                if (b == " ")
                {
                    found++;
                    std::cout << found << std::endl;
                }
                z = line.substr(found + 1, (length - found));
                std::cout << z << "\t" << stoi(z) << std::endl;
                switch (x)
                {
                case(KSCP_mAlgId):
                    returned_KeySlot->KSCP.mAlgId = stoi(z);
                    break;
                case(KSCP_mObjectType):
                    returned_KeySlot->KSCP.mObjectType = CryptoObjectType(stoi(z));
                    break;
                case(KSCP_mObjectUid_mGeneratorUid_mQwordLs):
                    returned_KeySlot->KSCP.mObjectUid.mGeneratorUid.mQwordLs = stoi(z);
                    break;
                case(KSCP_mObjectUid_mGeneratorUid_mQwordMs):
                    returned_KeySlot->KSCP.mObjectUid.mGeneratorUid.mQwordMs = stoi(z);
                    break;
                case(KSCP_mObjectUid_mVersionStamp):
                    returned_KeySlot->KSCP.mObjectUid.mVersionStamp = stoi(z);
                    break;
                case(KSCP_mContentAllowedUsage):
                    returned_KeySlot->KSCP.mContentAllowedUsage = stoi(z);
                    break;
                case(KSCP_mObjectSize):
                    returned_KeySlot->KSCP.mObjectSize = stoi(z);
                    break;
                case(KSPP_mSlotCapacity):
                    returned_KeySlot->KSPP.mSlotCapacity = stoi(z);
                    break;
                case(KSPP_mSlotType):
                    returned_KeySlot->KSPP.mSlotType = KeySlotType(stoi(z));
                    break;
                case(KSPP_mAlgId):
                    returned_KeySlot->KSPP.mAlgId = stoi(z);
                    break;
                case(KSPP_mAllocateSpareSlot):
                    returned_KeySlot->KSPP.mAllocateSpareSlot = stoi(z);
                    break;
                case(KSPP_mAllowContentTypeChange):
                    returned_KeySlot->KSPP.mAllowContentTypeChange = stoi(z);
                    break;
                case(KSPP_mMaxUpdateAllowed):
                    returned_KeySlot->KSPP.mMaxUpdateAllowed = stoi(z);
                    break;
                case(KSPP_mExportAllowed):
                    returned_KeySlot->KSPP.mExportAllowed = stoi(z);
                    break;
                case(KSPP_mContentAllowedUsage):
                    returned_KeySlot->KSPP.mContentAllowedUsage = stoi(z);
                    break;
                case(KSPP_mObjectType):
                    returned_KeySlot->KSPP.mObjectType = CryptoObjectType(stoi(z));
                    break;
                }
            }
        }
        infile.close();
    }
    return returned_KeySlot;
}

//function to convert the string into enum for using it in a switch case statement 
TextVariables KSPKeyStorageProvider::String_to_enum(std::string a)
{
    if (a == "KSCP.mAlgId" || a == "KSCP.mAlgId ")
        return KSCP_mAlgId;
    else if (a == "KSCP.mObjectType" || a == "KSCP.mObjectType ")
        return KSCP_mObjectType;
    else if (a == "KSCP.mObjectUid.mGeneratorUid.mQwordLs" || a == "KSCP.mObjectUid.mGeneratorUid.mQwordLs ")
        return KSCP_mObjectUid_mGeneratorUid_mQwordLs;
    else if (a == "KSCP.mObjectUid.mGeneratorUid.mQwordMs" || a == "KSCP.mObjectUid.mGeneratorUid.mQwordMs ")
        return KSCP_mObjectUid_mGeneratorUid_mQwordMs;
    else if (a == "KSCP.mObjectUid.mVersionStamp" || a == "KSCP.mObjectUid.mVersionStamp ")
        return KSCP_mObjectUid_mVersionStamp;
    else if (a == "KSCP.mContentAllowedUsage" || a == "KSCP.mContentAllowedUsage ")
        return KSCP_mContentAllowedUsage;
    else if (a == "KSCP.mObjectSize" || a == "KSCP.mObjectSize ")
        return KSCP_mObjectSize;
    else if (a == "KSPP.mSlotCapacity" || a == "KSPP.mSlotCapacity ")
        return KSPP_mSlotCapacity;
    else if (a == "KSPP.mSlotType" || a == "KSPP.mSlotType ")
        return KSPP_mSlotType;
    else if (a == "KSPP.mAlgId" || a == "KSPP.mAlgId ")
        return KSPP_mAlgId;
    else if (a == "KSPP.mAllocateSpareSlot" || a == "KSPP.mAllocateSpareSlot ")
        return KSPP_mAllocateSpareSlot;
    else if (a == "KSPP.mAllowContentTypeChange" || a == "KSPP.mAllowContentTypeChange ")
        return KSPP_mAllowContentTypeChange;
    else if (a == "KSPP.mMaxUpdateAllowed" || a == "KSPP.mMaxUpdateAllowed ")
        return KSPP_mMaxUpdateAllowed;
    else if (a == "KSPP.mExportAllowed" || a == "KSPP.mExportAllowed ")
        return KSPP_mExportAllowed;
    else if (a == "KSPP.mContentAllowedUsage" || a == "KSPP.mContentAllowedUsage ")
        return KSPP_mContentAllowedUsage;
    else if (a == "KSPP.mObjectType" || a == "KSPP.mObjectType ")
        return KSPP_mObjectType;
}




///@breif: Rollback all changes executed during the transaction in Key Storage.
//The rollback command permanently cancels all changes made during the transaction in Key Storage.
//A rolled back transaction is completely invisible for all applications.
 void KSPKeyStorageProvider::RollbackTransaction(TransactionId id) noexcept
 {
     //counters for the loop
     uint8_t OpenedTransactionscounter, SlotCounter;
     //a flag to detect when the code exits without finding the provided id
     uint8_t flag = 0;

     //loop on every opened transaction to find the one to rollback
     for (OpenedTransactionscounter = 1; OpenedTransactionscounter < this->spareOpenedTransactions.size(); OpenedTransactionscounter++)
     {
         if (this->spareOpenedTransactions[OpenedTransactionscounter].transactionId == id)
         {
             TransactionScope requiredTransaction = std::move(this->spareOpenedTransactions[OpenedTransactionscounter].transaction);
             flag = 1;
             /*if provided id is invalid, i.e. correspondent transaction already was finished (committed or rolled back),
              *an error is signaled*/
             if ((this->spareOpenedTransactions[OpenedTransactionscounter].transactionState == TransactionScopeState::commited) || (this->spareOpenedTransactions[OpenedTransactionscounter].transactionState == TransactionScopeState::rolledback))
             {
                 //raising SecurityErrorDomain::kInvalid Argument
             }
             else
             {
                 // loop on every key slot in the Transactionscope to remove the changes & rollback
                 for (SlotCounter = 0; SlotCounter < requiredTransaction.size(); SlotCounter++)
                 {
                     //Open each key slot spare & save it to roll back any changes that occurred)
                     ConcreteIOInterface::Uptr IOInterfacePtr = std::move(requiredTransaction[SlotCounter].Open(1, 1));
                     requiredTransaction[SlotCounter].SaveCopy(*IOInterfacePtr);
                 }
                 //change the state of the transaction to rolledback so that it won't be rolled back again
                 this->spareOpenedTransactions[OpenedTransactionscounter].transactionState = TransactionScopeState::rolledback;
             }
         }
     }
     /*if provided id is invalid, i.e. this ID is unknown (not found), an error is signaled*/
     if (flag == 0)
     {
         //raising SecurityErrorDomain::kInvalid Argument
     }
 }


 ///@breif: Get a vector of IOInterface from a Transaction id.
 std::vector<ConcreteIOInterface::Uptr> KSPKeyStorageProvider::GetIOInterfaceFromid(TransactionId id) noexcept
 {
     //counters for the loops
     uint8_t OpenedTransactionscounter, SlotCounter;

     //vector of IOInterfaces of the required transaction to be returned
     std::vector<ConcreteIOInterface::Uptr> IOContent;
     //loop on every opened transaction to find the one to retrieve its key slots' IOInterfaces
     for (OpenedTransactionscounter = 1; OpenedTransactionscounter < this->transactionIdState.size(); OpenedTransactionscounter++)
     {
         if (this->transactionIdState[OpenedTransactionscounter].transactionId == id)
         {
             if (this->transactionIdState[OpenedTransactionscounter].transactionState == TransactionScopeState::opened)
             {
                 TransactionScope requiredTransaction = std::move(this->transactionIdState[OpenedTransactionscounter].transaction);
                 //loop on every key slot in the required Transactionscope to remove the changes & rollback
                 for (SlotCounter = 0; SlotCounter < requiredTransaction.size(); SlotCounter++)
                 {
                     IOContent.push_back(std::move(requiredTransaction[SlotCounter].IOInterfacePtr));

                 }
             }


         }
     }
     return IOContent;
 }


 InhKeySlot::Uptr KSPKeyStorageProvider::CreateNewKeySlot(std::string name)
 {
     std::ifstream my_file;
     my_file.open("keyslotsfile.txt");
     std::string lines;
     //my_file >> lines;
     //std::cout << lines;
     while (!my_file.eof())
     {
         //std::cout << "while entered\n";
         my_file >> lines;
         std::cout << lines;
         if (lines == name)
         {
             ara::core::InstanceSpecifier ins;
             ins.stringview = name;
             InhKeySlot::Uptr LoadedCreatedSlot = std::move(LoadKeySlot(ins));
             return LoadedCreatedSlot;
         }

     }
     
     InhKeySlot::Uptr newCreatedSlot = std::make_unique<InhKeySlot>(name);
     return newCreatedSlot;
 }


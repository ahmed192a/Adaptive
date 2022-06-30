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
 ////KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept
 ////{
	////
 ////}


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
                     IOInterface::Uptr IOInterfacePtr = requiredTransaction[SlotCounter].Open(1, 1);
                     /******************************* this line needs syntax correction ****************************/
                     //requiredTransaction[SlotCounter].SaveCopy(&(*IOInterfacePtr));
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
                     IOContent.push_back(requiredTransaction[SlotCounter].IOInterfacePtr);

                 }
             }


         }
     }
     return IOContent;
 }


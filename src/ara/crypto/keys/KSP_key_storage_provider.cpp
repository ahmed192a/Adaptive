#include "../../../../include/ara/crypto/keys/KSP_key_storage_provider.hpp"

using namespace ara::crypto;
using namespace ara::crypto::keys;

//@breif: Begin new transaction for key slots update
TransactionId KSPKeyStorageProvider::BeginTransaction(const TransactionScope& targetSlots) noexcept
{
	//define a counter to use it in the foor loop
	uint8_t counter = 0;

	// loop on every key slot in the Transactionscope to be sure that it has not already been opened before
	for (counter = 0; counter < targetSlots.size(); counter++)
	{
		if (targetSlots[counter].state != SlotState::opened)
		{
			// Open each key slot for updates
			targetSlots[counter].Open(1, 1);
		}
		
		else
		{
			// raise CryptoErrorDomain::kBusyResource error
			break;
		}
	}

	// Assign the Id of this transaction 
	TransactionId TransId = this->nextId;

	//increment nextId for the next assignment
	(this->nextId)++;

	// Push this opened transaction to the vector of opened transactions
	this->openedTransactionsWithIds.push_back({ targetSlots,TransId});

	return TransId;
}

//@breif: Commit changes of the transaction to Key Storage
void KSPKeyStorageProvider:: CommitTransaction(TransactionId id) noexcept
{
	//define a counter to use it in the foor loop
	uint8_t OpenedTransactionscounter = 0;
	uint8_t TransactionScopecounter = 0;

	// loop on every key slot in the TransactionScope to be sure that it has been opened 
	for (OpenedTransactionscounter = 0; OpenedTransactionscounter < this->openedTransactionsWithIds.size();
		OpenedTransactionscounter++)
	{
		if (openedTransactionsWithIds[OpenedTransactionscounter].OpenedTransactionId == id)
		{
			break;
		}
		
		// exract the selected TransactionScope correspondant to the provided transactionId
		TransactionScope TransactionsToBeCommited = this->openedTransactionsWithIds[OpenedTransactionscounter].OpenedTransaction;
		
		// save the changes to the correspondant key slot
		for (TransactionScopecounter = 0; TransactionScopecounter < TransactionsToBeCommited.size(); TransactionScopecounter++)
		{
			TransactionsToBeCommited[TransactionScopecounter].SaveCopy(*(TransactionsToBeCommited[TransactionScopecounter].IOInterfacePtr));
		}
		
		// remove the committed transaction from the opened transaction vector
		openedTransactionsWithIds.erase(openedTransactionsWithIds.begin()+ OpenedTransactionscounter);

	}

}


//@breif: Load a key slot
// The function loads the information associated with a KeySlot into a KeySlot object
KeySlot::Uptr LoadKeySlot(ara::core::InstanceSpecifier& iSpecify) noexcept
{
	
}


//@breif: Rollback all changes executed during the transaction in Key Storage.
// The rollback command permanently cancels all changes made during the transaction in Key Storage.
// A rolled back transaction is completely invisible for all applications.
void RollbackTransaction(TransactionId id) noexcept
{
	//counters for the loop
	uint8_t OpenedTransactionscounter, SlotCounter;
	//a flag to detect when the code exits without finding the provided id
	uint8_t flag = 0;
	
	//loop on every opened transaction to find the one to rollback
	for (OpenedTransactionscounter = 1; OpenedTransactionscounter < this->spareOpenedTransactions.size(); OpenedTransactionscounter++)
	{
		if (this->spareOpenedTransactions[OpenedTransactionscounter].OpenedTransactionId == id)
		{
			TransactionScope requiredTransaction = this->spareOpenedTransactions[OpenedTransactionscounter].OpenedTransaction;
			flag = 1;
			/*if provided id is invalid, i.e. correspondent transaction already was finished (committed or rolled back),
			 *an error is signaled*/
			if (this->spareOpenedTransactions[OpenedTransactionscounter].OpenedTransactionState == TransactionScopeState::commited || this->spareOpenedTransactions[OpenedTransactionscounter].OpenedTransactionState == TransactionScopeState::rolledback)
			{
				//raising SecurityErrorDomain::kInvalid Argument
			}
			else
			{
				// loop on every key slot in the Transactionscope to remove the changes & rollback
				for (SlotCounter = 0; SlotCounter < requiredTransaction.OpenedTransaction.size(); SlotCounter++)
				{
					//Open each key slot spare & save it to roll back any changes that occurred)
					IOInterface::Uptr IOInterfacePtr = requiredTransaction[SlotCounter].Open(1, 1);
					requiredTransaction[SlotCounter].SaveCopy(IOInterfacePtr);
				}
				//change the state of the transaction to rolledback so that it won't be rolled back again
				this->spareOpenedTransactions[OpenedTransactionscounter].OpenedTransactionState = TransactionScopeState::rolledback;
			}
		}
	}
	/*if provided id is invalid, i.e. this ID is unknown (not found), an error is signaled*/
	if (flag == 0)
	{	
		//raising SecurityErrorDomain::kInvalid Argument
	}
}


//@breif: Get a vector of IOInterface from a Transaction id.
vector<IOInterface::Uptr> GetIOInterfaceFromid(TransactionId id) noexcept
{
	//counters for the loops
	uint8_t OpenedTransactionscounter, SlotCounter;

	//loop on every opened transaction to find the one to retrieve its key slots' IOInterfaces
	for (OpenedTransactionscounter = 1; OpenedTransactionscounter < this->openedTransactionsWithIds.size(); OpenedTransactionscounter++)
	{
		if (this->openedTransactionsWithIds[OpenedTransactionscounter].OpenedTransactionId == id)
		{
			TransactionScope requiredTransaction = this->openedTransactionsWithIds[OpenedTransactionscounter].OpenedTransaction;
			//loop on every key slot in the required Transactionscope to remove the changes & rollback
			for (SlotCounter = 0; SlotCounter < requiredTransaction.size(); SlotCounter++)
			{
				//push the IOInterfaces to the vector
				this->TransactionIOInterfaces.push_back(requiredTransaction[SlotCounter].IOInterfacePtr);

			}
			
		}	
	}
	return this->TransactionIOInterfaces;
}

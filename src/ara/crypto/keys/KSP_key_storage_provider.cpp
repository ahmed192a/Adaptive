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
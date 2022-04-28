#include "../../../../include/ara/crypto/keys/KSP_key_storage_provider.hpp"

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
	uint8_t counter = 0;

	// loop on every key slot in the TransactionScope to be sure that it has been opened 
	for (counter = 0; counter < this->openedTransactionsWithIds.size(); counter++)
	{
		if (openedTransactionsWithIds[counter].OpenedTransactionId == id)
		{
			break;
		}

		/////////////////////////////////////////////////////////////////
		/*********************** Save the changes **********************/
		/////////////////////////////////////////////////////////////////

		// remove the committed transaction from the opened transaction vector
		openedTransactionsWithIds.erase(openedTransactionsWithIds.begin()+counter);

	}

}
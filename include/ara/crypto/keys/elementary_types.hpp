// #ifndef ARA_CRYPTO_KEYS_ELEMENTARY_ELEMENTS_HPP
// #define ARA_CRYPTO_KEYS_ELEMENTARY_ELEMENTS_HPP

// #include <vector>
// #include "keyslot.hpp"

// namespace ara
// {
// 	namespace crypto
// 	{
// 		namespace keys
// 		{

// 			//@breif: Definition of a transaction identifier type. 
// 			// The zero value should be reserved for especial cases.
// 			using TransactionId = std::uint64_t;

// 			//@breif: The "transaction scope" is a list of key slots that are target for update in a transaction
// 			using TransactionScope = std::vector<KeySlot>;

// 			/************************************************************************************/
// 			/********* Not in SWS so may be remeoved later if better solution is found **********/
// 			/************************************************************************************/
			
// 			enum class TransactionScopeState : std::uint8_t
// 			{
// 				opened,
// 				commited,
// 				rolledback
// 			};

// 			//@breif: a pair to keep track of opened TransactionScopes which are ready to be commited with changes 
// 			//        combined with their TransactionId s
// 			struct OpenedTransactionScopeWithIdPair
// 			{
// 				TransactionScope OpenedTransaction;
// 				TransactionId OpenedTransactionId;
// 				TransactionScopeState OpenedTransactionState;
// 			};
// 		}
// 	}
// }

// #endif
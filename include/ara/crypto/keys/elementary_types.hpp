 #ifndef ARA_CRYPTO_KEYS_ELEMENTARY_ELEMENTS_HPP
 #define ARA_CRYPTO_KEYS_ELEMENTARY_ELEMENTS_HPP

#include <vector>
//#include "keyslot.hpp"
#include "Inher_key_slote.hpp"

 namespace ara
 {
 	namespace crypto
 	{
 		namespace keys
 		{

 			//@breif: Definition of a transaction identifier type. 
 			// The zero value should be reserved for especial cases.
 			using TransactionId = std::uint64_t;

 			//@breif: The "transaction scope" is a list of key slots that are target for update in a transaction
 			using TransactionScope = std::vector<InhKeySlot>;

 			/************************************************************************************/
 			/********* Not in SWS so may be remeoved later if better solution is found **********/
 			/************************************************************************************/
			
 			enum class TransactionScopeState : std::uint8_t
 			{
 				opened,
 				commited,
 				rolledback
 			};

 			//@breif: a struct to keep track of TransactionScopes commited with changes combined with 
            //        their TransactionId s, and stating whether these changes are ready to commited, 
            //        already committed, or rolled back
 			struct TransactionScopeWithIdAndState
 			{
 				TransactionScope Transaction;
 				TransactionId TransactionId;
 				TransactionScopeState TransactionState;
 			};
 		}
 	}
 }

 #endif
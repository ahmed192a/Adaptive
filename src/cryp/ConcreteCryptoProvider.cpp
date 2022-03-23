/*
 * ConcreteCryptoProvider.cpp
 *
 *  Created on: Mar 19, 2022
 *      Author: aliab
 */

#include "../../../../include/ara/crypto/cryp/concrete_crypto_provider.hpp"

using namespace ara::crypto::cryp;

CryptoProvider::AlgId ConcreteCryptoProvider::ConvertToAlgId (std::string primitiveName) 
{
	//check the list of algorithm names supported
	for(int i=0;i<ALGORITHMSNUMBER;i++)
	{
		if(primitiveName==algorithmNames[i])
			return i+1;
	}
	//if not found so return undefined
	return kAlgIdUndefined;
}


 std::string ConcreteCryptoProvider::ConvertToAlgName (CryptoProvider::AlgId algId)
 {
	 //check if algId contains supported value
	 if(algId==0||algId>ALGORITHMSNUMBER)
		 return "kUnknownIdentifier";

	 //return the common name saved in the supported algorithms list
	 return algorithmNames[algId-1];
 }
 MessageAuthnCodeCtx::Uptr ConcreteCryptoProvider::CreateMessageAuthCodeCtx (AlgId algId)
 {
	 //if the algId not supported
	 if(ConcreteCryptoProvider::ConvertToAlgName(algId)=="kUnkownIdentifier")
		 return std::make_unique<MessageAuthnCodeCtx>(nullptr);
	 //if the algId is not suitable for the MAC
	 if(algId!=1)
		 return std::make_unique<MessageAuthnCodeCtx>(nullptr);
	 //create the context according to the algId
	 if(algorithmNames[algId-1]=="HMACSHA_256")
		 return std::make_unique<HMAC>();
	 return std::make_unique<MessageAuthnCodeCtx>(nullptr);
 }

 //waiting for the implementation of the algorithms to complete the rest of functions

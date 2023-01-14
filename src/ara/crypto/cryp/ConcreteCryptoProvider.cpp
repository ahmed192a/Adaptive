/*
 * ConcreteCryptoProvider.cpp
 *
 *  Created on: Mar 19, 2022
 *      Author: aliab
 */

#include "ara/crypto/cryp/concrete_crypto_provider.h"

using namespace ara::crypto::cryp;

ara::crypto::VolatileTrustedContainer::Uptr ConcreteCryptoProvider::AllocVolatileContainer (std::size_t capacity) noexcept
{
	ConcreteIOInterface::Uptr ioptr= std::make_unique<ConcreteIOInterface>();
	return ioptr->CreateVolatileContainer(capacity);
}

CryptoProvider::AlgId ConcreteCryptoProvider::ConvertToAlgId (std::string primitiveName) const noexcept
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


 std::string ConcreteCryptoProvider::ConvertToAlgName (CryptoProvider::AlgId algId) const noexcept
 {
	 //check if algId contains supported value
	 if(algId==0||algId>ALGORITHMSNUMBER)
		 return "kUnknownIdentifier";

	 //return the common name saved in the supported algorithms list
	 return algorithmNames[algId-1];
 }
 HMAC::Uptr ConcreteCryptoProvider::CreateMessageAuthCodeCtx (AlgId algId) noexcept
 {
	 //if the algId not supported
	 if(ConcreteCryptoProvider::ConvertToAlgName(algId)=="kUnkownIdentifier")
		 return std::make_unique<HMAC>(nullptr);
	 //if the algId is not suitable for the MAC
	 if(algId!=1)
		 return std::make_unique<HMAC>(nullptr);
	 //create the context according to the algId
	 if(algorithmNames[algId-1]=="HMACSHA_256")
		 return std::make_unique<HMAC>(this);
	 return std::make_unique<HMAC>(nullptr);
 }

PRNG::Uptr ConcreteCryptoProvider::CreateRandomGeneratorCtx (CryptoProvider::AlgId algId, bool initialize) noexcept
{
	return std::make_unique<PRNG>(this);
}

HashService::Uptr ConcreteCryptoProvider::CreateHashFunctionCtx(CryptoProvider::AlgId) noexcept
{
	return std::make_unique<HashService>(this);
}
 SecSeed::Uptrc ConcreteCryptoProvider::GenerateSeed (CryptoProvider::AlgId algId, SecSeed::Usage allowedUsage, bool isSession, bool isExportable) noexcept
 {
	 SecSeed::Uptr pointer=std::make_unique<SecSeed>(allowedUsage,isSession,isExportable);
	 pointer->Seed=255;
	 PRNG::Uptr RNGPointer=ConcreteCryptoProvider::CreateRandomGeneratorCtx(0,true);
	 RNGPointer->Seed(*pointer);
	 pointer->Seed_val=RNGPointer->Generate(16);
	 return pointer;
 }
 ara::crypto::cryp::SymmetricCipher::Uptr ConcreteCryptoProvider::CreateSymmetricBlockCipherCtx (CryptoProvider::AlgId algId) noexcept
 {
	 SymmetricKey x;
	 return std::make_unique<ara::crypto::cryp::SymmetricCipher>(this,x);
 }
 SymmetricKey::Uptrc ConcreteCryptoProvider::GenerateSymmetricKey(CryptoProvider::AlgId algId, ara::crypto::AllowedUsageFlags allowedUsage, bool isSession=true,bool isExportable=false) noexcept
 {
	 SymmetricKey::Uptr pointer=std::make_unique<SymmetricKey>(allowedUsage,isSession,isExportable);
	 pointer->Seed=255;
	 PRNG::Uptr RNGPointer=ConcreteCryptoProvider::CreateRandomGeneratorCtx(0,true);
	 pointer->keyVal=RNGPointer->Generate(16);
	 return pointer;
 }

Keywrapper::Uptr ConcreteCryptoProvider::CreateSymmetricKeyWrapperCtx (CryptoProvider::AlgId algId) noexcept
{
	SymmetricKey::Uptrc key = ConcreteCryptoProvider::GenerateSymmetricKey(1,0xffff);
	return std::make_unique<Keywrapper>();
}

 std::vector<uint8_t>  ConcreteCryptoProvider::ExportPublicObject (const ara::crypto::ConcreteIOInterface &container) noexcept
 {
	 if(container.GetAllowedUsage()&0x0001==1)
	 return container.payload;
	 else{
		 //do nothing
		 return container.payload;
	 }
 }
 std::vector<uint8_t>  ConcreteCryptoProvider::ExportSecuredObject (const ara::crypto::ConcreteIOInterface &container, Keywrapper &transportContext) noexcept
 {
	 if(container.GetAllowedUsage()&0x0001==1)
	 {
	 SymmetricKey b;
	 b.keyVal=container.payload;
	 std::vector<uint8_t> a= transportContext.WrapKeyMaterial(b);
	 }
	 else{

	 } 
 }

 HKDF::Uptr ConcreteCryptoProvider::CreateKeyDerivationFunctionCtx(CryptoProvider::AlgId algid) noexcept
 {
	 return std::make_unique<HKDF>(this);
 }

 Authentication::Uptr ConcreteCryptoProvider::CreateAuthCipherCtx(CryptoProvider::AlgId algid) noexcept
 {	
	 return std::make_unique<Authentication>(this,ara::crypto::CryptoTransform::kEncrypt);
 }

 std::size_t ConcreteCryptoProvider::GetPayloadStorageSize(ara::crypto::CryptoObjectType cryptoObjecttype  ,CryptoProvider::AlgId algid)const noexcept
 {
	 //AES
	 if (algid==1)
	 return 16;
	 //HMAC and SHA and AuthenticatedCipher
	 else if(algid==2||algid==3)
	 return 64;
 }

 


 void ConcreteCryptoProvider::ImportPublicObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, CryptoObjectType expectedObject) noexcept
 {
	 container.payload=serialized;
 }
void ConcreteCryptoProvider::ImportSecuredObject (ConcreteIOInterface &container, ReadOnlyMemRegion serialized, Keywrapper &transportContext, bool isExportable, CryptoObjectType expectedObject) noexcept
{
	container.payload=serialized;
}


Sign::Uptrc ConcreteCryptoProvider::CreateSignature (CryptoProvider::AlgId signAlgId, ara::crypto::ReadOnlyMemRegion value, const RestrictedUseObject &key,CryptoProvider::AlgId hashAlgId) noexcept
{
	std::vector<uint8_t> a;
	return std::make_unique<Sign>(a);
}
	cryptoobj::Uptrc ConcreteCryptoProvider::LoadObject(const ConcreteIOInterface& Container) noexcept
	{
		return std::make_unique<cryptoobj>();
		
	}

	SymmetricKey::Uptrc ConcreteCryptoProvider::LoadSymmetricKey(const ConcreteIOInterface& Container) noexcept
	{
		SymmetricKey a;
		a.keyVal=Container.payload;
	}

	SecSeed::Uptrc ConcreteCryptoProvider::LoadSecretSeed(const ConcreteIOInterface& Container) noexcept
	{
		SecSeed a(0xffff,true,true);
		a.Seed_val=Container.payload;
	}





 

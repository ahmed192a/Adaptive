#include "ara/crypto/cryp/hash_service.hpp"
#include "ara/crypto/cryp/sha256.hpp"


using namespace ara::crypto::cryp;

/************************* HASHFUNCTIONCTX METHODS ***********************************/

/// @brief Initialize the context for a new data stream processing and clear current hashed value.
/// @returns 
void HashService::Start(){
    //clear stored hashed value..
    this->hashedValue.clear();
    //clear value to be hashed to be ready for another hashing process
    this->vectorToBeHashed.clear();

    //raise the init flag
    this->flagInit = 1;

    return;
    
}

/// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
/// @param[in] in part of input message processed (byte value to br processed)
void HashService::Update (uint8_t in)
{
    //update the value to be hashed with the input
    this->vectorToBeHashed.push_back(in); 

    return;
}


/// @brief Finish the digest calculation and optionally produce the "signature" object. Only after call of this method the digest can be signed, verified, extracted or compared.
/// @returns unique smart pointer to created signature object,
std::vector<byte> HashService::Finish()
{
    SHA256 hashingObject;
    hashingObject.add(this->vectorToBeHashed.data(), vectorToBeHashed.size());

    std::string hashedstr = hashingObject.getHash();

    for(std::uint8_t i = 0; i < 32; i++){
        this->hashedValue[i] = std::stoi(hashedstr.substr(i*2,2), nullptr, 16);
    }

    return this->hashedValue;
    
}


/// @brief Get DigestService instance.
/// @returns DigestService::Uptr
DigestService::Uptr HashService::GetDigestService() const 
{

}


/// @brief Get requested part of calculated digest.
/// @param[in] offset position of the first byte of digest that should be placed to the output buffer.
/// @returns number of digest bytes really stored to the output buffer
std::vector<byte> HashService::GetDigest (std::size_t offset=0) const 
{
    std::vector<byte> result;
    result.insert(result.begin(), this->hashedValue.begin()+offset, this->hashedValue.end())

    return result;


}


/// @brief Update the digest calculation context by a new part of the message. This method is dedicated for cases then the RestrictedUseObject is a part of the "message".
/// @param[in] in part of input message processed 
//void HashService::Update (ReadOnlyMemRegion in){

//}


/****************************** CRYPTOCONTEXT METHODS ***************************/
bool IsInitialized(){
    if(this->flagInit){
        return true;
    }
    else{
        return false;
    }

}

/*Return CryptoPrimitivId instance containing instance identification */
HashService::CryptoPrimitiveId::Uptr GetCryptoPrimitiveId() const {


}

/* Get a reference to Crypto Provider of this context*/
HashService::CryptoProvider& MyProvider() const {
    return *(this->myProvider);

}

HashService::HashService(CryptoProvider * provider){
    this->myProvider = provider;
}

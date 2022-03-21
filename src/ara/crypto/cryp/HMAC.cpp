#include "../../../../include/ara/crypto/cryp/HMAC.hpp"

using namespace ara::crypto::cryp;

/** Inherited from CryptoContext class**/

HMAC::HMAC(CryptoProvider * provider) {
    this->myProvider = provider;
}


bool HMAC::IsInitialized() {
    if(status == MessageAuthnCodeCtx_Status::notInitialized)
        return false;
    else
        return true;
}


// CryptoPrimitiveId::Uptr HMAC::GetCryptoPrimitiveId() const noexcept {

// }


CryptoProvider& HMAC::MyProvider() const noexcept {
    return (*myProvider) ;
}



/** Inherited from MessageAuthnCode class**/

void HMAC::Reset() {
    status = MessageAuthnCodeCtx_Status::notInitialized;
    signature_ptr = nullptr;

}

void HMAC::SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) {
        
    if(transform == CryptoTransform::kMacGenerate){
        // operations to check whether the key is valid or not
        this->key = key;
        status = MessageAuthnCodeCtx_Status::initialized;
    }
    else {
        // do nothing
    }
}

void HMAC::Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) {
    
    hashFunction = std::make_unique<HashFunctionCtx>(); // creating the needed algorithm
    status == MessageAuthnCodeCtx_Status::started; // change to the new state
}

void HMAC::Update(std::uint8_t in) {

}

// Signature::Uptrc HMAC::Finish(bool makeSignatureObject = false) noexcept {
//     if(makeSignatureObject == false)
//         return std::make_unique<Signature>(nullptr);
//     else
//         return std::make_unique<Signature>(); // should be initialized with the correct value
// }
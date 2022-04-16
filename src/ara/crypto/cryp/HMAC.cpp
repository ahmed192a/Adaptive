#include "ara/crypto/cryp/HMAC.hpp"
#include "ara/crypto/cryp/HMAC_digest_service.hpp"

using namespace ara::crypto::cryp;

HMAC::HMAC(CryptoProvider * provider) {
    this->myProvider = provider;
}

/** Inherited from CryptoContext class**/

bool HMAC::IsInitialized() {
    if(status == MessageAuthnCodeCtx_Status::notInitialized)
        return false;
    else
        return true;
}

CryptoProvider& HMAC::MyProvider() const noexcept {
    return (*myProvider) ;
}


// CryptoPrimitiveId::Uptr HMAC::GetCryptoPrimitiveId() const noexcept {
//     CryptoPrimitiveId::Uptr ;

// }


/** Inherited from MessageAuthnCode class**/

void HMAC::Reset() {
    status = MessageAuthnCodeCtx_Status::notInitialized;
    signature_ptr = nullptr;
    hashFunction = nullptr;
    digest.resize(0); // shrink the vector size back as we started
}

// void HMAC::SetKey(const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kMacGenerate) {
        
//     if(transform == CryptoTransform::kMacGenerate){
//         // operations to check whether the key is valid or not
//         this->key = key;
//         status = MessageAuthnCodeCtx_Status::initialized;
//     }
//     else {
//         // do nothing
//     }
// }

// void HMAC::Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) {
    
//     status == MessageAuthnCodeCtx_Status::started; // change to the new state
//     hashFunction = std::make_unique<HashFunctionCtx>(); // creating the needed algorithm
//     digest.resize(0); // shrink the vector size back as we started
// }

// void HMAC::Update(std::uint8_t in) {

// }


DigestService::Uptr HMAC::GetDigestService() const noexcept {
    //return std::make_unique<HMACDigestService>;
}


std::vector<ara::crypto::byte> HMAC::GetDigest(std::size_t offset = 0) const noexcept {
    return {digest.begin() + offset, digest.end()};
}

Signature::Uptrc HMAC::Finish(bool makeSignatureObject = false) {

   status = MessageAuthnCodeCtx_Status::finished; // changing the status

    if(makeSignatureObject)
        return nullptr;
    else
        return std::make_unique<Signature>();

}
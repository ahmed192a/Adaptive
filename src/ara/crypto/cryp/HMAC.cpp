#include "../../../../include/ara/crypto/cryp/HMAC.hpp"

using namespace ara::crypto::cryp;


bool HMAC::IsInitialized() {
    if(status == MessageAuthnCodeCtx_Status::notInitialized)
        return false;
    else
        return true;
}

void HMAC::Reset() {
    status = MessageAuthnCodeCtx_Status::notInitialized;
    signature_ptr = nullptr;



}


Signature::Uptrc HMAC::Finish(bool makeSignatureObject = false) noexcept {
    if(makeSignatureObject == false)
        return std::make_unique<Signature>(nullptr);
    else
        return std::make_unique<Signature>(); // should be initialized with the correct value
}
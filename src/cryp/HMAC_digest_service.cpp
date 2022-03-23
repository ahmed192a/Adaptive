#include "ara/crypto/cryp/HMAC_digest_service.hpp"

using namespace ara::crypto::cryp;


/* ExtensionService inhereted functions implementation */

std::size_t HMACDigestService::GetMaxKeyBitLength() const {
    return this->key_maxBitLength;
}

std::size_t HMACDigestService::GetMinKeyBitLength() const {
    return this->key_minBitLength;
}

bool HMACDigestService::IsKeyBitLengthSupported(std::size_t keyBitLength) const {
    if(keyBitLength > this->key_maxBitLength || keyBitLength < this->key_minBitLength) {
        return false;
    }
    else {
        return true;
    }
}


std::size_t HMACDigestService::GetDigestSize() const {
    return this->size;
}


// bool HMACDigestService::IsFinished() const {
    
// }


// bool HMACDigestService::IsStarted() const {
    
// }
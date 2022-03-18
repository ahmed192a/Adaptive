#include "ara/crypto/cryp/HMAC_digest_service.hpp"

using namespace ara::crypto::cryp;


std::size_t HMACDigestService::GetDigestSize() const {
    return this->size;
}


bool HMACDigestService::IsFinished() const {
    
}


bool HMACDigestService::IsStarted() const {
    
}
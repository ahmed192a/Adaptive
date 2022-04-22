#include "ara/crypto/cryp/HMAC.hpp"
#include "ara/crypto/cryp/HMAC_digest_service.hpp"

using namespace ara::crypto::cryp;


HMAC::HMAC(CryptoProvider * provider) {
    // intializing the key
    input_key.resize(B);
    std::fill(input_key.begin(), input_key.end(), 0);

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
//     return (this->myProvider->ConvertToAlgId("test"));

// }



/** Inherited from MessageAuthnCode class**/
void HMAC::Reset() {
    status = MessageAuthnCodeCtx_Status::notInitialized;
    signature_ptr = nullptr;
    hashFunction = nullptr;
    digest.clear(); // shrink the vector size back as we started
    inputBuffer.clear();
}



// void HMAC::SetKey(const   &key, CryptoTransform transform = CryptoTransform::kMacGenerate) {
        
//     if(transform == CryptoTransform::kMacGenerate){
//         // operations to check whether the key is valid or not
//         this->key = key;
//         status = MessageAuthnCodeCtx_Status::initialized;
//     }
//     else {
//         // do nothing
//     }
// }



void HMAC::Start(ReadOnlyMemRegion iv = ReadOnlyMemRegion()) {
    
    Reset(); // resetting the context;
    status = MessageAuthnCodeCtx_Status::started; // change to the new state
    hashFunction = std::make_unique<HashFunctionCtx>(); // creating the needed algorithm
}


void HMAC::Update(std::uint8_t in) {
    inputBuffer.push_back(in);
    status = MessageAuthnCodeCtx_Status::updated;
}



DigestService::Uptr HMAC::GetDigestService() const noexcept {
    //return std::make_unique<HMACDigestService>;
}



std::vector<ara::crypto::byte> HMAC::GetDigest(std::size_t offset = 0) const noexcept {
    return {digest.begin() + offset, digest.end()};
}


Signature::Uptrc HMAC::Finish(bool makeSignatureObject = false) {

  status = MessageAuthnCodeCtx_Status::finished; // changing the status

  // Generating the HMAC from the input buffer and putting the result in the digest vector
  hmac_digestion(inputBuffer, digest);


  if(makeSignatureObject)
      return nullptr;
  else
      return std::make_unique<Signature>();

}



void HMAC::hash_sha256(std::vector<byte> &input, std::vector<byte> &output) {

  byte * intput_str = input.data();

  SHA256 hashing;

  hashing.add(intput_str, input.size());

  std::string result = hashing.getHash();
  std::uint8_t size = result.size() >> 1;
  output.clear();
  output.resize(size);

  for (std::uint8_t i = 0; i < size; i++)
    output[i] = std::stoi(result.substr(i*2, 2), nullptr, 16);

  return ;
}



void HMAC::hmac_digestion(std::vector<byte> &plainText, std::vector<byte> &output) {
  std::vector<byte> S1_vect;
  std::vector<byte> S2_vect;

  // Xoring the iPad with the key
  for(std::uint8_t i = 0; i < B; i++)
    input_key[i] = input_key[i] ^ iPad;

  // Adding the S1 key generated
  S1_vect.insert(S1_vect.begin(), input_key.begin(), input_key.end());
  // Appending the input message to the S1 version generated from the key
  S1_vect.insert(S1_vect.end(), plainText.begin(), plainText.end());

  hash_sha256(S1_vect, S2_vect);
  S1_vect.clear();

  // Xoring the oPad with the key and removing the effect of the iPad
  for(uint8_t i = 0; i < B; i++)
    input_key[i] = input_key[i] ^ iPad ^ oPad;

  // Adding the S2 key generated
  S2_vect.insert(S2_vect.begin(), input_key.begin(), input_key.end());

  output.clear();
  hash_sha256(S2_vect, output);

  // Removing the effect of the oPad
  for(uint8_t i = 0; i < B; i++)
    input_key[i] = input_key[i] ^ oPad;

  return ;
}

#include "ara/crypto/cryp/symmetric_cipher.hpp"

using namespace ara::crypto;
using namespace ara::crypto::cryp;
using namespace CryptoPP;

///@brief: a constructor to save the instance of the crypto provider of the SymmetricBlockCipher context
SymmetricCipher::SymmetricCipher(CryptoProvider* Provider)
{
	//@ storing the crypto provider instance of the context
	this->myProvider = Provider;

    //@ set the status of the context as notInitialized
	this->status = SymmetricBlockCipher_Status::notInitialized;

	//@ indicating that initially the function set_key isn not called yet
	this->Key_is_Set = 0;
}

/***********************************************************************/
/***** implementation of inherited CyrptoContext virtual functions *****/
/***********************************************************************/

///@brief: inherited function from CryptoContext, determines whether context is ready to use or not 
bool SymmetricCipher::IsInitialized()
{
    //@ return false if the context is not initialized
	if (this->status == SymmetricBlockCipher_Status::notInitialized)
	{
		return false;
	}
	//@ return true if the context is initialized 
	else 
	{
		// It checks all required values, including: key value
		if (this->Key_is_Set)
			return true;
		else
			return false;
	}
}

///@brief: inherited function from CryptoContext, gets a reference to CryptoPrimitivId instance of this CryptoContext
CryptoPrimitiveId::Uptr SymmetricCipher::GetCryptoPrimitiveId() const noexcept
{
	AlgId myAlgorithmId = (this->myProvider)->ConvertToAlgId("AES_128");
	//CryptoPrimitiveId::Uptr myPrimitiveId = std::make_unique<CryptoPrId>(myAlgorithmId);
	return myAlgorithmId;
}

///@brief: inherited function from CryptoContext, gets a reference to Crypto Provider instance of this CryptoContext
CryptoProvider&  SymmetricCipher::MyProvider() const noexcept
{
	//@return pointer references the Crypto Provider instance of the context
	return *(this->myProvider);
}


/************************************************************************************/
/***** implementation of symmetric_block_cipher_ctx inherited virtual functions *****/
/************************************************************************************/

/*Get the kind of transformation configured for this context: kEncrypt or kDecrypt*/
CryptoTransform SymmetricCipher::CryptoTransform GetTransformation () const noexcept
{
    if (this->Key_is_Set) 
    {
		return this->Alg_transformation;
	}
    else
    {
        //raise CryptoErrorDomain::kUninitializedContext error
    }
}


/*Process (encrypt / decrypt) an input block according to the crypto configuration*/
std::vector<byte> Symmetric_Cipher::ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept
{
	std::vector<uint8_t> key = this->Alg_key.keyVal;
    
	RandomGeneratorCtx::Uptr R = std::make_unique<PRNG>();
	std::vector<byte> iv = (*R).Generate(AES::BLOCKSIZE);
	
	std::string in_data, out_data;
	std::vector<byte> return_data;

	for (uint8_t i=0; i<in.size(); i++)
	{
		in_data += in[i];
	}

	/*raise and error if the boolean parameter {suppressPadding} was set to TRUE and 
	 *the provided input buffer does not match the block-size*/
	if (suppressPadding == true && in.size() != AES::BLOCKSIZE)
	{
		//raise CryptoErrorDomain::kInvalidInputSize
	}
	/*raise and error if the context was not initialized by calling SetKey()*/
	else if(!(this->Key_is_Set))
	{
		//raise CryptoErrorDomain::kUninitialized Context
	}
	else
	{
		try
		{
			if (this->Alg_transformation == CryptoTransform::kEncrypt)
			{
				CBC_Mode<AES>::Encryption e;
				e.SetKeyWithIV(key.data(), key.size(), iv.data());
				StringSource s(in_data, true, 
					new StreamTransformationFilter(e,
						new StringSink(out_data)
					) // StreamTransformationFilter
				); // StringSource
			}
			else if(this->Alg_transformation == CryptoTransform::kDecrypt)
			{
				CBC_Mode<AES>::Decryption d;
				d.SetKeyWithIV(key.data(), key.size(), iv.data());
				StringSource s(in_data, true, 
					new StreamTransformationFilter(e,
						new StringSink(out_data)
					) // StreamTransformationFilter
				); // StringSource
			}
		}
		catch(const Exception& e)
		{
			std::cerr << e.what() << std::endl;
			exit(1);
		}

		//Convert the string result into vector of bytes
		for(uint8_t i=0; i<out_data.length(); i++)
		{
			return_data.push_back(out_data[i]);
		}
		return return_data;
	}
}

                
/*Processe provided blocks without padding. The in and out buffers must have same size and
*this size must be divisible by the block size (see GetBlockSize()). Pointers to the input and
*output buffers must be aligned to the block-size boundary!*/
//std::vector<byte> SymmetricCipher::Process_Blocks (ReadOnlyMemRegion in) const noexcept
                
/*Clear the crypto context*/                
void SymmetricCipher::Reset () noexcept
{
    this->Key_is_Set = 0;
    this->status = SymmetricBlockCipher_Status::notInitialized;
}
                
/*Set (deploy) a key to the symmetric algorithm context*/
void SymmetricCipher::SetKey (const SymmetricKey &key, CryptoTransform transform = CryptoTransform::kEncrypt) noexcept
{
    if ((transform == CryptoTransform::kEncrypt && kAllowDataEncryption != NULL) || (transform == CryptoTransform::kDecrypt && kAllowDataDecryption != NULL))
	{
		this->Key_is_Set = 1;
        this->Alg_key = key;
		this->Alg_transformation = transform;
        this->status = SymmetricBlockCipher_Status::initialized;
	}
    else
    {
        //raise CryptoErrorDomain::kUsageViolation error
    }
}

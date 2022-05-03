
#ifndef ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP
#define ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP

#include <string>
#define ALGORITHMSNUMBER 1

//enter the algorithm name used according to the standard naming in the array of string
//the algorithm ID will be shifted by one less when trying to access the array
//then AlgId of HMACSHA_256 is 1 and when used in algorithmNames variable will be 0
const std::string algorithmNames[] =
{
	"HMACSHA_256",
	"AES_128"
};



#endif /* ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP */

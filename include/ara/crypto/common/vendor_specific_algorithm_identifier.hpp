
#ifndef ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP
#define ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP

#include <string>

//enter the algorithm name used according to the standard naming and two times
//in enum and array of string

//HMACSHA_256 is here for example and testing
enum algorithmsId
	{
	HMACSHA_256=1

	 } ;
const std::string algorithmNames[] =
{
	"HMACSHA_256"
};



#endif /* ARA_CRYPTO_COMMON_VENDOR_SPECIFIC_ALGORITHM_IDENTIFIER_HPP */

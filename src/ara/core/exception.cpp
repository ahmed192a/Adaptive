
// #include  "exception.h"
// #include <iostream>
// #include<sstream>

// namespace ara
// {
// 	namespace core
// 	{
// 		// SWS_CORE_00611
// 		/**
// 		 * \brief Construct a new Exception object with a specific ErrorCode.
// 		 *
// 		 * \param[in] err   the ErrorCode
// 		 */
// 	//Defined in the header.
// //		Exception::Exception(ara::core::ErrorCode &err) noexcept
// //		{
// //			mErrorCode = err;
// //		}

// 		// SWS_CORE_00612
// 		/**
// 		 * \brief Return the explanatory string.
// 		 *
// 		 * This function overrides the virtual function std::exception::what. All guarantees about the
// 		 * lifetime of the returned pointer that are given for std::exception::what are preserved.
// 		 *
// 		 * \return char const*  a null-terminated string
// 		 */

// 		 std::string Exception::what() const noexcept
// 		 {
// 		 	ErrorDomain::CodeType codeType = this->mErrorCode.mValue;
// 		 	std::stringstream ss;
// 		    ss<<codeType;
// 		    std::string s;
// 		    ss>>s;
// 		 	return "CodeType of error message: " + s;
// 		 }

// 		// SWS_CORE_00613
// 		/**
// 		 * \brief Return the embedded ErrorCode that was given to the constructor.
// 		 *
// 		 * \return ErrorCode const&     reference to the embedded ErrorCode
// 		 */

// 		 ErrorCode const& Exception::Error() const noexcept
// 		 {
// 		 	return this->mErrorCode;
// 		 }

// 	}
// }

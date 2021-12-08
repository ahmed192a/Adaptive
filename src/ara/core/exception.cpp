
#include  "exception.h"

namespace ara
{
	namespace core
	{
		// SWS_CORE_00611
		/**
		 * \brief Construct a new Exception object with a specific ErrorCode.
		 *
		 * \param[in] err   the ErrorCode 
		 */
		explicit Exception::Exception(ErrorCode err) noexcept
		{
			this->errorCode = err;
		}

		// SWS_CORE_00612
		/**
		 * \brief Return the explanatory string.
		 *
		 * This function overrides the virtual function std::exception::what. All guarantees about the
		 * lifetime of the returned pointer that are given for std::exception::what are preserved.
		 *
		 * \return char const*  a null-terminated string
		 */

		// char const* Exception::what() const noexcept
		// {
		// 	ErrorDomain::CodeType codeType = this->errorCode.codeType;
		// 	char codeTypeStr[33];
		// 	snprintf( codeTypeStr, 33, "%d", (int)codeType );
		// 	return "CodeType of error message: " + codeTypeStr;
		// }

		// SWS_CORE_00613
		/**
		 * \brief Return the embedded ErrorCode that was given to the constructor.
		 *
		 * \return ErrorCode const&     reference to the embedded ErrorCode
		 */

		// ErrorCode::ErrorCode const& Exception::Error() const noexcept
		// {
		// 	return this->errorCode;
		// }

	}
}

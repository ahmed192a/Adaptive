
#include "error_code.h"
#include "string"
using namespace std;
namespace ara
{
	namespace core
	{
		// SWS_CORE_00512
		/**
		 * \brief Construct a new ErrorCode instance with parameters.
		 *
		 * This constructor does not participate in overload resolution unless EnumT is an enum type.
		 *
		 * \tparam EnumT    an enum type that contains error code values
		 * \param e     a domain-specific error code value
		 * \param data  optional vendor-specific supplementary error context data
		 */
		//NOT NEEDED

//		template <typename EnumT>
//		 constexpr ErrorCode::ErrorCode(EnumT e, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept
//		 {
//		 	this->mValue = e;
//		 	this->mSupportData = data;
//		 }

		// SWS_CORE_00513
		/**
		 * \brief Construct a new ErrorCode instance with parameters.
		 *
		 * \param value     a domain-specific error code value
		 * \param domain    the ErrorDomain associated with value
		 * \param data      optional vendor-specific supplementary error context data
		 */
//		constexpr ErrorCode::ErrorCode(ErrorDomain::CodeType value,ErrorDomain *domain, ErrorDomain::SupportDataType data) noexcept : mValue(value), mSupportData(data)
//		{
//			if(domain != nullptr)
//			{
//				this->mDomain = domain;
//			}
//		}

		// SWS_CORE_00514
		/**
		 * \brief Return the raw error code value.
		 *
		 * \return constexpr ErrorDomain::CodeType  the raw error code value
		 */
		constexpr ErrorDomain::CodeType ErrorCode::Value() const noexcept
		{
			return this->mValue;
		}

		// SWS_CORE_00515
		/**
		 * \brief Return the domain with which this ErrorCode is associated.
		 *
		 * \return constexpr ErrorDomain const&     the ErrorDomain
		 */

//		constexpr ErrorDomain& ErrorCode::Domain() const noexcept
//		{
//			ErrorDomain& ref = *mDomain;
//			return ref;
//		}

		// SWS_CORE_00516
		/**
		 * \brief Return the supplementary error context data.
		 *
		 * The underlying type and the meaning of the returned value are implementation-defined.
		 *
		 * \return constexpr ErrorDomain::SupportDataType   the supplementary error context data
		 */
		constexpr ErrorDomain::SupportDataType ErrorCode::SupportData() const noexcept
		{
			return this->mSupportData;
		}

		// SWS_CORE_00518
		/**
		 * \brief Return a textual representation of this ErrorCode.
		 *
		 * \return StringView   the error message text
		 */
		std::string ErrorCode::Message() const noexcept
		{
			// char codeTypeStr[33];
			// snprintf( codeTypeStr, 33, "%d", (int)this->codeType );
			string codeTypeStr = to_string(this->mValue);
			return "CodeType of error message: " + codeTypeStr;
		}

		// SWS_CORE_00519
		/**
		 * \brief Throw this error as exception.
		 *
		 * This function will determine the appropriate exception type for this ErrorCode and throw it. The
		 * thrown exception will contain this ErrorCode.
		 *
		 */
		void ErrorCode::ThrowAsException() const
		{
			throw this->mValue;
		}

        constexpr void ErrorCode::operator=(ErrorCode const &err) noexcept
        {
        	this->mValue = err.mValue;
        	this->mSupportData = err.mSupportData;
        	this->mDomain = err.mDomain;
        }

        // SWS_CORE_00571
        /**
         * \brief Global operator== for ErrorCode.
         *
         * Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
         * are equal. The result of SupportData() is not considered for equality.
         *
         * \param[in] lhs   the left hand side of the comparison
         * \param[in] rhs   the right hand side of the comparison
         *
         * \return true     if the two instances compare equal
         * \return false    otherwise
         */
        constexpr bool operator==(ErrorCode const &lhs, ErrorCode const &rhs) noexcept
        {
        	return lhs.Domain() == rhs.Domain() && lhs.Value() == rhs.Value();
        }

        // SWS_CORE_00572
        /**
         * \brief Global operator!= for ErrorCode.
         *
         * Two ErrorCode instances compare equal if the results of their Value() and Domain() functions
         * are equal. The result of SupportData() is not considered for equality.
         *
         * \param[in] lhs   the left hand side of the comparison
         * \param[in] rhs   the right hand side of the comparison
         *
         * \return true     if the two instances compare not equal
         * \return false    otherwise
         */
        constexpr bool operator!=(ErrorCode const &lhs, ErrorCode const &rhs) noexcept
        {
        	return lhs.Domain() != rhs.Domain() || lhs.Value() != rhs.Value();
        }
	}
}

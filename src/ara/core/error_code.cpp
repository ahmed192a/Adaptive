
#include "error_code.h"

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

		//NOTE"KASSEM": USE THE 3 PARAMETER CONSTRACTOR TO AVOID ERRORS
		template <typename EnumT>
		constexpr ErrorCode::ErrorCode(EnumT e, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept
		{
			this->codeType = e;
			this->errorDomainPtr = nullptr;
			this->supportDataType = data;
		}

		// SWS_CORE_00513
		/**
		 * \brief Construct a new ErrorCode instance with parameters.
		 *
		 * \param value     a domain-specific error code value
		 * \param domain    the ErrorDomain associated with value
		 * \param data      optional vendor-specific supplementary error context data
		 */
		constexpr ErrorCode::ErrorCode(ErrorDomain::CodeType value, ErrorDomain const &domain, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept
		{
			this->codeType = value;
			this->errorDomainPtr = domain;
			this->supportDataType = data;
		}

		// SWS_CORE_00514
		/**
		 * \brief Return the raw error code value.
		 *
		 * \return constexpr ErrorDomain::CodeType  the raw error code value
		 */
		constexpr ErrorDomain::CodeType ErrorCode::Value() const noexcept
		{
			return this->codeType;
		}

		// SWS_CORE_00515
		/**
		 * \brief Return the domain with which this ErrorCode is associated.
		 *
		 * \return constexpr ErrorDomain const&     the ErrorDomain
		 */
		constexpr ErrorDomain const& ErrorCode::Domain() const noexcept
		{
			return this->errorDomainPtr;
		}

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
			return this->supportDataType;
		}

		// SWS_CORE_00518
		/**
		 * \brief Return a textual representation of this ErrorCode.
		 *
		 * \return StringView   the error message text
		 */
		char* ErrorCode::Message() const noexcept
		{
			char codeTypeStr[33];
			snprintf( codeTypeStr, 33, "%d", (int)codeType );
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
			throw this->codeType;
		}
	}
}


#include "exec_error_domain.h"

namespace ara
{
	namespace exec
	{
		// SWS_EM_02283
		/**
		 * \brief Constructs a new ExecException object containing an error code.
		 *
		 * \param[in] errorCode     The error code.
		 */
		explicit ExecException::ExecException(ara::core::ErrorCode errorCode) noexcept
		{
			this->errorCode = errorCode;
		}


		//SWS_EM_02290
		/*
		 * \brief Returns a reference to the global ExecErrorDomain object.
		 *
		 * \return const ara::core::ErrorDomain&
		 */
		const ara::core::ErrorDomain& ExecException::GetExecErrorDomain () noexcept
		{
			return this->errorCode.errorDomainPtr;
		}


		//SWS_EM_02291
		/*
		 *\brief Creates an instance of ErrorCode.
		 *
		 *\param[in] code         Error code number.
		 *\param[in] data         Vendor defined data associated with the error.
		 *
		 *\return ara::core::ErrorCode             An ErrorCode object.
		 */
		ara::core::ErrorCode ExecException::MakeErrorCode (ara::exec::ExecErrc code, ara::core::ErrorDomain::SupportDataType data = ara::core::ErrorDomain::SupportDataType()) noexcept
		{
			ara::core::ErrorCode obj;
			obj.ErrorCode(code, nullptr, data);
			return obj;
		}

		// SWS_EM_02286
		/**
		 * \brief Constructs a new ExecErrorDomain object
		 *
		 */
		ExecErrorDomain::ExecErrorDomain() noexcept = default;

		// SWS_EM_02287
		/**
		 * \brief Returns a string constant associated with ExecErrorDomain.
		 *
		 * \return char const*  The name of the error domain.
		 */
		char const * ExecErrorDomain::Name() const noexcept
		{
			return "Exec";
		}

		// SWS_EM_02288
		/**
		 * \brief Returns the message associated with errorCode.
		 *
		 * \param[in] errorCode     The error code number.
		 *
		 * \return char const*      The message associated with the error code.
		 */
		char const * ExecErrorDomain::Message(CodeType errorCode) const noexcept
		{
			char codeTypeStr[33];
			snprintf( codeTypeStr, 33, "%d", (int)errorCode );
			return "CodeType of error message: " + codeTypeStr;
		}

		// SWS_EM_02289
		/**
		 * \brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
		 *
		 * \param[in] errorCode     The error to throw.
		 */
		void ExecErrorDomain::ThrowAsException(ara::core::ErrorCode const &errorCode) const noexcept(false)
		{
			ara::core::Exception exp = ara::core::Exception(errorCode);
			char* c = exp.ara::core::Exception::what();
		}
	}
}


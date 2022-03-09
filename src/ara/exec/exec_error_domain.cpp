/**
 * @file exec_error_domain.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 #include "ara/exec/exec_error_domain.hpp"
 #include <iostream>

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
 		 /*ExecException::ExecException(ara::core::ErrorCode errorCode) noexcept :  ara::core::Exception(errorCode)
 		 {

 		 	this->errorCode = errorCode;
 		 }*/


 		//SWS_EM_02290
 		/*
 		 * \brief Returns a reference to the global ExecErrorDomain object.
 		 *
 		 * \return const ara::core::ErrorDomain&
 		 */
 		const ara::core::ErrorDomain& ExecException::GetExecErrorDomain () noexcept
 		{
 			return this->errorCode.Domain();
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
		// ara::core::ErrorCode ExecException::MakeErrorCode (ara::exec::ExecErrc code, ara::core::ErrorDomain::SupportDataType data = ara::core::ErrorDomain::SupportDataType()) noexcept
		// {
		// ara::core::ErrorDomain *ref = nullptr;
		// ara::core::ErrorCode obj((ara::core::ErrorDomain::CodeType)code, ref, (ara::core::ErrorDomain::SupportDataType)data);
		// return obj;
		// }



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
 			std::string codeTypeStr = std::to_string((int)errorCode);
 			return ("CodeType of error message: " + codeTypeStr).c_str();


 		}

 		// SWS_EM_02289
 		/**
 		 * \brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
 		 *
 		 * \param[in] errorCode     The error to throw.
 		 */
 		void ExecErrorDomain::ThrowAsException(ara::core::ErrorCode &errorCode) const noexcept(false)
 		{
 			ara::core::Exception exp(std::move(errorCode));
 			std::string c = exp.what();
 		}
 	}
 }


/**
 * @file exec_error_domain.cpp
 * @author Flashing Adapter Graduation Project Team
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
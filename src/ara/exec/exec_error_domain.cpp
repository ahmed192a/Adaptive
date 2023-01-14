/**
 * @file exec_error_domain.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Implementation of the ExecErrorDomain class which is responsible for handling all Excuation Management exceptions
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 #include "ara/exec/exec_error_domain.h"
 #include <iostream>

 namespace ara
 {
 	namespace exec
 	{
		/*---------------------------------ExecException---------------------------------*/
		ExecException::ExecException(ara::core::ErrorCode errorCode) noexcept : ara::core::Exception(std::move(errorCode)), errorCode(errorCode)
 		{
 		}

 		const ara::core::ErrorDomain& ExecException::GetExecErrorDomain () noexcept
 		{
 			return this->errorCode.Domain();
 		}

		ara::core::ErrorCode ExecException::MakeErrorCode(ara::exec::ExecErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept{
			return ara::core::ErrorCode(static_cast<ara::core::ErrorDomain::CodeType>(code), this->errorCode.Domain(), data);
		}

		/*---------------------------------ExecErrorDomain---------------------------------*/
		
		constexpr ExecErrorDomain::ExecErrorDomain(IdType id) noexcept : ara::core::ErrorDomain(id)
 		{
			
 		}

 		char const * ExecErrorDomain::Name() const noexcept
 		{
 			return "Exec";
 		}


 		char const * ExecErrorDomain::Message(CodeType errorCode) const noexcept
 		{
 			std::string codeTypeStr = std::to_string((int)errorCode);
 			return ("CodeType of error message: " + codeTypeStr).c_str();


 		}


 		void ExecErrorDomain::ThrowAsException(ara::core::ErrorCode &errorCode) const noexcept(false)
 		{
 			ara::core::Exception exp(std::move(errorCode));
 			std::string c = exp.what();
 		}
 	}
 }
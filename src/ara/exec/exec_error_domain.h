#ifndef ARA_EXEC_EXEC_ERROR_DOMAIN_H_
#define ARA_EXEC_EXEC_ERROR_DOMAIN_H_

/**
 * @file exec_error_domain.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of the ExecErrorDomain class which is responsible for handling all Excuation Management exceptions
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"
#include <cstdint>
#include <string>

namespace ara
{
	namespace exec
	{
		/**
		 * @brief ExecErrc enum class Defines an enumeration class for the Execution Management error codes.
		 * @note  SWS_EM_02281
		 */
		enum class ExecErrc : ara::core::ErrorDomain::CodeType
		{
			kGeneralError = 1,						 /*!< Some unspecified error occurred */
			kInvalidArguments = 2,					 /*!< Invalid argument was passed */
			kCommunicationError = 3,				 /*!< Communication error occurred */
			kMetaModelError = 4,					 /*!< Wrong meta model identifier passed to a function */
			kCancelled = 5,							 /*!< Transition to the requested Function Group state was cancelled by a newer request */
			kFailed = 6,							 /*!< Transition to the requested Function Group state failed */
			kFailedUnexpectedTerminationOnExit = 7,	 /*!< Unexpected Termination during transition in Process of previous Function Group State happened*/
			kFailedUnexpectedTerminationOnEnter = 8, /*!< Unexpected Termination during transition in Process of target Function Group State happened*/
			kInvalidTransition = 9,					 /*!< Transition invalid (e.g. to Terminating when already in Terminating state)*/
			kAlreadyInState = 10,					 /*!< Transition to the requested Function Group state failed because it is already in requested state*/
			kInTransitionToSameState = 11,			 /*!< Transition to the requested Function Group state failed because transition to requested state is already in progress*/
			kNoTimeStamp = 12,						 /*!< DeterministicClient time stamp information is not available*/
		};

		/**
		 * @brief ExecException Defines a class for exceptions to be thrown by the Execution Management.
		 * @note  SWS_EM_02282
		 */
		class ExecException : public ara::core::Exception
		{
		public:
			ara::core::ErrorCode errorCode; /*!< The error code. (ExecException will use ErrorCode Attribute in the Exception class)*/

			/**
			 * \brief Constructs a new ExecException object containing an error code.
			 * @note SWS_EM_02283 
			 * \param[in] errorCode     The error code.
			 */
			explicit ExecException(ara::core::ErrorCode errorCode) noexcept;

			/**
			 * @brief Get the Exec Error Domain object
			 * @note SWS_EM_02290
			 * @return const ara::core::ErrorDomain&  Returns a reference to the global ExecErrorDomain object.
			 * @exception noexcept
			 */
			const ara::core::ErrorDomain &GetExecErrorDomain() noexcept;


			/**
			 * @brief Creates an instance of ErrorCode.
			 * @note SWS_EM_02291
			 * 
			 * @param code 	execution management error code
			 * @param data 	vendor defined data associated with the error
			 * @return ara::core::ErrorCode 			An ErrorCode object.
			 * @exception noexcept
			 * 
			 */
			ara::core::ErrorCode MakeErrorCode(ara::exec::ExecErrc code, ara::core::ErrorDomain::SupportDataType data) noexcept;
		};

		/**
		 * @brief ExecErrorDomain Defines a class representing the Execution Management error domain.
		 * @note SWS_EM_02284
		 */
		class ExecErrorDomain final : public ara::core::ErrorDomain
		{
			using IdType = ara::core::ErrorDomain::IdType; /*!< The type of the error domain identifier. */
		public:
			/**
			 * @brief Construct a new Exec Error Domain object
			 * @note SWS_EM_02286
			 */
			explicit constexpr ExecErrorDomain(IdType id) noexcept;
			// ExecErrorDomain(IdType id) noexcept = default;

			/**
			 * @brief Returns a string constant associated with ExecErrorDomain.
			 * @note SWS_EM_02287
			 * @return char const*  The name of the error domain.
			 */
			char const *Name() const noexcept override;

			/**
			 * \brief Returns the message associated with errorCode.
			 * @note SWS_EM_02288
			 * \param[in] errorCode     The error code number.
			 *
			 * \return char const*      The message associated with the error code.
			 */
			char const *Message(CodeType errorCode) const noexcept override;

			
			/**
			 * \brief Creates a new instance of ExecException from errorCode and throws it as a C++ exception.
			 * @note SWS_EM_02289
			 * \param[in] errorCode     The error to throw.
			 */
			void ThrowAsException(ara::core::ErrorCode &errorCode) const noexcept(false);
		};
	} // namespace exec

} // namespace ara

#endif // ARA_EXEC_EXEC_ERROR_DOMAIN_H_

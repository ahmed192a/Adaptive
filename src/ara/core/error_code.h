
#ifndef ARA_CORE_ERROR_CODE_H_
#define ARA_CORE_ERROR_CODE_H_

// #include <stdio.h>
// #include <stdlib.h>
#include "error_domain.h"
// #include <string>
#include <ostream>
#include <cstdint>

namespace ara
{
    namespace core
    {
        // SWS_CORE_00501
        /**
         * \brief Encapsulation of an error code.
         * 
         * An ErrorCode contains a raw error code value and an error domain. The raw error code value is
         * specific to this error domain.
         * 
         */
        class ErrorCode 
        {
        public:

            using CodeType = ErrorDomain::CodeType;
            using SupportDataType = ErrorDomain::SupportDataType;

            //ErrorCode class attributes
        	/*
        	 * \codeType    		 a domain-specific error code value
             * \errorDomain  	     the ErrorDomain associated with value
             * \supportDataType      optional vendor-specific supplementary error context data
        	 */

            CodeType mValue;
            SupportDataType mSupportData = 0;
            ErrorDomain *mDomain = nullptr;  // non-owning pointer to the associated ErrorDomain
            

            // SWS_CORE_00512
            /**
             * \brief Construct a new ErrorCode instance with parameters.
             * 
             * This constructor does not participate in overload resolution unless EnumT is an enum type.
             * 
             * \tparam EnumT    an enum type that contains error code values
             * 
             * \param e     a domain-specific error code value
             * \param data  optional vendor-specific supplementary error context data
             */
            /*template <typename EnumT, typename = typename std::enable_if<std::is_enum<EnumT>::value>::type>
            constexpr ErrorCode(EnumT e, SupportDataType data = 0, char const* userMessage = nullptr) noexcept
                // Call MakeErrorCode() unqualified, so the correct overload is found via ADL.
                : ErrorCode(MakeErrorCode(e, data, userMessage))
            {
            }*/

//			 template <typename EnumT>
//			 constexpr ErrorCode(EnumT e, ErrorDomain::SupportDataType data=ErrorDomain::SupportDataType()) noexcept;

            // SWS_CORE_00513
            /**
             * \brief Construct a new ErrorCode instance with parameters.
             *
             * \param value     a domain-specific error code value
             * \param domain    the ErrorDomain associated with value
             * \param data      optional vendor-specific supplementary error context data
             */
//            constexpr ErrorCode(ErrorDomain::CodeType value,ErrorDomain *domain, ErrorDomain::SupportDataType data) noexcept;
    		constexpr ErrorCode(ErrorDomain::CodeType value,ErrorDomain *domain, ErrorDomain::SupportDataType data) noexcept : mValue(value), mSupportData(data)
    		{
    			if(domain != nullptr)
    			{
    				this->mDomain = domain;
    			}
    		}

            // SWS_CORE_00514
            /**
             * \brief Return the raw error code value.
             * 
             * \return constexpr ErrorDomain::CodeType  the raw error code value
             */
            constexpr ErrorDomain::CodeType Value() const noexcept;

            // SWS_CORE_00515
            /**
             * \brief Return the domain with which this ErrorCode is associated.
             * 
             * \return constexpr ErrorDomain const&     the ErrorDomain
             */
//            constexpr ErrorDomain& Domain() const noexcept;
    		constexpr ErrorDomain& Domain() const noexcept
    		{
    			ErrorDomain& ref = *mDomain;
    			return ref;
    		}

            // SWS_CORE_00516
            /**
             * \brief Return the supplementary error context data.
             * 
             * The underlying type and the meaning of the returned value are implementation-defined.
             * 
             * \return constexpr ErrorDomain::SupportDataType   the supplementary error context data
             */
            constexpr ErrorDomain::SupportDataType SupportData() const noexcept;

            // SWS_CORE_00518
            /**
             * \brief Return a textual representation of this ErrorCode.
             * 
             * \return StringView   the error message text
             */
            std::string Message() const noexcept;

            // SWS_CORE_00519
            /**
             * \brief Throw this error as exception.
             * 
             * This function will determine the appropriate exception type for this ErrorCode and throw it. The
             * thrown exception will contain this ErrorCode.
             * 
             */
            void ThrowAsException() const;

            constexpr void operator=(ErrorCode const &err) noexcept;
        };
        
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
        
        constexpr bool operator==(ErrorCode const &lhs, ErrorCode const &rhs) noexcept;

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
        constexpr bool operator!=(ErrorCode const &lhs, ErrorCode const &rhs) noexcept;
        
    } // namespace core
    
} // namespace ara


#endif // ARA_CORE_ERROR_CODE_H_

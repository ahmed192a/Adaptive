
#ifndef ARA_CORE_EXCEPTION_H_
#define ARA_CORE_EXCEPTION_H_

#include <exception>
#include "ara/core/error_code.h"

namespace ara
{
    namespace core
    {
        // SWS_CORE_00601
        /**
         * \brief Base type for all AUTOSAR exception types.
         * 
         */
        class Exception : public std::exception
        {
        public:
        	ErrorCode errorCode;
            // SWS_CORE_00611
            /**
             * \brief Construct a new Exception object with a specific ErrorCode.
             * 
             * \param[in] err   the ErrorCode
             */
            explicit Exception(ErrorCode err) noexcept;

            // SWS_CORE_00612
            /**
             * \brief Return the explanatory string.
             * 
             * This function overrides the virtual function std::exception::what. All guarantees about the
             * lifetime of the returned pointer that are given for std::exception::what are preserved.
             * 
             * \return char const*  a null-terminated string
             */
            char const* what() const noexcept override;

            // SWS_CORE_00613
            /**
             * \brief Return the embedded ErrorCode that was given to the constructor.
             * 
             * \return ErrorCode const&     reference to the embedded ErrorCode
             */
            ErrorCode const& Error() const noexcept;
        };
    } // namespace core
    
} // namespace ara


#endif // ARA_CORE_EXCEPTION_H_

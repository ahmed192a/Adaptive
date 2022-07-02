#ifndef ARA_SM_SM_ERROR_DOMAIN_H
#define ARA_SM_SM_ERROR_DOMAIN_H

#include "ara/core/error_domain.hpp"
#include "ara/core/error_code.hpp"

namespace ara
{
    namespace sm
    {

        using Error = ara::core::ErrorDomain;

        enum class errorDomains : uint16_t // shall be updated to ErrorCode or ErrorDomain **
        {
            kRejected = 5,                        // Requested operation was rejected due to State Managements machines proxy_skeleton state.
            kVerifyFailed = 6,                    // Verification step of update failed.
            kPrepareFailed = 7,                   // Preparation step of update failed.
            kRollbackFailed = 8,                  // Rollback step of update failed.
            kNotAllowedMultipleUpdateSessions = 9 // Request for new session was rejected as only single active (update) session is allowed.
        };

        errorDomains x = errorDomains::kRejected;

    } // namespace sm
} // namespace ara

#endif // ARA_SM_SM_ERROR_DOMAIN_H

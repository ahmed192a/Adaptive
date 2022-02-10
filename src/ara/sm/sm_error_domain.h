#ifndef ARA_SM_SM_ERROR_DOMAIN_H
#define ARA_SM_SM_ERROR_DOMAIN_H

#include "../core/error_domain.h"
#include "../core/error_code.h"


namespace ara {
    namespace sm {

    using Error = ara::core::ErrorDomain;


    enum class errorDomains : ara::core::ErrorDomain // shall be updated to ErrorCode or ErrorDomain **
    {
        kRejected = 5, // Requested operation was rejected due to State Managements machines internal state.
        kVerifyFailed = 6, // Verification step of update failed.
        kPrepareFailed = 7, // Preparation step of update failed.
        kRollbackFailed = 8, // Rollback step of update failed.
        kNotAllowedMultipleUpdateSessions = 9 // Request for new session was rejected as only single active (update) session is allowed.
    };

    uint16_t x = errorDomains::kRejected;


    } // namespace sm
} // namespace ara

#endif // ARA_SM_SM_ERROR_DOMAIN_H

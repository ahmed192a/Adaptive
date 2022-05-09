/**
 * @file update_request_return_types.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef RETURN_TYPES_H_
#define RETURN_TYPES_H_
#include "ara/sm/sm_error_domain.hpp"
namespace ara
{
    namespace sm
    {
        namespace update_request
        {
            struct ResetMachineOutput
            {
                bool status; 
                errorDomains error ;
            };
            struct StopUpdateSessionOutput
            {
                bool status; 
                errorDomains error ;
            };
            struct StartUpdateSessionOutput
            {
                bool status; 
                errorDomains error ;
            };
            struct PrepareUpdateOutput
            {
                bool status; 
                errorDomains error ;
            };
            struct VerifyUpdateOutput
            {
                bool status; 
                errorDomains error ;
            };
            struct PrepareRollbackOutput
            {
                bool status; 
                errorDomains error ;
            };
        } // namespace update_request

    } // namespace sm

} // namespace ara

#endif
/**
 * @file diagnostic_reset_return_types.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-03-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RETURN_TYPES_H_
#define RETURN_TYPES_H_

#include "ara/sm/diagnostic_reset/diagnostic_reset_types.hpp"


namespace ara
{
    namespace sm
    {
        namespace diagnostic_reset
        {
            struct MessageDiagnosticOutput
            {
                DiagnosticResetMsg msg;
            };
            struct EventDiagnosticOutput
            {
                DiagnosticResetRespMsg respMsg;
            };
        } // namespace DiagnosticReset

    } // namespace sm

} // namespace ara

#endif
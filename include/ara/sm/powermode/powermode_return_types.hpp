/**
 * @file powermode_return_types.hpp
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

#include "powermode_types.hpp"


namespace ara
{
    namespace sm
    {
        namespace powermode
        {
            struct MessagePowermodeOutput
            {
                PowerModeMsg msg;
            };
            struct EventPowermodeOutput
            {
                PowerModeRespMsg respMsg;
            };
        } // namespace powermode

    } // namespace sm

} // namespace ara

#endif
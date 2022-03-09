/**
 * @file execution_error_event.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <cstdint>
#include "ara/exec/function_group.hpp"

namespace ara
{
    namespace exec
    {
        using ExecutionError = std::uint32_t;
        //Represents an execution error event which happens in a Function Group
        struct ExecutionErrorEvent final
        {
            ExecutionError executionError;
            FunctionGroup functionGroup;
        };

    } // namespace exec

} // namespace ara

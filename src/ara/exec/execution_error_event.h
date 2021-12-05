#include <cstdint>
#include "function_group.h"

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

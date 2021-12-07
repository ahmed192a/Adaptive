#ifndef ARA_EXEC_EXECUTION_CLIENT_H_
#define ARA_EXEC_EXECUTION_CLIENT_H_

#include <cstdint>
#include <string>
// #include <iostream>
// #include "ara/core/result.h"
namespace ara
{
    namespace exec
    {
        // SWS_EM_02000
        /**
         * Defines the internal states of a Process (see 7.3.1). Scoped Enumeration of uint8_t .
         */
        enum class ExecutionState : uint8_t
        {
            kRunning = 0,     /* After a Process has been started by Execution Management, it reports ExecutionState kRunning. */
            kTerminating = 1, /* On receipt of SIGTERM, a Reporting Process acknowledges the request (by reporting kTerminating to Execution Management. */
        };

        // SWS_EM_02001
        /**
         * \brief Class to implement operations on Execution Client.
         * 
         */
        class ExecutionClient
        {
            // location of FIFO to communicate between EM & SM
            char fifo_l[30] = "execution_client_fifo";
            // index of File descriptor
            int fd;

            // SWS_EM_02030
            /**
             * Constructor that creates the Execution Client. 
             */
            ExecutionClient() noexcept;

            // SWS_EM_02002
            /**
             * Destructor of the Execution Client instance.
             */
            ~ExecutionClient() noexcept;

            // SWS_EM_02003
            /**
             * Interface for a Process to report its internal state to Execution Management.
             * 
             * \param state     Value of the Execution State
             * 
             * \return          An instance of ara::core::Result. The instance holds
             *                  an ErrorCode containing either one of the specified
             *                  errors or a void-value.
             */
            /*ara::core::Result<void>*/ void ReportExecutionState(ExecutionState state) const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_EXECUTION_CLIENT_H_

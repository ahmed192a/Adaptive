/**
 * @file execution_client.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of the execution client class
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_EXECUTION_CLIENT_H_
#define ARA_EXEC_EXECUTION_CLIENT_H_

#include <cstdint>
#include <string>
#include <variant>
#include "ara/exec/exec_error_domain.hpp"

namespace ara
{
    namespace exec
    {
        // SWS_EM_02000
        /**
         * Defines the proxy_skeleton states of a Process (see 7.3.1). Scoped Enumeration of uint8_t .
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
        class ExecutionClient final
        {
        private:
            // location of FIFO to communicate between EM & SM
            char fifo_l[30] = "execution_client_fifo";
            // index of File descriptor
            int fd;

        public:
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
             * Interface for a Process to report its proxy_skeleton state to Execution Management.
             * 
             * \param state     Value of the Execution State
             * 
             * \return          An instance of Boost::varient2::variant<void, ExecErrc>.
             *                  - The instance holds an ExecErrc containing either
             *                      -ara::exec::ExecErrc::kGeneralError     if some unspecified error occurred
             *                      -ara::exec::ExecErrc::kCommunication    Error Communication error between Application 
             *                                                              and Execution Management, e.g. unable to report 
             *                                                              state for Non-reporting Process.
             */
            std::variant<std::monostate , ExecErrc> ReportExecutionState(ExecutionState state) const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_EXECUTION_CLIENT_H_
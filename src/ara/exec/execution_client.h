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
#include "ara/exec/exec_error_domain.h"

namespace ara
{
    namespace exec
    {
        
        /**
         * @brief ExecutionState Defines the proxy_skeleton states of a Process (see 7.3.1). Scoped Enumeration of uint8_t .
         * @note SWS_EM_02000
         */
        enum class ExecutionState : uint8_t
        {
            kRunning = 0,     /*!< After a Process has been started by Execution Management, it reports ExecutionState kRunning. */
            kTerminating = 1, /*!< On receipt of SIGTERM, a Reporting Process acknowledges the request (by reporting kTerminating to Execution Management. */
        };

        /**
         * @brief ExecutionClient Class to implement operations on Execution Client.
         * @note SWS_EM_02001
         */
        class ExecutionClient final
        {
        private:
            char fifo_l[30] = "execution_client_fifo"; /*!< location of FIFO to communicate between EM & SM */
            int fd; /*!< index of File descriptor */

        public:
            
            /**
             * @brief Constructor that creates the Execution Client. 
             * @note SWS_EM_02030
             */
            ExecutionClient() noexcept;

            /**
             * @brief Destructor of the Execution Client instance.
             * @note SWS_EM_02002
             */
            ~ExecutionClient() noexcept;

            /**
             * @brief Interface for a Process to report its proxy_skeleton state to Execution Management.
             * @note SWS_EM_02003
             * @param [in] state     Value of the Execution State
             * 
             * @return          An instance of Boost::varient2::variant<void, ExecErrc>.
             *                  - The instance holds an ExecErrc containing either
             *                      -ara::exec::ExecErrc::kGeneralError     if some unspecified error occurred
             *                      -ara::exec::ExecErrc::kCommunication    Error Communication error between Application 
             *                                                              and Execution Management, e.g. unable to report 
             *                                                              state for Non-reporting Process.
             */
            std::variant< std::monostate , ExecErrc> ReportExecutionState(ExecutionState state) const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_EXECUTION_CLIENT_H_
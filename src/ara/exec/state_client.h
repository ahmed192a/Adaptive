/**
 * @file state_client.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of the StateClient class
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_EXEC_STATE_CLIENT_H
#define ARA_EXEC_STATE_CLIENT_H

#include "ara/exec/function_group_state.h"
#include "ara/exec/exec_error_domain.h"
#include <variant>
#include <future>
namespace ara
{
    namespace exec
    {

        /**
         * @brief StateClient class representing connection to Execution Management that is used to request Function
         *        Group state transitions (or other operations).
         * @note SWS_EM_02275
         * @note StateClient opens communication channel to Execution Management (e.g. POSIX FIFO). Each
         *       Process that intends to perform state management, shall create an instance of this class and it
         *       shall have rights to use it.
         */
        class StateClient
        {

            char fifo_l[30] = "state_client_fifo"; /*!< location of FIFO to communicate between EM & SM */
            int fd;                                /*!< index of File descriptor */
        public:
            
            /**
             * @brief Constructor that creates StateClient instance
             * @note SWS_EM_02276
             */
            StateClient() noexcept;

    
            /**
             * @brief Destructor of the StateClient instance
             * @note SWS_EM_02277
             */
            ~StateClient() noexcept;

            
            /**
             * @brief Method to request state transition for a single Function Group.
             * @note SWS_EM_02278
             * @details This method will request Execution Management to perform state transition and return
             * immediately. Returned ara::core::Future can be used to determine result of requested
             * transition.
             *
             * @param[in] state     representing meta-model definition of a state inside
             *                      a specific Function Group. Execution Management
             *                      will perform state transition from the current state to
             *                      the state identified by this parameter.
             *
             * @return ara::core::Future<void>  void if requested transition is successful, otherwise it
             *                                  returns ExecErrorDomain error.
             * 
             * @b  ara::exec::ExecErrc::kCancelled         if transition to the requested Function Group state
             *                                                  was cancelled by a newer request
             * @b  ara::exec::ExecErrc::kFailed             if transition to the requested Function Group state
             *                                                  failed
             * @b  ara::exec::ExecErrc::kInvalidArguments   if arguments passed doesn’t appear to be valid (e.g.
             *                                                  after a software update, given functionGroup doesn’t
             *                                                  exist anymore)
             * @b  ara::exec::ExecErrc::kCommunicationError if StateClient can’t communicate with Execution
             *                                                  Management (e.g. IPC link is down)
             * @b  ara::exec::ExecErrc::kGeneralError       if any other error occurs.
             *
             * @note Thread-safe
             */
            std::future<std::variant<std::monostate, ara::exec::ExecErrc>> SetState(FunctionGroupState const &state) const noexcept;

            // 
            /**
             * @brief Method to retrieve result of Machine State initial transition to Startup state.
             *
             * @details This method allows State Management to retrieve result of a transition specified by SWS_
             * EM_01023 and SWS_EM_02241. Please note that this transition happens once per machine
             * life cycle, thus result delivered by this method shall not change (unless machine is started
             * again).
             *
             * @return Future<void>  void if requested transition is successful, otherwise it
             *                       returns ExecErrorDomain error.
             *
             * @b  ara::exec::ExecErrc::kCancelled          if transition to the requested Function Group state
             *                                                  was cancelled by a newer request
             * @b  ara::exec::ExecErrc::kFailed             if transition to the requested Function Group state
             *                                                  failed
             * @b  ara::exec::ExecErrc::kCommunicationError if StateClient can’t communicate with Execution
             *                                                  Management (e.g. IPC link is down)
             * @b  ara::exec::ExecErrc::kGeneralError       if any other error occurs.
             *
             * @note Thread-safe
             * @note SWS_EM_02279
             */
            std::future<std::variant<std::monostate, ara::exec::ExecErrc>> GetInitialMachineStateTransitionResult() const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_STATE_CLIENT_H
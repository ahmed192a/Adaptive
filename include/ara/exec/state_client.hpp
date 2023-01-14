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

#include "ara/exec/function_group_state.hpp"
#include "ara/exec/exec_error_domain.hpp"
#include <variant>
#include <future>
namespace ara
{
    namespace exec
    {


        // SWS_EM_02275
        /**
         * \brief Class representing connection to Execution Management that is used to request Function
         *        Group state transitions (or other operations).
         *
         * \note StateClient opens communication channel to Execution Management (e.g. POSIX FIFO). Each
         *       Process that intends to perform state management, shall create an instance of this class and it
         *       shall have rights to use it.
         */
        class StateClient
        {
            // location of FIFO to communicate between EM & SM
            char fifo_l[30] = "state_client_fifo";
            // index of File descriptor
            int fd;
            public:
            // SWS_EM_02276
            /**
             * \brief Constructor that creates StateClient instance
             *
             */
            StateClient() noexcept;

            // SWS_EM_02277
            /**
             * \brief Destructor of the StateClient instance
             *
             */
            ~StateClient() noexcept;

            // SWS_EM_02278
            /**
             * \brief Method to request state transition for a single Function Group.
             *
             * This method will request Execution Management to perform state transition and return
             * immediately. Returned ara::core::Future can be used to determine result of requested
             * transition.
             *
             * \param[in] state     representing meta-model definition of a state inside
             *                      a specific Function Group. Execution Management
             *                      will perform state transition from the current state to
             *                      the state identified by this parameter.
             *
             * \return ara::core::Future<void>  void if requested transition is successful, otherwise it
             *                                  returns ExecErrorDomain error.
             *
             * \errors ara::exec::ExecErrc::kCancelled          if transition to the requested Function Group state
             *                                                  was cancelled by a newer request
             *         ara::exec::ExecErrc::kFailed             if transition to the requested Function Group state
             *                                                  failed
             *         ara::exec::ExecErrc::kInvalidArguments   if arguments passed doesn’t appear to be valid (e.g.
             *                                                  after a software update, given functionGroup doesn’t
             *                                                  exist anymore)
             *         ara::exec::ExecErrc::kCommunicationError if StateClient can’t communicate with Execution
             *                                                  Management (e.g. IPC link is down)
             *         ara::exec::ExecErrc::kGeneralError       if any other error occurs.
             *
             * Thread-safe
             */
            std::future<std::variant<std::monostate,ara::exec::ExecErrc>> SetState(FunctionGroupState const &state) const noexcept;

            // SWS_EM_02279
            /**
             * \brief Method to retrieve result of Machine State initial transition to Startup state.
             *
             * This method allows State Management to retrieve result of a transition specified by SWS_
             * EM_01023 and SWS_EM_02241. Please note that this transition happens once per machine
             * life cycle, thus result delivered by this method shall not change (unless machine is started
             * again).
             *
             * \return Future<void>  void if requested transition is successful, otherwise it
             *                       returns ExecErrorDomain error.
             *
             * \errors ara::exec::ExecErrc::kCancelled          if transition to the requested Function Group state
             *                                                  was cancelled by a newer request
             *         ara::exec::ExecErrc::kFailed             if transition to the requested Function Group state
             *                                                  failed
             *         ara::exec::ExecErrc::kCommunicationError if StateClient can’t communicate with Execution
             *                                                  Management (e.g. IPC link is down)
             *         ara::exec::ExecErrc::kGeneralError       if any other error occurs.
             *
             * Thread-safe
             */
            // ara::core::Future<void> 
            std::future<std::variant<std::monostate, ara::exec::ExecErrc>> GetInitialMachineStateTransitionResult() const noexcept;
        };
    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_STATE_CLIENT_H
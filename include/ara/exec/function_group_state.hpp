/**
 * @file function_group_state.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Defintion of FunctionGroupState class
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_FUNCTION_GROUP_STATE_H_
#define ARA_EXEC_FUNCTION_GROUP_STATE_H_
#include <string>
#include "ara/exec/function_group.hpp"

namespace ara
{
    namespace exec
    {
        // SWS_EM_02269
        /**
         * @brief Class representing Function Group State defined in meta-model (ARXML).
         * @class FunctionGroupState
         * @note Once created based on ARXML path, it’s proxy_skeleton value stay bounded to it for entire lifetime of
         *       an object.
         */
        class FunctionGroupState
        {
            private:
            std::string mc_state;                           //!< Function group state name
            std::string mFunction_group_name ;              //!< Function group name
            public:

            using CtorToken = struct{std::string fg_name; std::string c_state;};    //!< CtorToken type
            
            /**
             * @brief Set the FG name
             * 
             * @param fg_name 
             */
            void set_FGname(std::string fg_name);

            /**
             * @brief Set the FG state
             * 
             * @param state 
             */
            void set_states(std::string state);
            
            /**
             * @brief Get the FG name
             * 
             * @return std::string 
             */
            std::string get_FGname() const noexcept;
            
            /**
             * @brief Get the FG state
             * 
             * @return std::string 
             */
            std::string get_states() const noexcept;
            
            /**
             * @brief Pre construction method for FunctionGroupState.
             *
             * This method shall validate/verify meta-model path passed and perform any operation that could
             * fail and are expected to be performed in constructor.
             *
             * @param [in] functionGroup         the Function Group instance the state shall be
             *                                  connected with.
             * @param [in] metaModelIdentifier   stringified meta model identifier (short name path)
             *                                  where path separator is ’/’.
             *
             * @return std::variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken>     
             *                                                              a construction token from which an instance of
             *                                                              FunctionGroupState can be constructed, or Exec
             *                                                              ErrorDomain error.
             *
             */
            static std::variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken>  Preconstruct(FunctionGroup const &functionGroup, std::string metaModelIdentifier) noexcept;

            // SWS_EM_02271
            /**
             * @brief Constructor that creates FunctionGroupState instance
             *
             * @param [in] token     representing pre-constructed object.
             *
             */
            FunctionGroupState(FunctionGroupState::CtorToken &&token) noexcept;

            // SWS_EM_02272
            /**
             * \brief Destructor of the FunctionGroupState instance
             *
             */
            ~FunctionGroupState() noexcept;

            // SWS_EM_02273
            /**
             * @brief eq operator to compare with other FunctionGroupState instance.
             *
             * @param [in] other     FunctionGroupState instance to compare this one with.
             *
             * @return true         in case both FunctionGroupStates are
             *                      representing exactly the same meta-model element
             * @return false        otherwise
             *
             */
            bool operator==(FunctionGroupState const &other) const noexcept;

            // SWS_EM_02274
            /**
             * @brief uneq operator to compare with other FunctionGroupState instance.
             *
             * @param [in] other     FunctionGroupState instance to compare this one with.
             *
             * @return true         otherwise
             * @return false        in case both FunctionGroupStates are
             *                      representing exactly the same meta-model element
             *
             * Thread-safe
             */
            bool operator!=(FunctionGroupState const &other) const noexcept;
        };


    } // namespace exec

} // namespace ara

#endif

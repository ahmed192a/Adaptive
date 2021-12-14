#ifndef ARA_EXEC_FUNCTION_GROUP_STATE_H_
#define ARA_EXEC_FUNCTION_GROUP_STATE_H_
#include <string>
#include "function_group.h"
namespace ara
{
    namespace exec
    {
        // SWS_EM_02269
        /**
         * \brief Class representing Function Group State defined in meta-model (ARXML).
         *
         * \note Once created based on ARXML path, it’s internal value stay bounded to it for entire lifetime of
         *       an object.
         */
        class FunctionGroupState
        {
            using CtorToken = std::string;
            // SWS_EM_02270
            /**
             * \brief Pre construction method for FunctionGroupState.
             *
             * This method shall validate/verify meta-model path passed and perform any operation that could
             * fail and are expected to be performed in constructor.
             *
             * \param[in] functionGroup         the Function Group instance the state shall be
             *                                  connected with.
             * \param[in] metaModelIdentifier   stringified meta model identifier (short name path)
             *                                  where path separator is ’/’.
             *
             * \return ara::core::Result<FunctionGroupState::CtorToken>     a construction token from which an instance of
             *                                                              FunctionGroupState can be constructed, or Exec
             *                                                              ErrorDomain error.
             *
             * Thread-safe
             */
            // ara::core::StringView ---> std::string
            static FunctionGroupState::CtorToken Preconstruct(FunctionGroup const &functionGroup, std::string metaModelIdentifier) noexcept;

            // SWS_EM_02271
            /**
             * \brief Constructor that creates FunctionGroupState instance
             *
             * \param[in] token     representing pre-constructed object.
             *
             * \note Please note that token is destructed during object construction!
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
             * \brief eq operator to compare with other FunctionGroupState instance.
             *
             * \param[in] other     FunctionGroupState instance to compare this one with.
             *
             * \return true         in case both FunctionGroupStates are
             *                      representing exactly the same meta-model element
             * \return false        otherwise
             *
             * Thread-safe
             */
            bool operator==(FunctionGroupState const &other) const noexcept;

            // SWS_EM_02274
            /**
             * \brief uneq operator to compare with other FunctionGroupState instance.
             *
             * \param[in] other     FunctionGroupState instance to compare this one with.
             *
             * \return true         otherwise
             * \return false        in case both FunctionGroupStates are
             *                      representing exactly the same meta-model element
             *
             * Thread-safe
             */
            bool operator!=(FunctionGroupState const &other) const noexcept;
        };


    } // namespace exec

} // namespace ara

#endif

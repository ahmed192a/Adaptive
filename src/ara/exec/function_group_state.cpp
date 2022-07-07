/**
 * @file function_group_state.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/exec/function_group_state.hpp"
#include <string>

using namespace ara::exec;
namespace ara
{
    namespace exec
    {
        /**
         * @brief This method shall validate/verify meta-model path passed and perform any operation that could fail and are expected to be performed in constructor.
         * 
         * @param functionGroup 
         * @param metaModelIdentifier 
         * @return boost::variant2::variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> 
         */
        boost::variant2::variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> FunctionGroupState::Preconstruct(FunctionGroup const &functionGroup, std::string metaModelIdentifier) noexcept
        {
            boost::variant2::variant<ara::exec::ExecErrc, FunctionGroupState::CtorToken> token;
            int sl = metaModelIdentifier.find('/');
            if (functionGroup.get_FGname() != metaModelIdentifier.substr(0, sl))
            {
                token.emplace<0>(ara::exec::ExecErrc::kMetaModelError);
                return token;
            }
            FunctionGroupState::CtorToken ctoken;
            ctoken.fg_name = functionGroup.get_FGname();
            ctoken.c_state = metaModelIdentifier.substr(sl + 1, metaModelIdentifier.size() - sl - 1);
            token.emplace<1>(ctoken);
            return token;
        }

        /**
         * @brief Constructor that creates FunctionGroupState instance.
         * 
         * @param token 
         */
        FunctionGroupState::FunctionGroupState(FunctionGroupState::CtorToken &&token) noexcept
        {
            this->mFunction_group_name = token.fg_name;
            this->mc_state = token.c_state;
        }

        /**
         * @brief Destroy the Function Group State:: Function Group State object
         * 
         */
        FunctionGroupState::~FunctionGroupState() noexcept
        {
        }

        /**
         * @brief Set the Function Group name
         * 
         * @param fg_name 
         */
        void FunctionGroupState::set_FGname(std::string fg_name)
        {
            mFunction_group_name = fg_name;
        }

        /**
         * @brief set function group state
         * 
         * @param state 
         */
        void FunctionGroupState::set_states(std::string state)
        {
            mc_state = state;
        }

        /**
         * @brief get function group name
         * 
         * @return std::string 
         */
        std::string FunctionGroupState::get_FGname() const noexcept
        {
            return mFunction_group_name;
        }

        /**
         * @brief get function group state
         * 
         * @return std::string 
         */
        std::string FunctionGroupState::get_states() const noexcept
        {
            return mc_state;
        }

        /**
         * @param other 
         * @return true 
         * @return false 
         */
        bool FunctionGroupState::operator==(FunctionGroupState const &other) const noexcept
        {
            if (this->mFunction_group_name == other.mFunction_group_name)
            {
                return true;
            }
            return false;
        }

        /**
         * @param other 
         * @return true 
         * @return false 
         */
        bool FunctionGroupState::operator!=(FunctionGroupState const &other) const noexcept
        {
            if (this->mFunction_group_name == other.mFunction_group_name)
            {
                return false;
            }
            return true;
        }
    } // namespace exec

} // namespace ara

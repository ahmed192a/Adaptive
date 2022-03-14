/**
 * @file function_group.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ARA_EXEC_FUNCTION_GROUP_H_
#define ARA_EXEC_FUNCTION_GROUP_H_
#include <string>
#include <vector>
#include "ara/exec/exec_error_domain.hpp"
#include <nlohmann/json.hpp>
#include <variant>
namespace ara
{
    namespace exec
    {
         // SWS_EM_02263
        /**
         * Class representing Function Group defined in meta-model (ARXML).
         */
        class FunctionGroup final
        {
        private:
            std::string mFunction_group_name;
            std::vector<std::string> mstates;
        public:

            using CtorToken = nlohmann::json; //std::string;
            void set_FGname(std::string fg_name) ;
            void set_states(std::vector<std::string> states);
            std::string get_FGname() const noexcept;
            std::vector<std::string> get_states() const noexcept;


            // SWS_EM_02264
            /**
             * \brief Pre construction method for FunctionGroup.
             *
             * This method shall validate/verify meta-model path passed and perform any operation that could
             * fail and are expected to be performed in constructor.
             *
             * \param[in] metaModelIdentifier   stringified meta model identifier (short name path)
             *                                  where path separator is ’/’.
             *
             * \return Result<FunctionGroup::CtorToken>     a construction token from which an instance of
             *                                              FunctionGroup can be constructed, or ExecErrc
             *                                              error.
             *
             * Thread-safe
             *
             * \errors      ara::exec::ExecErrc::kMetaModelError    if metaModelIdentifier passed is incorrect (e.g.
             *                                                      FunctionGroupState identifier has been passed).
             *              ara::exec::ExecErrc::kGeneralError      if any other error occurs
             */
            // ara::core::StringView ---> std::string
            // 
            static std::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken>  Preconstruct(std::string metaModelIdentifier) noexcept;

            // SWS_EM_02265
            /**
             * \brief Constructor that creates FunctionGroup instance.
             *
             * \param[in] token     representing pre-constructed object.
             *
             * \note Please note that token is destructed during object construction!
             */
            FunctionGroup(FunctionGroup::CtorToken &&token) noexcept; 


            // SWS_EM_02266
            /**
             * \brief Destructor of the FunctionGroup instance.
             *
             */
            ~FunctionGroup() noexcept;

            // SWS_EM_02267
            /**
             * \brief eq operator to compare with other FunctionGroup instance.
             *
             * \param[in] other     FunctionGroup instance to compare this one with.
             *
             * \return true         in case both FunctionGroups are representing
             *                      exactly the same meta-model element,
             * \return false        otherwise.
             *
             * Thread-safe
             */
            bool operator==(FunctionGroup const &other) const noexcept;

            // SWS_EM_02268
            /**
             * \brief uneq operator to compare with other FunctionGroup instance.
             *
             * \param[in] other     FunctionGroup instance to compare this one with.
             * \return true         otherwise
             * \return false        in case both FunctionGroups are representing
             *                      exactly the same meta-model element
             *
             * Thread-safe
             */
            bool operator!=(FunctionGroup const &other) const noexcept;


            FunctionGroup &operator=(FunctionGroup &&other);

        };


    } // namespace exec

} // namespace ara

#endif
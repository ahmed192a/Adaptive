/**
 * @file function_group.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief Definition of FunctionGroup class
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
#include <boost/variant2/variant.hpp>

namespace ara
{
    namespace exec
    {
        /**
         * @class representing Function Group defined in meta-model (ARXML).
         */
        class FunctionGroup final
        {
        private:
            std::string mFunction_group_name;                          //!< Function group name
            std::vector<std::string> mstates;                          //!< Function group states
        public:
            using CtorToken = nlohmann::json;

            /**
             * @brief Set the function group name
             * 
             * @param fg_name 
             */
            void set_FGname(std::string fg_name) ;

            /**
             * @brief Set the function group states
             * 
             * @param states 
             */
            void set_states(std::vector<std::string> states);

            /**
             * @brief Get the function group name
             * 
             * @return std::string 
             */
            std::string get_FGname() const noexcept;

            /**
             * @brief Get the function group states
             * 
             * @return std::vector<std::string> 
             */
            std::vector<std::string> get_states() const noexcept;


            /**
             * \brief Pre construction method for FunctionGroup.
             *
             * This method shall validate/verify meta-model path passed and perform any operation that could
             * fail and are expected to be performed in constructor.
             *
             * \param[in] metaModelIdentifier   stringified meta model identifier (short name path)
             *                                  where path separator is ’/’.
             *
             * \return boost::variant2::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken>     
             *                              a construction token from which an instance of
             *                               FunctionGroup can be constructed, or ExecErrc error.
             *                          Errors:
             *                          -  ara::exec::ExecErrc::kMetaModelError    
             *                              if metaModelIdentifier passed is incorrect (e.g. FunctionGroupState identifier has been passed).
             *                          -  ara::exec::ExecErrc::kGeneralError      
             *                              if any other error occurs
             */
            static boost::variant2::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken>  Preconstruct(std::string metaModelIdentifier) noexcept;

            /**
             * \brief Constructor that creates FunctionGroup instance.
             *
             * \param[in] token     representing pre-constructed object.
             *
             * \note Please note that token is destructed during object construction!
             */
            FunctionGroup(FunctionGroup::CtorToken &&token) noexcept; 


            /**
             * \brief Destructor of the FunctionGroup instance.
             *
             */
            ~FunctionGroup() noexcept;

            /**
             * \brief eq operator to compare with other FunctionGroup instance.
             *
             * \param[in] other     FunctionGroup instance to compare this one with.
             *
             * \return true         in case both FunctionGroups are representing
             *                      exactly the same meta-model element,
             * \return false        otherwise.
             *
             */
            bool operator==(FunctionGroup const &other) const noexcept;

            /**
             * \brief uneq operator to compare with other FunctionGroup instance.
             *
             * \param[in] other     FunctionGroup instance to compare this one with.
             * \return true         otherwise
             * \return false        in case both FunctionGroups are representing
             *                      exactly the same meta-model element
             *
             */
            bool operator!=(FunctionGroup const &other) const noexcept;

            /**
             * @brief eq operator to compare with other FunctionGroup instance.
             * 
             * @param other                 FunctionGroup instance to compare this one with.
             * @return FunctionGroup&      this instance.
             */
            FunctionGroup &operator=(FunctionGroup &&other);

        };


    } // namespace exec

} // namespace ara

#endif
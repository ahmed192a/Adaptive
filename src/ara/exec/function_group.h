#ifndef ARA_EXEC_FUNCTION_GROUP_H_
#define ARA_EXEC_FUNCTION_GROUP_H_
#include <string>
namespace ara
{
    namespace exec
    {
        // SWS_EM_02263
        /**
         * @brief 
         * Class representing Function Group defined in meta-model (ARXML).
         * Once created based on ARXML path, it’s internal value stay bounded to it for entire lifetime of an object.
         */
        class FunctionGroup
        {
        private:
            /* data */
            using CtorToken = std::string;

        public:
            // SWS_EM_02264
            /**
             * @brief 
             * Pre construction method for FunctionGroup.
             * This method shall validate/verify meta-model path passed and perform any operation that could
             * fail and are expected to be performed in constructor.
             * 
             * \param[in] metaModelIdentifier       stringified meta model identifier (short name path) where path separator is ’/’.
             * 
             * \return Result< FunctionGroup::CtorToken >  a construction token from which an instance of FunctionGroup can be constructed, or ExecErrc error.

             */
            static FunctionGroup::CtorToken Preconstruct(std::string metaModelIdentifier) noexcept;

            // SWS_EM_02265
            /**
             * @brief Constructor that creates FunctionGroup instance.
             * Please note that token is destructed during object construction!
             * 
             * @param[in] token     representing pre-constructed object.
             */
            FunctionGroup(FunctionGroup::CtorToken &&token) noexcept;

            // SWS_EM_02266
            /**
             * @brief Destroy the Function Group object
             * 
             */
            ~FunctionGroup() noexcept;
        };

    } // namespace exec

} // namespace ara

#endif

/**
 * @file manifest_parser.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include "ara/exec/parser/manifest_parser_struct.hpp"
#include "ara/exec/function_group_state.hpp"
using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

struct GLOB{
    std::shared_ptr<FunctionGroup>c_FG;
    std::shared_ptr<FunctionGroupState> current_FGS;
};
namespace ara
{
    namespace exec
    {
        namespace parser
        {

            using json = nlohmann::json;        

            /**
             * @brief Class Manifest Parser used to parse Execution and Machine manifiests of the system
             * 
             */
            class ManifestParser 
            {
            public:
                /**
                 * @brief Construct a new Manifest Parser object
                 * 
                 */
                ManifestParser() noexcept = default;
                /**
                 * @brief Destroy the Manifest Parser object
                 * 
                 */
                ~ManifestParser() noexcept = default;
                /**
                 * @brief parse the execution manifest
                 * 
                 * @param path 
                 * @return ExecutionManifest 
                 */
                ExecutionManifest parse_execution_manifest(const std::string &path) noexcept(false) ;
                /**
                 * @brief parse machine manifest and fill the map of sys function groups
                 * 
                 * @param path 
                 * @param sys_FG 
                 * @return MachineManifest 
                 */
                MachineManifest   parse_machine_manifest(const std::string &path,map<std::string, GLOB> &sys_FG )noexcept(false) ;
            
            };

            /**
             * @brief read the value of the passed key from the json object
             * 
             * @tparam T 
             * @param json_obj 
             * @param key 
             * @param output_value 
             * @return true 
             * @return false 
             */
            template <typename T>
            bool read_value(const json &json_obj, const std::string &key, T &output_value) noexcept;
            /**
             * @brief read the data from the passed file and return json object filled with this data
             * 
             * @param path 
             * @return json 
             */
            json read_manifest_file(const std::string &path) noexcept(false);
            /**
             * @brief  checks if the json object violate the passed vector of keys
             * 
             * @param json_obj 
             * @param json_keys 
             */
            void validate_content(const json &json_obj, const std::vector<std::string> &json_keys) noexcept(false);



            /****************************************************************************/
            namespace EMJsonKeys // All Keys which should be in the Execution manifiests
            {
                const std::string kApplicationManifest = "Execution_manifest";
                const std::string kApplicationManifestId = "Execution_manifest_id";
                const std::string kProcess = "Process";
                const std::string kProcessName = "Process_name";
                const std::string kModeDependentStartupConfigs = "Mode_dependent_startup_configs";
                const std::string kStartupOptions = "Startup_options";
                const std::string kStartupOptionsOptionKind = "Option_kind";
                const std::string kStartupOptionsOptionName = "Option_name";
                const std::string kStartupOptionsOptionArg = "Option_arg";
                const std::string KExecutionDependencies = "ExecutionDependencies"; 
                const std::string KFunctionGroupDependencies = "FunctionGroupDependencies";
                const std::string kFunctionGroup = "Function_group";
                const std::string kModes = "Modes";
                const std::vector<std::string> kAsVector{kApplicationManifest,
                                                            kApplicationManifestId,
                                                            kProcess,
                                                            kProcessName,
                                                            kModeDependentStartupConfigs,
                                                            kStartupOptions,
                                                            kStartupOptionsOptionKind,
                                                            kStartupOptionsOptionName,
                                                            kStartupOptionsOptionArg,
                                                            KExecutionDependencies,
                                                            KFunctionGroupDependencies,
                                                            kFunctionGroup,
                                                            kModes};

            } // namespace EMJsonKeys
            /****************************************************************************/

            namespace MMJsonKeys    // All Keys which should be in the Machine manifiests
            {
                const std::string kMachineManifest = "Machine_manifest";
                const std::string kMachineManifestId = "Machine_manifest_id";
                const std::string kModeDeclarationGroup = "Mode_declaration_group";
                const std::string kFunctionGroupName = "Function_group_name";
                const std::string kModeDeclarations = "Mode_declarations";
                const std::string kMode = "Mode";
                const std::vector<std::string> kAsVector{kMachineManifest, kMachineManifestId,
                                                            kModeDeclarationGroup, kFunctionGroupName,
                                                            kModeDeclarations, kMode};
            } // namespace MMJsonKeys
        } // namespace parser
    }  // namespace exec
} // namespace ara

#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_H_

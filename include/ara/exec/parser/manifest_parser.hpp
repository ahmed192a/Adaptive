/**
 * @file manifest_parser.hpp
 * @author your name (you@domain.com)
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

            class IManifestParser
            {
            public:
                virtual ~IManifestParser() noexcept = default;
                virtual ExecutionManifest parse_execution_manifest(const std::string &path) noexcept(false) = 0;
                virtual MachineManifest parse_machine_manifest(const std::string &path, map<std::string, GLOB> &sys_FG) noexcept(false) = 0;
            };

            class ManifestParser : public IManifestParser
            {
            public:
                virtual ~ManifestParser() noexcept = default;
                virtual ExecutionManifest parse_execution_manifest(const std::string &path) noexcept(
                    false) override;
                virtual MachineManifest parse_machine_manifest(const std::string &path,map<std::string, GLOB> &sys_FG )noexcept(
                    false) override;
            private:    
            
            };

            namespace EMJsonKeys
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
                const std::string kMode = "Mode";

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
                                                            kMode};

            } // namespace EMJsonKeys

            namespace MMJsonKeys
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


            template <typename T>
            bool read_value(const json &json_obj, const std::string &key, T &output_value) noexcept;
            json read_manifest_file(const std::string &path) noexcept(false);
            void validate_content(const json &json_obj, const std::vector<std::string> &json_keys) 
                    noexcept(false);

        } // namespace parser
    }     // namespace exec
} // namespace ara

#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_H_

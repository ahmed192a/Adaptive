#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_H_

#include <memory>
#include <nlohmann/json.hpp>
#include "manifest_parser_struct.h"

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
                virtual MachineManifest parse_machine_manifest(const std::string &path) noexcept(false) = 0;
            };

            class ManifestParser : public IManifestParser
            {
            public:
                virtual ~ManifestParser() noexcept = default;
                virtual ExecutionManifest parse_execution_manifest(const std::string &path) noexcept(
                    false) override;

                virtual MachineManifest parse_machine_manifest(const std::string &path) noexcept(
                    false) override;

            private:
                json read_manifest_file(const std::string &path) noexcept(false);
                void validate_content(const json &json_obj, const std::vector<std::string> &json_keys) const
                    noexcept(false);
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

        } // namespace parser
    }     // namespace exec
} // namespace ara

#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_H_


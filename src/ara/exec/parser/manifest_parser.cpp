#include "manifest_parser.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace ara
{
    namespace exec
    {
        namespace parser
        {

            using json = nlohmann::json;
            /**
             * @brief checks of the json object has the key value in its children. if it doesn't exist, it will return false
             *          and if it exists, it will return true and get the json tree where key is the parent in put it in output_value
             * 
             * @tparam T            type of the output 
             * @param json_obj      json object struct
             * @param key           the value which we want to find in the children of json_obj
             * @param output_value  the output json object if we found the key
             * @return true 
             * @return false 
             */
            template <typename T>
            bool read_value(const json &json_obj, const std::string &key, T &output_value) noexcept
            {
                T tmp{};
                try
                {
                    tmp = json_obj.at(key);
                }
                catch (json::out_of_range &e)
                {
                    return false;
                }
                catch (json::type_error &e)
                {
                    return false;
                }

                output_value = tmp;
                return true;
            }
            /**
             * @brief read the exection manifest file and checks if its valid then pasring its content into struct of type ExecutionManifest
             * 
             * @param path                  var contain the path of the file
             * @return ExecutionManifest 
             */
            ExecutionManifest ManifestParser::parse_execution_manifest(const std::string &path) noexcept(false)
            {
                using namespace EMJsonKeys;
                auto manifest_json_full = read_manifest_file(path);
                ExecutionManifest man{};
                validate_content(manifest_json_full, kAsVector);

                json manifest_json_content{};
                read_value(manifest_json_full, kApplicationManifest, manifest_json_content);

                read_value(manifest_json_content, kApplicationManifestId, man.manifest_id);

                json processes{};
                if (read_value(manifest_json_content, kProcess, processes))
                {
                    for (auto &process : processes)
                    {
                        Process proc{};
                        read_value(process, kProcessName, proc.name);

                        json startup_configs{};
                        if (read_value(process, kModeDependentStartupConfigs, startup_configs))
                        {
                            for (auto &startup_config : startup_configs)
                            {
                                Process::StartupConfig config{};

                                json startup_options{};
                                if (read_value(startup_config, kStartupOptions, startup_options))
                                {
                                    for (auto &startup_option : startup_options)
                                    {
                                        Process::StartupConfig::StartupOption option{};

                                        read_value(startup_option, kStartupOptionsOptionKind, option.kind);
                                        read_value(startup_option, kStartupOptionsOptionName, option.name);
                                        read_value(startup_option, kStartupOptionsOptionArg, option.arg);

                                        config.startup_options.push_back(option);
                                    }
                                }

                                json machine_instance_refs{};
                                if (read_value(startup_config, KExecutionDependencies,
                                               machine_instance_refs))
                                {
                                    for (auto &machine_instance_ref : machine_instance_refs)
                                    {
                                        Process::StartupConfig::MachineInstanceRef
                                            mach_inst_ref{};
                                        read_value(machine_instance_ref, kFunctionGroup,
                                                   mach_inst_ref.function_group);
                                        read_value(machine_instance_ref, kMode, mach_inst_ref.mode);

                                        config.machine_instance_refs.push_back(mach_inst_ref);
                                    }
                                }
                                if (read_value(startup_config, KFunctionGroupDependencies,
                                               machine_instance_refs))
                                {
                                    for (auto &machine_instance_ref : machine_instance_refs)
                                    {
                                        Process::StartupConfig::MachineInstanceRef
                                            mach_inst_ref{};
                                        read_value(machine_instance_ref, kFunctionGroup,
                                                   mach_inst_ref.function_group);
                                        read_value(machine_instance_ref, kMode, mach_inst_ref.mode);

                                        config.machine_instance_refs.push_back(mach_inst_ref);
                                    }
                                }
                                proc.startup_configs.push_back(config);
                            }
                        }
                        man.processes.push_back(proc);
                    }
                }
                return man;
            }
            /**
             * @brief read the machine manifest file and checks if its valid then pasring its content into struct of type MachineManifest
             * 
             * @param path 
             * @return MachineManifest 
             */
            MachineManifest ManifestParser::parse_machine_manifest(const std::string &path) noexcept(false)
            {
                using namespace MMJsonKeys;
                auto manifest_json_full = read_manifest_file(path);
                MachineManifest man{};
                validate_content(manifest_json_full, kAsVector);

                json manifest_json_content{};
                read_value(manifest_json_full, kMachineManifest, manifest_json_content);

                read_value(manifest_json_content, kMachineManifestId, man.manifest_id);

                json mode_declaration_groups{};
                if (read_value(manifest_json_content, kModeDeclarationGroup, mode_declaration_groups))
                {
                    for (auto &mode_declaration_group : mode_declaration_groups)
                    {
                        MachineManifest::ModeDeclarationGroup mdg{};
                        read_value(mode_declaration_group, kFunctionGroupName, mdg.function_group_name);

                        json mode_declarations{};
                        if (read_value(mode_declaration_group, kModeDeclarations, mode_declarations))
                        {
                            for (auto &mode_declaration : mode_declarations)
                            {
                                MachineManifest::ModeDeclarationGroup::ModeDeclaration md{};

                                read_value(mode_declaration, kMode, md.mode);
                                mdg.mode_declarations.push_back(md);
                            }
                        }
                        man.mode_declaration_groups.push_back(mdg);
                    }
                }
                return man;
            }
            /**
             * @brief read the mainfest file and convert it into json object
             * 
             * @param path 
             * @return json 
             */
            json ManifestParser::read_manifest_file(const std::string &path) noexcept(false)
            {
                std::ifstream manifest_content(path, std::ifstream::binary);
                if (not manifest_content.is_open())
                {
                    throw std::runtime_error(
                        "ara::com::exec::parser::parse_manifest -> cannot open manifest: " + path + "\n");
                }

                json manifest_json{};

                try
                {
                    manifest_content >> manifest_json;
                }
                catch (json::exception &e)
                {
                    manifest_content.close();
                    throw std::runtime_error(
                        "ManifestParser::read_manifest_file -> cannot read manifest file. " +
                        std::string(e.what()));
                }

                manifest_content.close();
                return manifest_json;
            }
            /**
             * @brief checks if the file is the requested manifest by checking the first child name to match the first json_key
             * 
             * @param json_obj 
             * @param json_keys 
             */
            void ManifestParser::validate_content(const json &json_obj,
                                                  const std::vector<std::string> &json_keys) const
                noexcept(false)
            {
                // If validation will end with failure, this method will throw std::runtime_error
                json tmp;
                try
                {
                    tmp = json_obj.at(json_keys[0]);
                }
                catch (json::exception &e)
                {
                    // std::cerr << e.what() << '\n';
                    throw std::runtime_error(std::string(e.what()));
                }
            }

        } // namespace parser
    }     // namespace exec
} // namespace ara



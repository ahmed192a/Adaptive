/**
 * @file manifest_parser.cpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ara/exec/parser/manifest_parser.h"
#include <variant>
#include <fstream>
#include <iostream>

namespace ara
{
    namespace exec
    {
        namespace parser
        {

            using json = nlohmann::json;

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
                                if (read_value(startup_config, KFunctionGroupDependencies,
                                               machine_instance_refs))
                                {
                                    for (auto &machine_instance_ref : machine_instance_refs)
                                    {
                                        Process::StartupConfig::MachineInstanceRef
                                            mach_inst_ref{};
                                        read_value(machine_instance_ref, kFunctionGroup,
                                                   mach_inst_ref.function_group);
                                        std::string csv;
                                        read_value(machine_instance_ref, kModes, csv);
                                        int start = 0, end = 0;
                                        while (end != std::string::npos)
                                        {
                                            end = csv.find(',', start);
                                            mach_inst_ref.modes.push_back(csv.substr(start, end - start));
                                            start = end + 1;
                                        }
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

            MachineManifest ManifestParser::parse_machine_manifest(const std::string &path, std::map<std::string, ara::exec::parser::GLOB> &sys_FG) noexcept(
                false)
            {
                using namespace MMJsonKeys;
                auto manifest_json_full = read_manifest_file(path);

                MachineManifest man{};
                validate_content(manifest_json_full, kAsVector);

                json manifest_json_content{};
                read_value(manifest_json_full, kMachineManifest, manifest_json_content);

                read_value(manifest_json_content, kMachineManifestId, man.manifest_id);

                json mode_declaration_groups{};
                read_value(manifest_json_content, kModeDeclarationGroup, mode_declaration_groups); 
                for (auto &mode_declaration_group : mode_declaration_groups){
                    std::string FGName = mode_declaration_group[kFunctionGroupName];
                    std::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(path+"/"+FGName);
                    if (_functionGroup.index() == 0)
                    {
                        continue;
                        // man.parsed = true;
                        // break;
                    }
                    std::shared_ptr<FunctionGroup> fg = std::make_shared<FunctionGroup>(std::move(std::get<1>(_functionGroup)));
                    sys_FG[fg->get_FGname()].c_FG = fg;
                    FunctionGroupState::CtorToken token = {fg->get_FGname(), fg->get_states()[0]};
                    sys_FG[fg->get_FGname()].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
                }
                man.parsed = true;


                
                // while (1)
                // {

                //     std::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(path+"/"+mode_declaration_group[kFunctionGroupName]);
                //     if (_functionGroup.index() == 0)
                //     {
                //         man.parsed = true;
                //         break;
                //     }
                //     std::shared_ptr<FunctionGroup> fg = std::make_shared<FunctionGroup>(std::move(std::get<1>(_functionGroup)));
                //     sys_FG[fg->get_FGname()].c_FG = fg;
                //     FunctionGroupState::CtorToken token = {fg->get_FGname(), fg->get_states()[0]};
                //     sys_FG[fg->get_FGname()].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
                // }
                return man;
            }

            json read_manifest_file(const std::string &path) noexcept(false)
            {
                std::ifstream manifest_content(path, std::ifstream::binary);
                if (not manifest_content.is_open())
                {
                    throw std::runtime_error(
                        "ManifestParser::read_manifest_file -> Cannot Open Manifest: " + path + "\n");
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
                        "ManifestParser::read_manifest_file -> Cannot Read Nanifest:" +
                        std::string(e.what()));
                }

                manifest_content.close();
                return manifest_json;
            }

            bool validate_content(const json &json_obj, const std::vector<std::string> &json_keys) noexcept(false)
            {
                // If validation will end with failure, this method will throw std::runtime_error
                // if (json_obj.empty())
                // {
                //     throw std::runtime_error(
                //         "ManifestParser::validate_content -> Manifest is Empty");
                // }

                json tmp;
                try
                {
                    tmp = json_obj.at(json_keys[0]);
                }
                catch (json::exception &e)
                {
                    // throw std::runtime_error(std::string(e.what()));
                    return false;
                }
                return true;
            }

        } // namespace parser
    }     // namespace exec
} // namespace ara
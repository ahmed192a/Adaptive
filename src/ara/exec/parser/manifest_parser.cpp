/**
 * @file manifest_parser.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/exec/parser/manifest_parser.hpp"
#include <boost/variant2/variant.hpp>
#include <fstream>
#include <iostream>
// #include <stdexcept>
// #include <memory>
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
                                // if (read_value(startup_config, KExecutionDependencies,
                                //                machine_instance_refs))
                                // {
                                //     for (auto &machine_instance_ref : machine_instance_refs)
                                //     {
                                //         Process::StartupConfig::MachineInstanceRef
                                //             mach_inst_ref{};
                                //         read_value(machine_instance_ref, kFunctionGroup,
                                //                    mach_inst_ref.function_group);
                                //         read_value(machine_instance_ref, kMode, mach_inst_ref.mode);

                                //         config.machine_instance_refs.push_back(mach_inst_ref);
                                //     }
                                // }
                                if (read_value(startup_config, KFunctionGroupDependencies,
                                               machine_instance_refs))
                                {
                                    for (auto &machine_instance_ref : machine_instance_refs)
                                    {
                                        Process::StartupConfig::MachineInstanceRef
                                            mach_inst_ref{};
                                        read_value(machine_instance_ref, kFunctionGroup,
                                                   mach_inst_ref.function_group);
                                        json modes{};
                                        if(read_value(machine_instance_ref, kModes, modes)){
                                            std::string mode0{};
                                            for (auto &mode : modes)
                                            {
                                                if(read_value(mode, kMode, mode0))
                                                {
                                                    mach_inst_ref.modes.push_back(mode0);
                                                }
                                            }
                                            
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
                    std::string FG_name;
                    for (auto &mode_declaration_group : mode_declaration_groups)
                    {
                        std::shared_ptr<FunctionGroup> fg_ptr(new FunctionGroup(std::move(mode_declaration_group)));
                        
                        man.mode_declaration_groups.push_back(fg_ptr);
                    }
                }
                return man;
            }
            MachineManifest ManifestParser::pares_test(const std::string &path,map<std::string, GLOB> &sys_FG )noexcept(
                    false)
            {
                using namespace MMJsonKeys;
                auto manifest_json_full = read_manifest_file(path);
                MachineManifest man{};
                validate_content(manifest_json_full, kAsVector);

                json manifest_json_content{};
                read_value(manifest_json_full, kMachineManifest, manifest_json_content);

                read_value(manifest_json_content, kMachineManifestId, man.manifest_id);

                while(1)
                {
                    boost::variant2::variant<ara::exec::ExecErrc, FunctionGroup::CtorToken> _functionGroup = FunctionGroup::Preconstruct(path);
                    if(_functionGroup.index()==0)
                        break;
                    //cout<<"finish FG : " <<u++<<endl;
                    std::shared_ptr<FunctionGroup> fg =std::make_shared<FunctionGroup>(std::move(get<1>(_functionGroup)));
                    sys_FG[fg->get_FGname()].c_FG = fg;
                    FunctionGroupState::CtorToken token={fg->get_FGname(),fg->get_states()[0]};
                    sys_FG[fg->get_FGname()].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
                }
                return man;

            }


            /**
             * @brief read the mainfest file and convert it into json object
             *
             * @param path
             * @return json
             */
            json read_manifest_file(const std::string &path) noexcept(false)
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
            void validate_content(const json &json_obj,
                                                  const std::vector<std::string> &json_keys) 
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
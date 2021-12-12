#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_STRUCT_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_STRUCT_H_

#include <string>
#include <vector>
namespace ara
{
    namespace exec
    {
        namespace parser
        {
            /**
             * @brief Struct for execution manifiest
             * 
             */
            struct ExecutionManifest
            {
                struct Process
                {
                    struct StartupConfig
                    {
                        struct StartupOption
                        {
                            std::string kind{};
                            std::string name{};
                            std::string arg{};
                            bool operator==(const StartupOption &) const noexcept;
                            bool operator!=(const StartupOption &) const noexcept;
                        };

                        struct MachineInstanceRef
                        {
                            std::string function_group{};
                            std::string mode{};
                            bool operator==(const MachineInstanceRef &) const noexcept;
                            bool operator!=(const MachineInstanceRef &) const noexcept;
                        };

                        std::vector<StartupOption> startup_options{};
                        std::vector<MachineInstanceRef> machine_instance_refs{};
                        bool operator==(const StartupConfig &) const noexcept;
                        bool operator!=(const StartupConfig &) const noexcept;
                    };

                    std::string name{};
                    std::vector<StartupConfig> startup_configs{};

                    bool operator==(const Process &) const noexcept;
                    bool operator!=(const Process &) const noexcept;
                };

                std::string manifest_id{};
                std::vector<Process> processes{};

                bool operator==(const ExecutionManifest &) const noexcept;
                bool operator!=(const ExecutionManifest &) const noexcept;
            };

            /**
             * @brief Struct for machine manifiest
             * 
             */
            struct MachineManifest
            {
                struct ModeDeclarationGroup
                {
                    struct ModeDeclaration
                    {
                        std::string mode{};
                        bool operator==(const ModeDeclaration &) const noexcept;
                        bool operator!=(const ModeDeclaration &) const noexcept;
                    };

                    std::string function_group_name{};
                    std::vector<ModeDeclaration> mode_declarations{};
                    bool operator==(const ModeDeclarationGroup &) const noexcept;
                    bool operator!=(const ModeDeclarationGroup &) const noexcept;
                };

                std::string manifest_id{};
                std::vector<ModeDeclarationGroup> mode_declaration_groups{};
                bool operator==(const MachineManifest &) const noexcept;
                bool operator!=(const MachineManifest &) const noexcept;
            };


            // Definitions of operators
                        bool ExecutionManifest::operator==(const ExecutionManifest &other) const noexcept
            {
                return (manifest_id == other.manifest_id) && (processes == other.processes);
            }

            bool ExecutionManifest::operator!=(const ExecutionManifest &other) const noexcept
            {
                return !(*this == other);
            }

            bool ExecutionManifest::Process::operator==(const Process &other) const noexcept
            {
                return (name == other.name) && (startup_configs == other.startup_configs);
            }

            bool ExecutionManifest::Process::operator!=(const Process &other) const noexcept
            {
                return !(*this == other);
            }

            bool ExecutionManifest::Process::StartupConfig::operator==(const StartupConfig &other) const
                noexcept
            {
                return (startup_options == other.startup_options) &&
                       (machine_instance_refs == other.machine_instance_refs);
            }

            bool ExecutionManifest::Process::StartupConfig::operator!=(const StartupConfig &other) const
                noexcept
            {
                return !(*this == other);
            }

            bool ExecutionManifest::Process::StartupConfig::StartupOption::operator==(
                const StartupOption &other) const noexcept
            {
                return (kind == other.kind) && (name == other.name) && (arg == other.arg);
            }

            bool ExecutionManifest::Process::StartupConfig::StartupOption::operator!=(
                const StartupOption &other) const noexcept
            {
                return !(*this == other);
            }

            bool ExecutionManifest::Process::StartupConfig::MachineInstanceRef::operator==(
                const MachineInstanceRef &other) const noexcept
            {
                return (function_group == other.function_group) && (mode == other.mode);
            }

            bool ExecutionManifest::Process::StartupConfig::MachineInstanceRef::operator!=(
                const MachineInstanceRef &other) const noexcept
            {
                return !(*this == other);
            }

            bool MachineManifest::operator==(const MachineManifest &other) const noexcept
            {
                return (manifest_id == other.manifest_id) &&
                       (mode_declaration_groups == other.mode_declaration_groups);
            }

            bool MachineManifest::operator!=(const MachineManifest &other) const noexcept
            {
                return !(*this == other);
            }

            bool MachineManifest::ModeDeclarationGroup::operator==(const ModeDeclarationGroup &other) const
                noexcept
            {
                return (function_group_name == other.function_group_name) &&
                       (mode_declarations == other.mode_declarations);
            }

            bool MachineManifest::ModeDeclarationGroup::operator!=(const ModeDeclarationGroup &other) const
                noexcept
            {
                return !(*this == other);
            }

            bool MachineManifest::ModeDeclarationGroup::ModeDeclaration::operator==(
                const ModeDeclaration &other) const noexcept
            {
                return (mode == other.mode);
            }

            bool MachineManifest::ModeDeclarationGroup::ModeDeclaration::operator!=(
                const ModeDeclaration &other) const noexcept
            {
                return !(*this == other);
            }


        } // namespace parser
        
    } // namespace exec
    
} // namespace ara




#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_STRUCT_H_
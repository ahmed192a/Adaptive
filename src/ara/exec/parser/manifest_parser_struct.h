#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_

#include <string>
namespace ara
{
    namespace exec
    {
        namespace parser
        {
            /**
             * @brief class for execution manifiest
             * 
             */
            class Process
                {
                    public:
                    class StartupConfig
                    {
                        public:
                        class StartupOption
                        {
                            public:
                            std::string kind{};
                            std::string name{};
                            std::string arg{};
                            bool operator==(const StartupOption &) const noexcept;
                            bool operator!=(const StartupOption &) const noexcept;
                        };

                        class MachineInstanceRef
                        {
                            public:
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
            class ExecutionManifest
            {
                public:
                

                std::string manifest_id{};
                std::vector<Process> processes{};

                bool operator==(const ExecutionManifest &) const noexcept;
                bool operator!=(const ExecutionManifest &) const noexcept;
            };

            /**
             * @brief class for machine manifiest
             * 
             */

            class MachineManifest
            {
                public:
                class ModeDeclarationGroup
                {
                    public:
                    class ModeDeclaration
                    {
                        public:
                        std::string mode{};
                        bool operator==(const ModeDeclaration &) const noexcept;
                        bool operator!=(const ModeDeclaration &) const noexcept;
                    };

                    std::string function_group_name{};
                    std::vector<ModeDeclaration> mode_declarations{};
                    bool operator==(const ModeDeclarationGroup &) const noexcept;
                    bool operator!=(const ModeDeclarationGroup &) const noexcept;
                };
                // mach_id/fuG_ID
                std::string manifest_id{};
                std::vector<ModeDeclarationGroup> mode_declaration_groups{};
                bool operator==(const MachineManifest &) const noexcept;
                bool operator!=(const MachineManifest &) const noexcept;
            };


        } // namespace parser
        
    } // namespace exec
    
} // namespace ara




#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_
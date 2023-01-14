/**
 * @file manifest_parser_struct.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief mainfest parser structures, configurations and classes
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_
#define ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_

#include <memory>
#include "ara/exec/execution_client.h"
#include "ara/exec/function_group.h"


namespace ara
{
    namespace exec
    {
        namespace parser
        {
            /**
             * @brief Process class to hold all prcoess configuration and handles to
             *          run and terminate the process
             *
             */
            class Process
            {
            public:
                /**
                 * @brief StartupConfig class to store the configurations
                 *           on which we will run the process
                 *
                 */
                class StartupConfig
                {
                public:
                    /**
                     * @brief StartupOption class to store all options that can be passed
                     *              to the process before running it
                     * @note ex. -p <port> -d <debug>
                     * @param   kind: to choose if it's short name option (-v) or long name (--version)
                     * @param   name: name of the option (ex. -p , -v, -d, .....)
                     * @param   arg:  is the passed arrgument (ex. portnum, debug flag,....)
                     */
                    class StartupOption
                    {
                    public:
                        std::string kind{}; /*!< short or long name option */
                        std::string name{}; /*!< name of the option */
                        std::string arg{};  /*!< argument of the option */

                        /**
                         * @brief eq operator to compare with other StartupOption instance
                         *
                         * @return true
                         * @return false
                         */
                        bool operator==(const StartupOption &) const noexcept;

                        /**
                         * @brief uneq operator to compare with other StartupOption instance
                         *
                         * @return true
                         * @return false
                         */
                        bool operator!=(const StartupOption &) const noexcept;
                    };
                    /**
                     * @brief MachineInstanceRef Class (Machine Instance Reference ) to store the reference
                     *          to the Funcion groups state which this process depends on
                     * @param function_group name of the functiongroup
                     * @param modes          all modes that the process depend on FG to be in them
                     *
                     */
                    class MachineInstanceRef
                    {
                    public:
                        std::string function_group{};     /*!< name of the functiongroup */
                        std::vector<std::string> modes{}; /*!< all modes that the process depend on FG to be in them */

                        /**
                         * @brief eq operator to compare with other MachineInstanceRef instance
                         *
                         * @return true
                         * @return false
                         */
                        bool operator==(const MachineInstanceRef &) const noexcept;

                        /**
                         * @brief uneq operator to compare with other MachineInstanceRef instance
                         *
                         * @return true
                         * @return false
                         */
                        bool operator!=(const MachineInstanceRef &) const noexcept;
                    };

                    std::vector<StartupOption> startup_options{};            /*!< all options that can be passed to the process before running it */
                    std::vector<MachineInstanceRef> machine_instance_refs{}; /*!< all references to the function groups state which this process depends on */

                    /**
                     * @brief eq operator to compare with other StartupConfig instance
                     *
                     * @return true
                     * @return false
                     */
                    bool operator==(const StartupConfig &) const noexcept;

                    /**
                     * @brief uneq operator to compare with other StartupConfig instance
                     *
                     * @return true
                     * @return false
                     */
                    bool operator!=(const StartupConfig &) const noexcept;
                };
                std::vector<Process *> dep_process;                                                /*!< pointer to all dependent processes */
                int _pid = 0;                                                                      /*!< process id which is initialized by zero in case not running */
                ara::exec::ExecutionState current_state = ara::exec::ExecutionState::kTerminating; /*!< current state of the process */
                std::string name{};                                                                /*!< name of the process */
                std::vector<StartupConfig> startup_configs{};                                      /*!< all startup configurations of the process */
                StartupConfig *current_config = nullptr;                                           /*!< pointer to the current startup configuration of the process */
                bool prun = false;                                                                 /*!< flag to indicate if the process is running or not */
                int exec_clinet_fd = 0;                                                            /*!< file discriptor for execution client fifo */

                /**
                 * @brief eq operator to compare with other Process instances
                 *
                 * @return true
                 * @return false
                 */
                bool operator==(const Process &) const noexcept;

                /**
                 * @brief uneq operator to compare with other Process instances
                 *
                 * @return true
                 * @return false
                 */
                bool operator!=(const Process &) const noexcept;

                /**
                 * @brief starting the process
                 *
                 * @return true
                 * @return false
                 */
                bool start();

                /**
                 * @brief terminating the process
                 *
                 */
                void terminate();
            };

            /**
             * @brief Definition of the ExecutionManifest class
             *
             */
            class ExecutionManifest
            {
            public:
                std::string manifest_id{};
                std::vector<Process> processes{};

                /**
                 * @brief eq operator to compare with other ExecutionManifest instance
                 *
                 * @return true
                 * @return false
                 */
                bool operator==(const ExecutionManifest &) const noexcept;

                /**
                 * @brief uneq operator to compare with other ExecutionManifest instance
                 *
                 * @return true
                 * @return false
                 */
                bool operator!=(const ExecutionManifest &) const noexcept;
            };

            /**
             * @brief MachineManifest definition of the machine manifest 
             *
             */

            class MachineManifest
            {
            public:
                std::string manifest_id{};      /*!< manifest id */
                bool parsed = false;            /*!< flag to indicate if the manifest is parsed or not */

                /**
                 * @brief eq operator to compare with other MachineManifest instance
                 *
                 * @return true
                 * @return false
                 */
                bool operator==(const MachineManifest &) const noexcept;

                /**
                 * @brief uneq operator to compare with other MachineManifest instance
                 *
                 * @return true
                 * @return false
                 */
                bool operator!=(const MachineManifest &) const noexcept;
            };

        } // namespace parser

    } // namespace exec

} // namespace ara

#endif // ARA_EXEC_PARSER_MANIFEST_PARSER_class_H_
#include "ara/exec/parser/manifest_parser_struct.hpp"
#include <iostream>
#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <utility>
#include <sys/wait.h>
#include "sys/stat.h"
#include <signal.h>

using namespace ara::exec::parser;
using namespace std;


// Definitions of operators
bool ExecutionManifest::operator==(const ExecutionManifest &other) const noexcept
{
    return (manifest_id == other.manifest_id) && (processes == other.processes);
}

bool ExecutionManifest::operator!=(const ExecutionManifest &other) const noexcept
{
    return !(*this == other);
}

bool Process::operator==(const Process &other) const noexcept
{
    return (name == other.name) && (startup_configs == other.startup_configs);
}

bool Process::operator!=(const Process &other) const noexcept
{
    return !(*this == other);
}
bool Process::start(){
    if (_pid != 0) {
        //TRACE_ERROR("EM: Invalid call for Start(): the process is already running");
        std::cout<<"EM: Invalid call for Start(): the process is already running"<<endl;
        return false;
    }
    //TRACE_INFO("EM: Starting executable " << executable_);
    std::cout<<"EM: Starting executable "+name<<endl;
    
    if (mkfifo("processes/execution_client_fifo", 0666) == -1)
    {
        if (errno != EEXIST)
        {
            // TO DO
            // Log Error : coundn't create fifo
        }
    }
    int pid = fork();
    if (pid < 0) {
        //TRACE_ERROR("EM: fork() failed" << ", errno: " << errno);
        std::cout<<"EM: fork() failed" << ", errno: " << errno<<endl;
        return false;
    }
    if (pid == 0) {
        // The child process

        // Change working directory to application root
        if (chdir("processes") != 0) {
            //TRACE_FATAL("EM: chdir() failed for dir " << childWorkDir << ",errno: " << errno);
            std::cout<<"EM(child): chdir() failed for dir processes/,errno: " << errno<<endl;
        } else {
            // Set environment variables
            //for (const auto& variable : environment_) {
            //    ::putenv(const_cast<char*>(variable.c_str()));  
            //}

            // Redirect terminal output for application to /var/redirected/<application_name_>
            //utility::RedirectProcessOutput(("/var/redirected/"+name).c_str());


            //cout<<"EM(child): in dir "<<get_current_dir_name()<<endl;
            // Execute the executable with the specified arguments
            char * args[]={
                &name[0],
                NULL
            };
            execve(args[0], &args[0],NULL);

            // When execv() is successful, the current process is replaced by the child.
            // Otherwise, the following code will be reached.
            //TRACE_FATAL("EM: execv() failed for executable " << childPath<< ", errno: " << errno);
            std::cout<<"EM(child): execv() failed for executable " << name.c_str() << ", errno: " << errno<<endl;
        }


        // Terminate the failed child process
        std::abort();
        return false;

    } else if (pid > 0) {
        // The parent process

   
        // get file discreptor
        int fd = open((startup_configs[0].startup_options[0].name+"/execution_client_fifo").c_str(), O_RDONLY);
        if(fd == -1) {
            std::cout<< "EM:[ERROR] => can't open fifo";
        }else{
            ara::exec::ExecutionState state;
            if (read(fd, &state, sizeof(state)) == -1)
            {
                // TO DO
                // Log Error : counldn't send the state to fifo
            }
            close(fd);
            if(state == ara::exec::ExecutionState::kRunning) 
            std::cout<<"EM: report succeed "<<(int) state<<endl;
        }





       // int status = 11;
        //waitpid(pid, &status, 0);

        //state_ = ProcessState::kStarting;
        _pid = pid;

        //TRACE_INFO("EM: Forked child ’" << executable_ << "’ with PID " <<_pid);
        std::cout<<"EM: Forked child ’" << name << "’ with PID " <<_pid<<endl;
        // The only successfull return
        return true;

    }
    return false;
}

void Process::terminate(){
    //  terminate seq of process
    kill(_pid, SIGTERM);
    wait(NULL);

}

bool Process::StartupConfig::operator==(const StartupConfig &other) const
    noexcept
{
    return (startup_options == other.startup_options) &&
            (machine_instance_refs == other.machine_instance_refs);
}

bool Process::StartupConfig::operator!=(const StartupConfig &other) const
    noexcept
{
    return !(*this == other);
}

bool Process::StartupConfig::StartupOption::operator==(
    const StartupOption &other) const noexcept
{
    return (kind == other.kind) && (name == other.name) && (arg == other.arg);
}

bool Process::StartupConfig::StartupOption::operator!=(
    const StartupOption &other) const noexcept
{
    return !(*this == other);
}

bool Process::StartupConfig::MachineInstanceRef::operator==(
    const MachineInstanceRef &other) const noexcept
{
    return (function_group == other.function_group) && (mode == other.mode);
}

bool Process::StartupConfig::MachineInstanceRef::operator!=(
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
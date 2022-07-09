/**
 * @file mnifest_parser_struct.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/exec/parser/manifest_parser_struct.hpp"
#include <iostream>
#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <utility>
#include <sys/wait.h>
#include "sys/stat.h"
#include <signal.h>

#define  W_DIR "processes/"

// #include <string>
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
        cout<<"EM: Invalid call for Start(): the process is already running"<<endl;
        return false;
    }
    cout<<"EM: Starting executable \""+name<<"\", Path: \""<<get_current_dir_name()<<"\""<<endl;
    if (mkfifo(("processes/"+name+"/execution_client_fifo").c_str(), 0666) == -1)
    {
        if (errno != EEXIST)
        {
            // TO DO
            // Log Error : coundn't create fifo
            cout<<"EM: couldn't create fifo"<<endl;
            
        }
        cout<<"EM: fifo already exists"<<endl;
        return false;
    }
    int pid = fork();
    if (pid < 0) {
        cout<<"EM: fork() failed" << ", errno: " << errno<<endl;
        return false;
    }
    if (pid == 0) {//child
        // Change working directory to application root
        if (chdir((W_DIR+name).c_str()) != 0) {
            cout<<name<<": chdir() failed for dir " << W_DIR+name << ",errno: " << errno<<endl;
        } 
        else {
            // Set environment variables
            //for (const auto& variable : environment_) {
            //    ::putenv(const_cast<char*>(variable.c_str()));  
            //}

            // Redirect terminal output for application to /var/redirected/<application_name_>
            // utility::RedirectProcessOutput(("/var/redirected/"+name).c_str());
            freopen (("../redirected/"+name+".txt").c_str(), "w", stdout);

            //cout<<"EM(child): in dir "<<get_current_dir_name()<<endl;
            // Execute the executable with the specified arguments
            char * args[]={
                &name[0],
                NULL
            };
            cout<<name<<": Executing... "<<endl;
            execve(args[0], &args[0],NULL);

            // When execv() is successful, the current process is replaced by the child.
            // Otherwise, the following code will be reached.
            cout<<"EM(child): execv() failed for executable " << name << ", errno: " << errno<<endl;
        }

        // Terminate the failed child process
        std::abort();
        return false;

    } else if (pid > 0) {//parent
        // get file discreptor
        exec_clinet_fd = open(("processes/"+name+"/execution_client_fifo").c_str(), O_RDONLY);
        if(exec_clinet_fd == -1) {
            cout<< "EM:[ERROR] => can't open fifo"<<endl;
        }else{
            if (read(exec_clinet_fd, &current_state, sizeof(current_state)) == -1)
            {
                // TO DO
                // Log Error : counldn't send the state to fifo
                cout<<"EM: couldn't read the state to fifo"<<endl;
                return false;
            }
            //close(fd);
            if(current_state == ara::exec::ExecutionState::kRunning) 
            cout<<"EM: report succeed executing \""<<name<<"\". [code:"<<(int) current_state<<", pid:"<<pid<<"]"<<endl;
        }
        //state_ = ProcessState::kStarting;
        _pid = pid;
        prun = true;
        return true;
    }
    return false;
}

void Process::terminate(){
    kill(_pid, SIGTERM);        // send SIGTERM to the process to terminate it 

    // wait for the process to terminate and read its status from execution client
    if (read(exec_clinet_fd, &current_state, sizeof(current_state)) == -1){
        // TO DO
        // Log Error : counldn't send the state to fifo
        cout<<"EM: couldn't read the state to fifo"<<endl;
    }
    close(exec_clinet_fd);      // close the execution client fifo

    if(current_state == ara::exec::ExecutionState::kTerminating) 
        cout<<"EM: report succeed terminatting "<<name<<" with code ("<<(int) current_state<<")"<<endl;
    else
        cout<<"EM: ERROR: coundn't Terminate the process "<<name<<endl;
    
    wait(NULL);                 // wait for the process to be terminated
    // delete the unused execution client fifo
    unlink(("processes/"+name+"/execution_client_fifo").c_str());   
    this->prun = false;         // set flag to indicated process not running
    this->current_config = nullptr; // clear the pointer of current configuration
    this->_pid = 0;             // reset the process id to default value 0
}

bool Process::StartupConfig::operator==(const StartupConfig &other) const noexcept{
    return (startup_options == other.startup_options) && (machine_instance_refs == other.machine_instance_refs);
}

bool Process::StartupConfig::operator!=(const StartupConfig &other) const noexcept{
    return !(*this == other);
}

bool Process::StartupConfig::StartupOption::operator==( const StartupOption &other) const noexcept{
    return (kind == other.kind) && (name == other.name) && (arg == other.arg);
}

bool Process::StartupConfig::StartupOption::operator!=( const StartupOption &other) const noexcept{
    return !(*this == other);
}

bool Process::StartupConfig::MachineInstanceRef::operator==( const MachineInstanceRef &other) const noexcept{
    return  (function_group == other.function_group) && (modes == other.modes);
}

bool Process::StartupConfig::MachineInstanceRef::operator!=( const MachineInstanceRef &other) const noexcept{
    return  !(*this == other);
}

bool MachineManifest::operator==(const MachineManifest &other) const noexcept{
    return (manifest_id == other.manifest_id);
}

bool MachineManifest::operator!=(const MachineManifest &other) const noexcept{
    return !(*this == other);
}

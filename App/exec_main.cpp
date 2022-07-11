/**
 * @file exec_main.cpp
 * @brief EM
 * @version 0.1
 * @date 2022-06-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/***************************************************************************
 *                          Include Section                                *
 ***************************************************************************/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <filesystem> // to get all files in certain dir
#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <utility>
#include <sys/wait.h>
#include <filesystem>

#include "ara/exec/parser/manifest_parser.hpp"
#include "ara/exec/function_group.hpp"
#include "ara/exec/function_group_state.hpp"
#include "ara/Log_trace/Log.hpp"

/***************************************************************************
 *                           Define Section                                *
 ***************************************************************************/
#define MC_MF   "/Manifests/machine_manifest.json"
#define EM_MF "/Manifests/execution_manifest.json"
#define SM_FIFO "processes/sm_process/state_client_fifo"
#define MAX_BUF 1024

/***************************************************************************
 *                      Namespace Section                                 *
 ***************************************************************************/
using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

/***************************************************************************
 *                      Fucntions Decleration Section                      *
 ***************************************************************************/

int exec_init();
void change_state(std::string n_FG, std::string n_state);
void view_out();
void p_operate();
void p_terminate();
void handle_sigterm(int sig){
    cout<<"EM: SIGTERM received"<<endl;
    change_state("MachineFG", "Shuttingdown");
    cout<<"EM: Shutting down"<<endl;
    exit(0);
}
/***************************************************************************
 *                      Global Variable Section                            *
 ***************************************************************************/
static map<string, GLOB> sys_FG;                // Map of all function groups of the system
std::vector<Process> process_pool;              // Vector of all processes of the system

// Backup streambuffers of  cout
streambuf* stream_buffer_cout = cout.rdbuf();   // backup cout stream buffer
streambuf* stream_buffer_cin = cin.rdbuf();     // backup cin stream buffer

/**
 * @brief Main program of Excution Managiment program
 * @param argc Number of arguments
 * @param argv Arguments
 * 
 * @note   this is the Main program of Excution managiment which has the following functions:
 *              1. Parsing manifest files
 *              2. start state management
 *              3. get the state from SM
 *              4. switch state (start terminating sequence and starting sequence)
 * @return  0 if success or 1 if failed 
 */
int main(int argc, char ** argv){
    signal(SIGTERM, handle_sigterm);    // handle SIGTERM signal used for terminating the system

    // check if there are files the the directory "processes/redirected"
    // if there are files, then delete them
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("processes/redirected")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] != '.') {
                remove((string("processes/redirected/") + ent->d_name).c_str());
            }
        }
        closedir (dir);
    }



    //Create redirected folder for cout of all processes,check if the folder exists
    // if(filesystem::exists("processes/redirected")) filesystem::remove_all("processes/redirected");
    // filesystem::create_directories("processes/redirected");    

    // file stream to write the output of EM to a EM.txt file
    fstream file;   
    file.open("processes/redirected/EM.txt", ios::out); 
    cout.rdbuf(file.rdbuf()); 
    // open the file EM.txt to visualize it in real time in another genome terminal
    //system("gnome-terminal -- sh -c 'tail -f -n 100 processes/redirected/EM.txt'");



/***************************************************************************
 *                      Start Of Execution Manager                          *
 ***************************************************************************/
    // Initialize the system
    cout << "\n-    EM Initialization..."<<endl;
    // print the pid of EM
    cout << "-    EM: PID: " << getpid() << endl << endl;
    exec_init();                            // initialize the system and parse the manifest files

    mkfifo(SM_FIFO, 0666);                  // create the fifo to communicate with State Management process
    std::string msg;                        // message to send to SM
    msg.resize(MAX_BUF);                    // resize the message to MAX_BUF bytes

    //change the state of MachineFG to Starting-up to start the state management process
    change_state("MachineFG" , "Pre-Starting-up"); 
    change_state("MachineFG" , "Starting-up"); 

    int fd = open(SM_FIFO, O_RDONLY);   // open the fifo to read the state from SM

    /****************************** Main Logic of EM ***********************************/
    // get FG name and new state from SM an change the state
    while(sys_FG["MachineFG"].current_FGS->get_states() != "off"){
        int n= read(fd, &msg[0], MAX_BUF); // read the state from SM
        std::string FG_name = msg.substr(0, msg.find("/")); // get the FG name
        std::string new_state = msg.substr(msg.find("/")+1, n-(msg.find('/')+1)); // get the new state
        change_state(FG_name, new_state); // change the state of FG
    }
    /***********************************************************************************/

    close(fd);                          // close the fifo
    unlink(SM_FIFO);                    // delete the fifo
    cout << "\n-    EM Terminated."<<endl;

    cout.rdbuf(stream_buffer_cout);     // restore the cout stream buffer
    file.close();                       // close the file stream
    view_out();                         // view the output of all processe
    return 0;
}
/**
 * @brief initialize the system and parse the manifest files
 * 
 * @return void
 */
int exec_init(){
    //Parser Inistantiation
    ManifestParser parser;              
    //Parse Machine manifest
    MachineManifest MM = parser.parse_machine_manifest(std::string(get_current_dir_name())+ MC_MF, sys_FG);
    cout<<"- Machine Manifest ID: \""+MM.manifest_id+"\" Parsed Successfully, FGs No.: "<<sys_FG.size()<<endl;
    //Parse Execution manifests
    ExecutionManifest EM = parser.parse_execution_manifest(std::string(get_current_dir_name())+ EM_MF);
    cout<<"- Execution Manifest ID: \""+EM.manifest_id+"\" Parsed Successfully, Processes No.: "<<EM.processes.size()<<endl;
    //Fetching processes from execution manifest parser
    process_pool = EM.processes;
    return 0;
}
/**
 * @brief operate is the method responsible for starting the processes that is satisfied by the FG state
 *          after changing the state of the FG 
 * 
 * @return void
 */
void p_operator(){
    for(auto &process : process_pool){     
        if(process.prun|| process._pid != 0)continue;   // if the process is running continue
        bool will_run = false;                          // flag to indicate if the process will run or not
        //check if the current state doesnt violate the configuration,otherwise terminate
        for(int config = 0; config < process.startup_configs.size();config++){  
            bool violate = false;           // flag to indicate if the current state violates the configuration
            // for each machine instance(FG) reference in the current configuration
            for(auto &mref: process.startup_configs[config].machine_instance_refs){  
                //Get the current state of the FG
                string fg_statue = sys_FG[mref.function_group].current_FGS->get_states(); 
                //Process wont run if fg_state is not process_config_states
                if (!count(mref.modes.begin(), mref.modes.end(), fg_statue)){
                    violate = true;         
                    break;
                }
            }
            if(!violate){           // if the current state doesnt violate the configuration
                process.current_config = &process.startup_configs[config];  // set the current configuration 
                will_run = true;    // set the flag to true to indicate that the process will run
                break;
            }
        }
        if(will_run)process.start();    // if the process will run start it
    }
}
/**
 * @brief terminate is the method responsible for terminating the processes that is not satisfied by the FG state 
 *            after changing the state of the FG 
 * 
 * @return void
 */
void p_terminator(){
    for(auto &process : process_pool){
        if(!process.prun)continue;      //if not running continue
        //check if the current state doesnt violate the configuration,otherwise terminate
        for(auto &mref:process.current_config->machine_instance_refs){
            //Get the current state of the FG
            string fg_statue = sys_FG[mref.function_group].current_FGS->get_states();
            //Terminate Process if fg_state is not process_config_states
            if (!count(mref.modes.begin(), mref.modes.end(), fg_statue)){
                process.terminate();
                break;
            }
        }
    }
}
/**
 * @brief change_state Change the state of a function group and terminate the process if it's 
 *          not in vaild state and start the process if it's in valid state
 * @param n_FG          The function group name
 * @param n_state       The new state
 *
 * @return void 
 */
void change_state(std::string n_FG, std::string n_state)
{
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"- EM: State Transition ("<<sys_FG[n_FG].current_FGS->get_FGname()<<"):  "+sys_FG[n_FG].current_FGS->get_states()+" --> "<<n_state<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
    sys_FG[n_FG].current_FGS.reset();
    FunctionGroupState::CtorToken token={n_FG,n_state};
    sys_FG[n_FG].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
    cout<<"\tTermination Log:"<<endl<<endl;
    p_terminator();
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"\tOperation Log:"<<endl<<endl;
    p_operator();
    cout<<"---------------------------------------------------------------"<<endl;
}
/**
 * @brief view_out Print the output files in the redirected folder
 *
 * @return void 
 */
void view_out(){
    namespace fs = std::filesystem;
    std::string root = std::string(get_current_dir_name())+"/processes/redirected/", ext = ".txt";
    if (fs::exists(root) && fs::is_directory(root))
    {
        for (auto const & entry : fs::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext){
                cout<<entry.path().filename().c_str()<<endl;
                system(("cd processes/redirected;cat "+ std::string(entry.path().filename().c_str())+";").c_str());
            }
        }
    }
    
}
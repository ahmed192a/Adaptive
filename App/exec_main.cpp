/**
 * @file exec_main.cpp
 * @brief EM
 * @version 0.1
 * @date 2022-06-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include "ara/exec/function_group.hpp"
#include "ara/exec/function_group_state.hpp"
#include "ara/Log_trace/Log.hpp"
#include <vector>
#include <map>
#include "ara/exec/parser/manifest_parser.hpp"
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
// #include "ara/SD_c/proxy.hpp"
using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

#define MC_MF   "/manifest_samples/machine_manifest.json"
#define EM_MF "/manifest_samples/execution_manifest.json"
#define SM_FIFO "processes/state_client_fifo"
#define MAX_BUF 1024

static map<string, GLOB> sys_FG;
std::vector<Process> process_pool;

void exec_init();
void change_state(std::string n_FG, std::string n_state);
void view_out();
void create_manifests();
void p_operate();
void p_terminate();

// Backup streambuffers of  cout
streambuf* stream_buffer_cout = cout.rdbuf();
streambuf* stream_buffer_cin = cin.rdbuf();

/**
 * @brief Main program of Excution Managiment program
 * @param argc
 * @param argv
 * 
 * @note   this is the Main program of Excution managiment which has the following functions:
 *  1. Parsing manifest files
 *  2. start state management
 *  3. get the state from SM
 *  4. switch state (start terminating sequence and starting sequence)
 * @return
 */
int main(int argc, char ** argv){
    //check if the folder exists
    if(std::filesystem::exists("processes/redirected")){
        // remove the folder and its content
        std::filesystem::remove_all("processes/redirected");
    }
    // create the redirected folder
    std::filesystem::create_directories("processes/redirected");    

    // file stream to write the output of EM to a EM.txt file
    fstream file;   
    // open the file
    file.open("processes/redirected/EM.txt", ios::out); 
    // redirect cout to the file
    cout.rdbuf(file.rdbuf());                        


    create_manifests();     // create the manifest files 

    cout << "\n-------------Program Started-------------"<<endl;
    exec_init();            // initialize the system and parse the manifest files

    mkfifo(SM_FIFO, 0666);  // create the fifo to communicate with State Management process
    std::string msg;        // message to send to SM
    msg.resize(MAX_BUF);    // resize the message to MAX_BUF bytes


   
   // change the state of MachineFG to Starting-up to start the state management process
    change_state("MachineFG" , "Pre-Starting-up"); 
    change_state("MachineFG" , "Starting-up");  
    int fd = open(SM_FIFO, O_RDONLY);   // open the fifo to read the state from SM


    /***********************************************************************************/
    // get FG name and new state from SM an change the state
    int n =read(fd,&msg[0],MAX_BUF);    // read the FG state from SM
    msg[n] = '\0';                      // set the end of string
    msg = msg.substr(0,n);              // remove the extra bytes from the string
    
    cout<<"Received From SM : "<<msg<<endl;

    // change the state of the FG to the state received from SM
    change_state(msg.substr(0, msg.find('/')), msg.substr(msg.find('/')+1, n-(msg.find('/')+1)) );  
    usleep(10000);                      // sleep for 10ms
    /***********************************************************************************/




    change_state("FG_1" , "off");       // change the state of FG_1 to off
    cout<<"FG_1 is off"<<endl;
    change_state("MachineFG" , "off");  // change the state of MachineFG to off
    close(fd);                          // close the fifo
    unlink(SM_FIFO);                    // delete the fifo
    cout<<"\n-------------Program Ended-------------"<<endl;

    cout.rdbuf(stream_buffer_cout);     // restore the cout stream buffer
    file.close();                       // close the file stream
    view_out();                         // view the output of all processe
    return 0;
}

void exec_init(){
    ManifestParser parser;              // create a parser to parse the manifest files

    //Parse Machine manifest
    MachineManifest MM = parser.parse_machine_manifest(std::string(get_current_dir_name())+ MC_MF, sys_FG);
    cout<<"1) Succeed parsing Machine manifest id = "+MM.manifest_id<<endl
        <<"FG's no.:"<<sys_FG.size()<<endl;

    //Parse Execution manifests
    ExecutionManifest EM = parser.parse_execution_manifest(std::string(get_current_dir_name())+ EM_MF);
    cout<<"2) Succeed parsing Execution manifest id = "+EM.manifest_id
        <<endl<<"processes no.:"<<EM.processes.size()<<endl;

    //Fetching processes from execution manifest parser
    process_pool = EM.processes;
}
/**
 * @brief operate is the method responsible for starting the processes that is satisfied by the FG state
 *          after changing the state of the FG 
 * 
 * @return void
 */
void p_operator(){
    for(auto &process : process_pool){       // for each process in the process pool
        // if the process is running continue
        if(process.prun|| process._pid != 0)continue;  
        //print process name
        // cout<<"Process "<<process.name<<" is checked "<< process.prun<<endl;     
        bool will_run = false;              // flag to indicate if the process will run or not

        //check if the current state doesnt violate the configuration,otherwise terminate
        for(int config = 0; config < process.startup_configs.size();config++){  
            bool violate = false;           // flag to indicate if the current state violates the configuration
            // for each machine instance(FG) reference in the current configuration
            for(auto &mref: process.startup_configs[config].machine_instance_refs){  
                // get the current state of the FG
                string key = sys_FG[mref.function_group].current_FGS->get_states(); 
                // if the current state of the FG doesnt match the mode
                if(!std::count(mref.modes.begin(), mref.modes.end(), key)){ 
                    // set the flag to true to indicate that the current state violates the configuration
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
         //if not running continue
        if(!process.prun)continue;
        //check if the current state doesnt violate the configuration,otherwise terminate
        for(auto &mref:process.current_config->machine_instance_refs){
            string key = sys_FG[mref.function_group].current_FGS->get_states();
            if(!(std::count(mref.modes.begin(), mref.modes.end(), key))){
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
    sys_FG[n_FG].current_FGS.reset();
    FunctionGroupState::CtorToken token={n_FG,n_state};
    sys_FG[n_FG].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
    cout<<"\nEM: check transition : "<<sys_FG[n_FG].current_FGS->get_FGname()<<" -> state : "<<sys_FG[n_FG].current_FGS->get_states()<<endl<<endl;
    p_terminator();
    p_operator();
}

/*********************************************************************************************
 *                         This section is used for testing on Github                        *
 *********************************************************************************************/
/**
 * @brief view_out Print the output files in the redirected folder
 *
 * @return void 
 */
void view_out(){
    namespace fs = std::filesystem;
    //system("cd processes/redirected");
    std::string root = std::string(get_current_dir_name())+"/processes/redirected/", ext = ".txt";
    if (fs::exists(root) && fs::is_directory(root))
    {
        for (auto const & entry : fs::recursive_directory_iterator(root))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == ext){
                cout<<entry.path().filename().c_str()<<endl;
                system(("cd processes/redirected;cat "+ std::string(entry.path().filename().c_str())+";").c_str());
            }
                //paths.emplace_back(entry.path().filename());
        }
    }
    
}
/**
 * @brief create_manifests Create the manifest files for the program
 *
 * @return void 
 */
void create_manifests()
{
    // detete folder and its content if it exists
    system("rm -rf manifest_samples");
    // rmdir("manifest_samples");
    const int dir_err = mkdir("manifest_samples", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    fstream file;
    file.open("manifest_samples/machine_manifest.json",ios::app);
    file << "{\n"
            "    \"Machine_manifest\": {\n"
            "        \"Machine_manifest_id\": \"mach_id\",\n"
            "        \"Mode_declaration_group\": [\n"
            "            {\n"
            "                \"Function_group_name\": \"MachineFG\",\n"
            "                \"Mode_declarations\": [\n"
            "                    {\n"
            "                      \"Mode\": \"off\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"Pre-Starting-up\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"Starting-up\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"Running\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"Shuttingdown\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"restart\"\n"
            "                    }\n"
            "                ]\n"
            "            },\n"
            "            {\n"
            "                \"Function_group_name\": \"FG_1\",\n"
            "                \"Mode_declarations\": [\n"
            "                    {\n"
            "                      \"Mode\": \"off\"\n"
            "                    },\n"
            "                    {\n"
            "                      \"Mode\": \"on\"\n"
            "                    }\n"
            "                ]\n"
            "            },\n"
            "            {\n"
            "              \"Function_group_name\": \"FG_2\",\n"
            "              \"Mode_declarations\": [\n"
            "                  {\n"
            "                    \"Mode\": \"off\"\n"
            "                  },\n"
            "                  {\n"
            "                    \"Mode\": \"on\"\n"
            "                  }\n"
            "              ]\n"
            "          }\n"
            "            \n"
            "        ]\n"
            "    }\n"
            "}";
    file.close();
    file.open("manifest_samples/execution_manifest.json", ios::app);
    file << "{\n"
            "    \"Execution_manifest\": {\n"
            "        \"Execution_manifest_id\": \"exec_id\",\n"
            "        \"Process\": [\n"
            "            {\n"
            "                \"Process_name\": \"process1\",\n"
            "                \"Mode_dependent_startup_configs\": [\n"
            "                    {\n"
            "                        \"Startup_options\": [\n"
            "                            {\n"
            "                                \"Option_kind\": \"commandLineShortForm\",\n"
            "                                \"Option_name\": \"EM_test_process\",\n"
            "                                \"Option_arg\": \"inputfile_1\"\n"
            "                            }\n"
            "                        ],\n"
            "                        \"FunctionGroupDependencies\": [\n"
            "                            {\n"
            "                                \"Function_group\": \"FG_1\",\n"
            "                                \"Modes\": [ \n"
            "                                           {\"Mode\" : \"on\"} \n"
            "                                           ]\n"
            "                            }\n"
            "                        ]\n"
            "                    }\n"
            "                ]\n"
            "                \n"
            "            },\n"
            "            {\n"
            "                \"Process_name\": \"SD\",\n"
            "                \"Mode_dependent_startup_configs\": [\n"
            "                    {\n"
            "                        \"Startup_options\": [\n"
            "                            {\n"
            "                                \"Option_kind\": \"commandLineShortForm\",\n"
            "                                \"Option_name\": \"filename\",\n"
            "                                \"Option_arg\": \"inputfile_1\"\n"
            "                            }\n"
            "                        ],\n"
            "                        \"FunctionGroupDependencies\": [\n"
            "                            {\n"  //
            "                                \"Function_group\": \"MachineFG\",\n"
            "                                \"Modes\": [ \n"
            "                                               {\"Mode\" : \"Pre-Starting-up\"}, \n"
            "                                               {\"Mode\" : \"Starting-up\"}, \n"
            "                                               {\"Mode\" : \"Running\"} \n"
            "                                           ]\n"
            "                            }\n"
            "                        ]\n"
            "                    }\n"
            "                ]\n"
            "                \n"
            "            },\n"
            "            {\n"
            "                \"Process_name\": \"sm_process\",\n"
            "                \"Mode_dependent_startup_configs\": [\n"
            "                    {\n"
            "                        \"Startup_options\": [\n"
            "                            {\n"
            "                                \"Option_kind\": \"commandLineShortForm\",\n"
            "                                \"Option_name\": \"filename\",\n"
            "                                \"Option_arg\": \"inputfile_1\"\n"
            "                            }\n"
            "                        ],\n"
            "                        \"FunctionGroupDependencies\": [\n"
            "                            {\n"  //
            "                                \"Function_group\": \"MachineFG\",\n"
            "                                \"Modes\": [ \n"
            "                                           {\"Mode\" : \"Starting-up\"}, \n"
            "                                           {\"Mode\" : \"Running\"} \n"
            "                                           ]\n"
            "                            }\n"
            "                        ]\n"
            "                    }\n"
            "                ]\n"
            "                \n"
            "            }\n"
            "        ]\n"
            "    }\n"
            "}";
    file.close();
}
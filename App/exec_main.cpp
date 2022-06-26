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

#define MC_MF "/manifest_samples/machine_manifest.json"
#define EM_MF "/manifest_samples/execution_manifest.json"
#define SM_FIFO "processes/state_client_fifo"

#define MAX_BUF 1024


std::vector<Process> process_pool;
static map<string, GLOB> sys_FG;

void exec_init_map();
void terminate_p(GLOB &G);
void start_p(GLOB &G);
void change_state(std::string n_FG, std::string n_state);
void view_out();
void create_man();
void operate();
void terminate();

// Backup streambuffers of  cout
streambuf* stream_buffer_cout = cout.rdbuf();
streambuf* stream_buffer_cin = cin.rdbuf();

int main(int, char **)
{
    std::filesystem::create_directories("processes/redirected");
    // freopen("processes/redirected/EM.txt", "w", stdout);

    fstream file;
    file.open("processes/redirected/EM.txt", ios::out);
    cout.rdbuf(file.rdbuf());
    // 1. parsing the Mahcine manifest
    // 2. parsing the Execution manifest
    // 3. start state management
    // 4. get the state from SM
    // 5. switch state (start terminating sequence and starting sequence)

    // Log lg;
    // lg.Insert("\n\n----------------------------program started-------------\n", "EM");
    create_man();
    cout << "\n\n----------------------------program started-------------\n";


    exec_init_map();


    mkfifo(SM_FIFO, 0666);
    std::string msg;
    msg.resize(MAX_BUF);


   // get FG name and new state from SM an change the state
    change_state("MachineFG" , "Starting-up");
    int fd = open(SM_FIFO, O_RDONLY);
    int n =read(fd,&msg[0],MAX_BUF);
    msg[n] = '\0';
    msg = msg.substr(0,n);
    cout<<"Received From SM : "<<msg<<endl;
    cout<<msg.substr(0, msg.find('/'))<<"  "<< msg.substr(msg.find('/')+1, n)<<"_1\n";

    change_state(msg.substr(0, msg.find('/')), msg.substr(msg.find('/')+1, n-(msg.find('/')+1)) );
    usleep(10000);
    change_state("FG_1" , "off");
    change_state("MachineFG" , "off");
    close(fd);
    unlink(SM_FIFO);

    cout.rdbuf(stream_buffer_cout);
    file.close();
    view_out();
    return 0;
}

void exec_init_map(){
    //parse machine manifest
    ManifestParser parser;
 
    MachineManifest MM = parser.pares_test(std::string(get_current_dir_name())+ MC_MF, sys_FG);
    cout<<"1: succeed parsing Machine manifest id = "+MM.manifest_id<<endl;
    cout<<"2: we have "<<sys_FG.size()<<" function groups\n";
    
    //parse execution manifests
    ExecutionManifest EM = parser.parse_execution_manifest(std::string(get_current_dir_name())+ EM_MF);
    cout<<"3: succeed parsing Execution manifest id = "+EM.manifest_id<<endl;
    cout<<"4: num process : "<<EM.processes.size()<<endl;

    //fetching processes from execution manifest parser
    process_pool = EM.processes;
}
void p_operator(){
    for(auto process : process_pool){
         //if running continue
        if(process.prun)continue;
        bool will_run = false;
        //check if the current state doesnt violate the configuration,otherwise terminate
        for(int config = 0; config < process.startup_configs.size();config++){
            bool violate = false;
            for(auto mref: process.startup_configs[config].machine_instance_refs){
                if(sys_FG[mref.function_group].current_FGS->get_states()!=mref.mode){
                    violate = true;
                    break;
                }
            }
            if(!violate){
                process.current_config = &process.startup_configs[config];
                will_run = true;
                break;
            }
        }
        if(will_run)process.start();
    }
}
void p_terminator(){
    for(auto process : process_pool){
         //if not running continue
        if(!process.prun)continue;
        //check if the current state doesnt violate the configuration,otherwise terminate
        for(auto mref:process.current_config->machine_instance_refs){
            string key = sys_FG[mref.function_group].current_FGS->get_states();
            if(!(std::count(mref.modes.begin(), mref.modes.end(), key))){
                process.terminate();
                break;
            }
        }
    }
}
void change_state(std::string n_FG, std::string n_state)
{
    sys_FG[n_FG].current_FGS.reset();
    FunctionGroupState::CtorToken token={n_FG,n_state};
    sys_FG[n_FG].current_FGS = std::make_shared<FunctionGroupState>(std::move(token));
    cout<<"\nEM: check transition : "<<sys_FG[n_FG].current_FGS->get_FGname()<<" -> state : "<<sys_FG[n_FG].current_FGS->get_states()<<endl<<endl;
    
    p_terminator();
    p_operator();
}
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
void create_man()
{
    rmdir("manifest_samples");
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
            "                                \"Mode\": \"on\"\n"
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
            "                            {\n"
            "                                \"Function_group\": \"MachineFG\",\n"
            "                                \"Mode\": \"Starting-up\"\n"
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
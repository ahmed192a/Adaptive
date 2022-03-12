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
#include <filesystem>  // to get all files in certain dir


#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <utility>
#include <sys/wait.h>
// #include "ara/SD_c/proxy.hpp"
using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

#define     MC_MF   "manifest_samples/machine_manifest.json"
#define     EM_MF   "manifest_samples/execution_manifest.json"



struct GLOB{
    FunctionGroup *c_FG;
    string FG_name;
    vector<Process> processes;
    FunctionGroupState *current_FGS;
};

void exec_init_map(map<string, GLOB> & system_FG);
void terminate_p(GLOB &G);
void start_p(GLOB &G);
void create_man();



int main(int, char**) {
    // 1. parsing the Mahcine manifest
    // 2. parsing the Execution manifest
    // 3. start state management
    // 4. get the state from SM
    // 5. switch state (start terminating sequence and starting sequence)
    

    //Log lg;
    //lg.Insert("\n\n----------------------------program started-------------\n", "EM");
    create_man();
    cout<<"\n\n----------------------------program started-------------\n";
    vector<GLOB> gg;
    map<string, GLOB> gs;
    //exec_init(gg);
    exec_init_map(gs);

    for(map<string, GLOB>::iterator it = gs.begin(); it!= gs.end(); it++ ){
        //lg.Insert("EM: Function group name : " + it->first+ " with number of processes = "+ to_string(it->second.processes.size()) + "\n", "EM");
        cout<<"EM: Function group name : "<<it->first<< " with number of processes = "<<it->second.processes.size()<<endl;
    }

    delete gs["FG_1"].current_FGS;
    gs["FG_1"].current_FGS = new FunctionGroupState("FG_1/on");
    cout<<"\nEM: check transition : "<<gs["FG_1"].current_FGS->Function_group_name<<" state : "<<gs["FG_1"].current_FGS->state<<endl<<endl;

    terminate_p(gs["FG_1"]);
    start_p(gs["FG_1"]);
    usleep(10000);
    delete gs["FG_1"].current_FGS;
    gs["FG_1"].current_FGS = new FunctionGroupState("FG_1/off");
    cout<<"\nEM: check transition : "<<gs["FG_1"].current_FGS->Function_group_name<<" state : "<<gs["FG_1"].current_FGS->state<<endl<<endl;
    terminate_p(gs["FG_1"]);
    start_p(gs["FG_1"]);



}

void exec_init_map(map<string, GLOB> & system_FG){
    // parse machine manifest
        ManifestParser parser;
        MachineManifest MM = parser.parse_machine_manifest(MC_MF);
        cout<<"succeed parsing Machine manifest id = "+MM.manifest_id<<endl;
        
        // create Functiongroup object for each one and create FunctionGroupState with its initial state
        for(auto i = 0 ; i< MM.mode_declaration_groups.size(); i++){
            GLOB gg;
            string meta = MM.mode_declaration_groups[i].function_group_name;
            for(auto j = 0; j< MM.mode_declaration_groups[i].mode_declarations.size(); j++){
                meta += "/"+MM.mode_declaration_groups[i].mode_declarations[j].mode;
            }
            gg.c_FG = new FunctionGroup(meta+"");
            gg.current_FGS = new FunctionGroupState(meta+"/"+MM.mode_declaration_groups[i].mode_declarations[0].mode);
            gg.FG_name = MM.mode_declaration_groups[i].function_group_name;
            //system_FG.push_back(gg);
            system_FG[gg.FG_name] = gg;
        }
        cout<<"we have "<<system_FG.size()<<" function groups\n";
        
    
    // parse execution manifests
        ExecutionManifest EM = parser.parse_execution_manifest(EM_MF);
        cout<<"succeed parsing Execution manifest id = "+EM.manifest_id<<endl;

        // push the process in vector 
        for(auto i = 0; i<EM.processes.size(); i++){
            for (auto j = 0; j < EM.processes[i].startup_configs.size(); j++)
            {
                for (auto h = 0; h < EM.processes[i].startup_configs[j].machine_instance_refs.size(); h++)
                {
                    system_FG[EM.processes[i].startup_configs[j].machine_instance_refs[h].function_group].processes.push_back(EM.processes[i]);
                }
            }
        }  
}


void terminate_p(GLOB &G){
    cout<<"EM: terminating switching\n";
  
    for (vector<Process>::iterator i = G.processes.begin(); i != G.processes.end(); i++)
    {
       if((*i).prun == true){
           for (vector<ara::exec::parser::Process::StartupConfig::MachineInstanceRef>::iterator fg_ref = (*(*i).current_config).machine_instance_refs.begin(); fg_ref != (*(*i).current_config).machine_instance_refs.end(); fg_ref++)
           {
               if((*fg_ref).function_group == G.FG_name){
                   if((*fg_ref).mode == G.current_FGS->state) continue;
                   else {
                       (*i).terminate();
                       (*i).prun  = false;
                       (*i).current_config=nullptr;
                       break;
                   }
               }
           }
       }
    }
}
void start_p(GLOB &G){
    for (vector<Process>::iterator i = G.processes.begin(); i != G.processes.end(); i++)
    {
       if((*i).current_config == nullptr || (*i).prun == false){
           for (vector<ara::exec::parser::Process::StartupConfig>::iterator stc = (*i).startup_configs.begin(); stc != (*i).startup_configs.end(); stc++)
           {
                for (vector<ara::exec::parser::Process::StartupConfig::MachineInstanceRef>::iterator fg_ref = (*stc).machine_instance_refs.begin(); fg_ref != (*stc).machine_instance_refs.end(); fg_ref++)
                {
                    if((*fg_ref).function_group == G.FG_name){
                        if((*fg_ref).mode == G.current_FGS->state)
                        { 
                            (*i).start();
                            (*i).prun = true;
                            (*i).current_config=&((*i).startup_configs[stc -(*i).startup_configs.begin()]);
                            break;
                        }
                    }
                }
           }
       }
    }
}


void create_man(){
    const int dir_err = mkdir("manifest_samples", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    fstream file;
    file.open("manifest_samples/machine_manifest.json", ios::app);
    file<< "{\n"
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
file<<"{\n"
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
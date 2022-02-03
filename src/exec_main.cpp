#include <iostream>
#include "function_group.h"
#include "function_group_state.h"
#include "Log_trace/Log.h"
#include <vector>
#include <map>
#include "manifest_parser.h"
#include <string>

#include <dirent.h>
#include <filesystem>  // to get all files in certain dir


#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <utility>
#include <sys/wait.h>

using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

#define     MC_MF   "../manifest_samples/machine_manifest.json"
#define     EM_MF   "../manifest_samples/execution_manifest.json"



struct GLOB{
    FunctionGroup *c_FG;
    string FG_name;
    vector<Process> processes;
    FunctionGroupState *current_FGS;
};

void exec_init_map(map<string, GLOB> & system_FG);
void terminate_p(GLOB &G);
void start_p(GLOB &G);




int main(int, char**) {
    // 1. parsing the Mahcine manifest
    // 2. parsing the Execution manifest
    // 3. start state management
    // 4. get the state from SM
    // 5. switch state (start terminating sequence and starting sequence)
    
    //Log lg;
    //lg.Insert("\n\n----------------------------program started-------------\n", "EM");
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
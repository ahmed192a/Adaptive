#include <iostream>
#include "function_group.h"
#include "function_group_state.h"
#include <vector>
#include <map>
#include <utility>
#include "manifest_parser.h"
using namespace ara::exec;
using namespace ara::exec::parser;
using namespace std;

#define     FG_IDS (vector<string>){"mach_id/FG_1", "mach_id/FG_2"}

enum ProcessState{
    idle,
    starting,
    running,
    terminating,
    terminated
};


//map<string, pair<FunctionGroupState, vector<Process>>> system_FG;

struct GLOB{
    FunctionGroup *c_FG;
    string FG_name;
    vector<Process> processes;
    FunctionGroupState *current_FGS;
};



void exec_init(vector<GLOB> & system_FG){
    // parse machine manifest
        ManifestParser parser;
        MachineManifest MM = parser.parse_machine_manifest("../src/ara/exec/manifest_samples/machine_manifest.json");
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
            system_FG.push_back(gg);
        }
        cout<<"we have "<<system_FG.size()<<" function groups\n";
        
    
    // parse execution manifests
        ExecutionManifest EM = parser.parse_execution_manifest("../src/ara/exec/manifest_samples/execution_manifest.json");
        cout<<"succeed parsing Execution manifest id = "+EM.manifest_id<<endl;

        // push the process in vector 
        for(auto i = 0; i<EM.processes.size(); i++){
            
        }
        EM.processes[0].startup_configs[0].machine_instance_refs[0].function_group;
}








int main(int, char**) {
    cout<<"\n\n----------------------------program started-------------\n";
    //system("ls");
    vector<GLOB> gg;
    exec_init(gg);
    std::cout << "\n\nHello, world! we created "<<gg.size()<<" function groups xD \n\n";
    vector<FunctionGroup > FG;
    vector<FunctionGroupState> FGS;

    // create function groups
    for(int i = 0; i< FG_IDS.size();i++){
        FG.push_back( FunctionGroup(FG_IDS[i]+""));
        cout<<FG_IDS[i]+"\t"<<FG[i].Function_group_name<<endl;
    } 

    // create function groups state
    for(int i = 0; i< FG_IDS.size();i++){
        FGS.push_back(FunctionGroupState(FG_IDS[i]+"/off"));
        cout<<FG_IDS[i]+"\t"<<FGS[i].Function_group_name<< "\t" << FGS[i].state<<endl;
    }





    // get processes
    // 2D array col index
    // 

    // 






















    

     

    //  
    //  FunctionGroup S("DLKDNKL");
    //  map<fucntion_group, vector<process>> n;
    //  function_group_state s;
    //  vector<process> tmp = n[s.function_group];
    //  for(i in tmp) if process.state == s.state -> run  else terminate

    //vector<fucntion_group>v;
    //vector<process>fg_1;
    //function_group_state x; == !=

    // 1. parsing the Mahcine manifest
    // 2. parsing the Execution manifest
    // 3. start state management
    // 4. 
}

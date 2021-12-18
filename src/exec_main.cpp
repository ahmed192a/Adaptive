#include <iostream>
#include "function_group.h"
#include "function_group_state.h"
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

#define     FG_IDS (vector<string>){"mach_id/FG_1", "mach_id/FG_2"}
#define     MC_MF   "../manifest_samples/machine_manifest.json"
#define     EM_MF   "../manifest_samples/execution_manifest.json"
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

void exec_init(vector<GLOB> & system_FG);
void exec_init_map(map<string, GLOB> & system_FG);
void terminate_p(GLOB G){
    for (vector<Process>::iterator i = G.processes.begin(); i != G.processes.end(); i++)
    {
       if((*i).current_config != nullptr){
           for (vector<ara::exec::parser::Process::StartupConfig::MachineInstanceRef>::iterator fg_ref = (*(*i).current_config).machine_instance_refs.begin(); fg_ref != (*(*i).current_config).machine_instance_refs.end(); fg_ref++)
           {
               if((*fg_ref).function_group == G.FG_name){
                   if((*fg_ref).mode == G.current_FGS->state) break;
                   else {
                       (*i).terminate();
                       (*i).current_config=nullptr;
                   }
               }
           }
       }
    }
}
void start_p(GLOB G){
    for (vector<Process>::iterator i = G.processes.begin(); i != G.processes.end(); i++)
    {
       if((*i).current_config == nullptr){
           for (vector<ara::exec::parser::Process::StartupConfig>::iterator stc = (*i).startup_configs.begin(); stc != (*i).startup_configs.end(); stc++)
           {
                for (vector<ara::exec::parser::Process::StartupConfig::MachineInstanceRef>::iterator fg_ref = (*stc).machine_instance_refs.begin(); fg_ref != (*stc).machine_instance_refs.end(); fg_ref++)
                {
                    if((*fg_ref).function_group == G.FG_name){
                        if((*fg_ref).mode == G.current_FGS->state)
                        { 
                            (*i).start();
                            (*i).current_config=&(*stc);
                            break;
                        }
                    }
                }
           }
       }
    }
}



int main(int, char**) {
    cout<<"\n\n----------------------------program started-------------\n";
    vector<GLOB> gg;
    map<string, GLOB> gs;
    //exec_init(gg);
    exec_init_map(gs);

    for(map<string, GLOB>::iterator it = gs.begin(); it!= gs.end(); it++ ){
        cout<<"EM: Function group name : "<<it->first<< " with number of processes = "<<it->second.processes.size()<<endl;
    }

    delete gs["FG_1"].current_FGS;
    gs["FG_1"].current_FGS = new FunctionGroupState("FG_1/on");
    cout<<"\nEM: check transition : "<<gs["FG_1"].current_FGS->Function_group_name<<" state : "<<gs["FG_1"].current_FGS->state<<endl<<endl;

    start_p(gs["FG_1"]);


    // std::cout << "\n\nHello, world! we created "<<gg.size()<<" function groups and  xD \n\n";
    // for (auto i = 0; i < gg.size(); i++)
    // {
    //     cout<< gg[i].FG_name<<" with number of processes = "<< gg[i].processes.size()<<endl;
    // }
    // gg[1].processes[0].start();

    












    // code for getting the names of the files in certain dir (manifests)
    /*
    cout<<"files in this DIR : \n";
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir( "../manifest_samples/");
    if (dp != nullptr) {
        while ((entry = readdir(dp))){
            if(entry->d_name[0]!='.'){
                printf ("%s\n", entry->d_name);
            }
        }
    }
    closedir(dp);
    */


    //run_process();



















    

     

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


void exec_init(vector<GLOB> & system_FG){
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
            system_FG.push_back(gg);
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
                    for (auto n = 0; n < system_FG.size(); n++)
                    {
                        if(system_FG[n].FG_name == EM.processes[i].startup_configs[j].machine_instance_refs[h].function_group){
                            system_FG[n].processes.push_back(EM.processes[i]);
                            break;
                        }
                    }
                }
            }
        }
}


void run_process(){
   int pid, status;
   // first we fork the process
   if (pid = fork()) {
       // pid != 0: this is the parent process (i.e. our process)
       waitpid(pid, &status, 0); // wait for the child to exit
   } else {
       /* pid == 0: this is the child process. now let's load the
          "ls" program into this process and run it */

        if(chdir("processes") == 0){
            cout<<"dir changed\n";
        cout<<get_current_dir_name()<<endl;
       const char executable[] = "./process1";

       // load it. there are more exec__ functions, try 'man 3 exec'
       // execl takes the arguments as parameters. execv takes them as an array
       // this is execl though, so:
       //      exec         argv[0]  argv[1] end
       execl(executable,executable,  NULL);

        }
        cout<<" cd faild\n";
        std::abort();
        return;


   }
   cout<<"\nstat : "<<status<<endl;
   if(status/256 == 0){
       cout<< "\nyaaa\n";
   }
   else if(status/256 == 1){
       cout<<"\nnooo\n";
   }
   //return status; // this is the parent process again.
    

    //while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes 
}

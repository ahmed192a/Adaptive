#include <iostream>
#include <memory>
#include <unistd.h>
#include <signal.h>
#include <csignal>
#include "ara/exec/state_client.hpp"
#include "ara/exec/function_group_state.hpp"
#include "ara/exec/execution_client.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/sm/triggerin/triggerin_skeleton.hpp"
#include "ara/sm/triggerin/triggerin_types.hpp"

///// Defines
#define NUM_THREADS             2       // number of threads
#define SERVER_PORT             5375    // port for the server socket OF State Manament used with UDP and TCP sockets
#define SD_PORT                 1690    // port of Service Discovery
#define T_IN_UCM_INSTANCE_ID    1       // instance id Trigger in UCM service (1)
#define T_IN_OTA_INSTANCE_ID    2       // instance id Trigger in UCM service (2)
#define MAX_QUEUE_CLIENTS       3       // max number of clients in the queue for STREAM server socket

///// Namespaces
using namespace std;                    
using namespace ara::exec;
using namespace ara::sm::triggerin;

///// Functions declarations
void  handle_sigterm(int sig);  
void *pthread0(void *v_var);
void *pthread1(void *v_var);

////// global variables
int sigval = 0;        // signal value
bool newState = false; // used for FSM of SM
//// create enum for different states of the FSM
enum class State {
    STATE_UNKNOWN,
    STATE_INITIAL,
    STATE_RUNNING,
    STATE_UPDATE,
    STATE_STOPPED,
    STATE_ERROR
};

State SM_State = State::STATE_UNKNOWN;

/**    UCM Trigger In Skeleton    **/
// instance id of Trigger in UCM service (1)
ara::com::InstanceIdentifier instance(T_IN_UCM_INSTANCE_ID);    
// skeleton handle for constructor Trigger in UCM service
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle triggerin_handle{SERVER_PORT, SD_PORT};  
// Create shared pointer object of Trigger in UCM service skeleton
std::shared_ptr<ara::sm::triggerin::skeleton::Trigger_In_UCM_Skeleton> UCM_triggerin_skeleton_ptr = std::make_shared<ara::sm::triggerin::skeleton::Trigger_In_UCM_Skeleton>(instance, triggerin_handle); 

/**     OTA Trigger In Skeleton    **/
// instance id of Trigger in OTA service (2)
ara::com::InstanceIdentifier instance_ota(T_IN_OTA_INSTANCE_ID);
// skeleton handle for constructor Trigger in OTA service
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle triggerin_handle_ota{SERVER_PORT, SD_PORT};
// Create shared pointer object of Trigger in OTA service skeleton
std::shared_ptr<ara::sm::triggerin::skeleton::Trigger_In_OTA_Skeleton> OTA_triggerin_skeleton_ptr = std::make_shared<ara::sm::triggerin::skeleton::Trigger_In_OTA_Skeleton>(instance_ota, triggerin_handle_ota);


CServer server_main_socket_DG(SOCK_DGRAM);  // socket for events (UDP)
CServer server_main_socket(SOCK_STREAM);    // socket for methods handle (TCP)
ExecutionClient client;
std::shared_ptr<ara::exec::StateClient> state_client_ptr;


/**
 * @brief Main code for State management
 * @return 0 if successful
 */
int main(){
    // Print the current directory will be used later to load the configuration files
    cout<<endl<<"[SM]"<<std::string(get_current_dir_name())<<endl;
    
    signal(SIGTERM, handle_sigterm);                        // register signal handler
    client.ReportExecutionState(ExecutionState::kRunning);  // report execution state to the execution server

    state_client_ptr = std::make_shared<ara::exec::StateClient>();

    

    cout<<"\t\t[SM]creating execution client "<<endl;


    server_main_socket_DG.OpenSocket(SERVER_PORT);          // open socket for events (UDP)
    server_main_socket_DG.BindServer();                     // bind socket for events (UDP)

    pthread_t threads[NUM_THREADS];                         // create threads
    int th1_id, th2_id;                                     // thread ids
    int counter_thead = 0;                                  // thread counter

    // create thread 0
    th1_id = pthread_create(&threads[0], NULL, pthread0, (void *)&counter_thead);  
    if (th1_id){
        // print error if thread can't be created
        cout << "[UCM SERVER] ERROR can't create thread " << th1_id << endl;    
        exit(-1);
    }


    pthread_exit(NULL);                                     // exit thread

    return 0;
}

/////// Functions definitions
/**
 * @brief Signal handler for SIGTERM
 * @param sig signal number
 * @return void
 */
void handle_sigterm(int sig){
    sigval = 1;                                 // set signal value will be used as flag
    cout<<"{SM} terminating"<<endl;            
    client.ReportExecutionState(ExecutionState::kTerminating);  // report execution state to the execution server         
    // UCM_triggerin_skeleton_ptr->StopOfferService();     // stop offering service
    server_main_socket.CloseSocket();                   // close server socket
    server_main_socket_DG.CloseSocket();                // close server socket
    exit(0);                                            // exit program
}

/**
 * @brief thread0 used to handle methods and FSM of SM
 * 
 * @param v_var     pointer to thread counter
 * @return void*    
 */
void *pthread0(void *v_var){
    

    cout<<"{SM} pthread0"<<endl;
    cout<<"[SM SERVER] OPEN SOCKET ON "<<endl;
    server_main_socket.OpenSocket(SERVER_PORT);         // open socket for methods handle (TCP)
    server_main_socket.BindServer();                    // bind socket for methods handle (TCP)
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS); // listen to server socket (TCP)

    cout<<"[SM] Offering service to the SD"<<endl;      
    UCM_triggerin_skeleton_ptr->OfferService();         // offering service to the SD
    OTA_triggerin_skeleton_ptr->OfferService();         // offering service to the SD
    cout<<"[SM] Offered service to the SD"<<endl;  


    // Create Function group state for MachineFG to Running state
    FunctionGroupState::CtorToken token;
    token.fg_name = "MachineFG";
    token.c_state = "Running";
    FunctionGroupState FGS(std::move(token));
    std::cout<<"[SM] FGS created "<<endl;
    std::future<boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc>> _future = state_client_ptr->SetState(FGS);
    boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc> var = _future.get();
    std::cout<<"[SM] state changed"<<endl;
    cout<<"\t\t[SM] result "<<var.index()<<endl;
    SM_State = State::STATE_INITIAL;



    while(1){
        Socket Sclient = server_main_socket.AcceptServer(); // accept client socket (TCP)
        cout << "\t[SM]  accepted" << endl; 

        std::vector<uint8_t> msg;                           // Payload message from client              
        uint32_t msg_size;                                  // Size of message 

        // Receive a payload from client containing the method name and parameters
        Sclient.Receive((void *)&msg_size, sizeof(msg_size));   // recieve message size 
        msg.resize(msg_size);           //  resize the vector to allocate size of the coming message
        Sclient.Receive((void *)&msg[0], msg_size);             //  recieve the message

        cout << "\t[SM]  received" << endl;

        // deserialize message to SOMEIP_MESSAGE::Message object
        ara::com::SOMEIP_MESSAGE::Message someip_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg); 

        // check if message is a method call or field methods (SET, GET)
        if(someip_msg.MessageId().serivce_id == UCM_triggerin_skeleton_ptr->GetServiceId()){
            if (someip_msg.check_Methode_ID() == true){ // No methods in SM Services
                cout << "This is method request from UCM_triggerin " << endl;
            }else{
                
                UCM_triggerin_skeleton_ptr->field_method_dispatch(someip_msg, Sclient);
            }
        }else if(someip_msg.MessageId().serivce_id == OTA_triggerin_skeleton_ptr->GetServiceId()){
            if (someip_msg.check_Methode_ID() == true){ // No methods in SM Services
                cout << "This is method request from OTA_triggerin " << endl;
            }else{
                OTA_triggerin_skeleton_ptr->field_method_dispatch(someip_msg, Sclient);
            }
        }else{
            cout << "Unknown service id" << endl;
            ara::com::proxy_skeleton::skeleton::ServiceSkeleton::NoServiceHandler(someip_msg, Sclient);

        }

        
        cout<< "finish request \n";


        /*******************************          FSM           **************************************/
        if(SM_State == State::STATE_INITIAL && UCM_triggerin_skeleton_ptr->trigger.get_event() == ara::sm::triggerin::UCM_State::UCM_STATE_INITIALIZED)
        {
            FunctionGroupState::CtorToken token;
            token.fg_name = "FG_1";
            token.c_state = "on";
            FunctionGroupState FGS(std::move(token));
            std::cout<<"[SM] FGS created "<<endl;
            std::future<boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc>> _future = state_client_ptr->SetState(FGS);
            boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc> var = _future.get();
            std::cout<<"[SM] state changed"<<endl;
            SM_State = State::STATE_RUNNING;
        }
        else if (SM_State == State::STATE_RUNNING && OTA_triggerin_skeleton_ptr->trigger.get_event() == ara::sm::triggerin::OTA_State::OTA_STATE_INITIALIZED){
            // used for OTA
            cout<<"[SM] OTA_STATE_INITIALIZED"<<endl;
            // comment the next code to use the full system bassant
            SM_State = State::STATE_UPDATE;
            FunctionGroupState::CtorToken token;
            token.fg_name = "MachineFG";
            token.c_state = "off";
            FunctionGroupState FGS(std::move(token));
            std::cout<<"[SM] FGS created "<<endl;
            std::future<boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc>> _future = state_client_ptr->SetState(FGS);
            boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc> var = _future.get();
            std::cout<<"[SM] state changed"<<endl;
        }

        /*******************************        END OF FSM      **************************************/

    }
    UCM_triggerin_skeleton_ptr->StopOfferService();    // stop offering service
    server_main_socket.CloseSocket();           // close server socket
}

/*
int main0()
{
    cout<<endl<<"[SM]"<<std::string(get_current_dir_name())<<endl;
    signal(SIGTERM, handle_sigterm);
    // struct sigaction sa;
    // sa.sa_handler = &handle_sigterm;    // handle SIGTERM
    // sa.sa_flags= SA_RESTART;            // restart system calls
    // sigaction(SIGTERM, &sa, NULL);      // register signal handler
    
    cout<<"\n\n\t\t[SM]you are in the second file"<<endl;
    cout<<"\t\t[SM]SM for testing"<<endl;
    cout<<"\t\t[SM]creating execution client "<<endl;
    ExecutionClient client;
    client.ReportExecutionState(ExecutionState::kRunning);

    StateClient sm_client;


    FunctionGroupState::CtorToken token;
    token.fg_name = "FG_1";
    token.c_state = "on";
    FunctionGroupState FGS(std::move(token));
    std::cout<<"[SM] FGS created "<<endl;
    std::future<boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc>> _future = sm_client.SetState(FGS);
    boost::variant2::variant<boost::variant2::monostate,ara::exec::ExecErrc> var = _future.get();
    std::cout<<"[SM] state changed"<<endl;
    cout<<"\t\t[SM] result "<<var.index()<<endl;
    // get<1>(var).get();
    while (1)
    {
        cout<<"\t\t[SM] running"<<endl;
        usleep(3000);
        if(sigval) break;
    }
    cout<<"\t[SM]finish reporting running to EM\n"<<endl;
    return 0;
}
*/


/**
 * @brief No Notifier in SM so this thread isn't used but i will leave just in case
 * 
 * @param v_var 
 * @return void* 
 */
void *pthread1(void *v_var){
    cout<<"{SM} pthread1"<<endl;
    /// used for field sub or unsubscription

    while (1)
    {
        sockaddr_in echoClntAddr;                       // Address of datagram source 
        unsigned int clntLen = sizeof(echoClntAddr);    // Address length 
        std::vector<uint8_t> msg;                       // Payload message from client
        uint32_t msg_size;                              // Size of message

        server_main_socket_DG.UDPRecFrom((void *)&msg_size, sizeof(msg_size), (struct sockaddr *)&echoClntAddr, &clntLen);
        msg.resize(msg_size);
        server_main_socket_DG.UDPRecFrom((void *)&msg[0], msg_size, (struct sockaddr *)&echoClntAddr, &clntLen);


        if (msg[14] == 0x02) // make sure it's SOMEIP/SD message
        {
            ara::com::SOMEIP_MESSAGE::sd::SomeIpSDMessage sd_msg;
            ara::com::proxy_skeleton::Client_udp_Info cudp;


            sd_msg.Deserialize(msg);
            auto entry = (ara::com::entry::EventgroupEntry *)sd_msg.Entries()[0];

            cudp.addr = std::string(inet_ntoa(echoClntAddr.sin_addr));

            printf("\n[SERVER]  ->> Handling client %s   with msg size %d\n", inet_ntoa(echoClntAddr.sin_addr), msg_size);

            switch (entry->ServiceId())
            {
            case T_IN_UCM_INSTANCE_ID:
                switch (entry->EventgroupId())
                {
                case 0:
                    
                    break;

                default: // error invalid eventgroup id
                    break;
                }
                break;
            default:    // reply with error invalid service id
            break;

            }

        }
    }

}


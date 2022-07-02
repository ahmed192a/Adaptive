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
#define NUM_THREADS 3
#define SERVER_PORT         5375
#define SD_PORT             1690
#define INSTANCE_ID         1

#define MAX_QUEUE_CLIENTS   3        

///// Namespaces
using namespace std;
using namespace ara::exec;
using namespace ara::sm::triggerin;

///// Functions declarations
void  handle_sigterm(int sig);
void *pthread0(void *v_var);
void *pthread1(void *v_var);

////// global variables
int sigval = 0;
bool newState = false; // used for FSM of SM



ara::com::InstanceIdentifier instance(INSTANCE_ID);
ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle triggerin_handle{SERVER_PORT, SD_PORT};
std::shared_ptr<ara::sm::triggerin::skeleton::Trigger_In_UCM_Skeleton> UCM_triggerin_skeleton_ptr = std::make_shared<ara::sm::triggerin::skeleton::Trigger_In_UCM_Skeleton>(instance, triggerin_handle);

CServer server_main_socket_DG(SOCK_DGRAM);
CServer server_main_socket(SOCK_STREAM); 


/// Main code
int main(){
    cout<<endl<<"[SM]"<<std::string(get_current_dir_name())<<endl;
    signal(SIGTERM, handle_sigterm);
    cout<<"\t\t[SM]creating execution client "<<endl;
    ExecutionClient client;
    client.ReportExecutionState(ExecutionState::kRunning);



    // UDP Server sockets for events
    server_main_socket_DG.OpenSocket(SERVER_PORT);
    server_main_socket_DG.BindServer();

    pthread_t threads[NUM_THREADS];

    int th1, th2;
    int i = 0;

    th1 = pthread_create(&threads[0], NULL, pthread0, (void *)&i);
    if (th1)
    {
        cout << "[UCM SERVER] ERROR can't create thread " << th1 << endl;
        exit(-1);
    }
    i = 1;
    th2 = pthread_create(&threads[1], NULL, pthread1, (void *)&i);
    if (th2)
    {
        cout << "[UCM SERVER] ERROR can't create thread " << th2 << endl;
        exit(-1);
    }

    pthread_exit(NULL);

    return 0;
}

/////// Functions definitions
void handle_sigterm(int sig){
    sigval = 1;
    cout<<"{SM} terminating"<<endl;

    UCM_triggerin_skeleton_ptr->StopOfferService();    // stop offering service
    server_main_socket.CloseSocket();           // close server socket
    server_main_socket_DG.CloseSocket();        // close server socket
    exit(0);
}

void *pthread0(void *v_var){
    StateClient sm_client;      // change Function Group state

    cout<<"{SM} pthread0"<<endl;
    cout<<"[SM SERVER] OPEN SOCKET ON "<<endl;
    server_main_socket.OpenSocket(SERVER_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(MAX_QUEUE_CLIENTS);

    cout<<"[SM] Offering service to the SD"<<endl;
    UCM_triggerin_skeleton_ptr->OfferService();
    cout<<"[SM] Offered service to the SD"<<endl;


    while(1){
        Socket Sclient = server_main_socket.AcceptServer();
        cout << "\t[SM]  accepted" << endl;

        // Payload message from client
        std::vector<uint8_t> msg;  
        // Size of message                         
        uint32_t msg_size;

        // Receive a payload from client containing the method name and parameters
        Sclient.Receive((void *)&msg_size, sizeof(msg_size));   // recieve message size 
        msg.resize(msg_size);           //  resize the vector to allocate size of the coming message
        Sclient.Receive((void *)&msg[0], msg_size);             //  recieve the message


        cout << "\t[SM]  received" << endl;
        ara::com::SOMEIP_MESSAGE::Message someip_msg = ara::com::SOMEIP_MESSAGE::Message::Deserialize(msg);

        
        if (someip_msg.check_Methode_ID() == true)
        {
            // No methods in SM Services
            cout << "This is method request " << endl;
        }
        else
        {
            // check service id and switch over them 
            
            cout << "This is SET OR GET request" << endl;
            // handling GET or SET field request
            UCM_triggerin_skeleton_ptr->field_method_dispatch(someip_msg, Sclient);
        }
        cout<< "finish request \n";


        /*******************************          FSM           **************************************/



        /*******************************        END OF FSM      **************************************/

    }
    UCM_triggerin_skeleton_ptr->StopOfferService();    // stop offering service
    server_main_socket.CloseSocket();           // close server socket
}

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
            case INSTANCE_ID:
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
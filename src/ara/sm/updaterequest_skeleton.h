/**
 * @file updaterequest_skeleton.h
 * @author basmala
 * @brief 
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include "functional"
#include "CServer.h"
#include <vector>
#include "../../../SKELETON/skeleton/service_skeleton.h"

using namespace std;

namespace ara 
{
namespace sm 
{
namespace update_request
{
namespace skeleton
{
namespace events
{

}
namespace fields
{

}
namespace methods
{
    // using ResetMachine = int;
    // using StopUpdateSession = int;
    // using StartUpdateSession = int;
    // using PrepareUpdate = int;
    // using VerifyUpdate = int;
    // using PrepareRollback = int;
}

struct SD_data{
    int service_id;
    int process_id;
    int port_number;
    bool message_type;
};

struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};

//class Service_skeleton;

class update_request_Skeleton : public ara::com::SKELETON::skeleton::ServiceSkeleton

{
    private:
    /* data */
    int portNumber;
    int service_id;
    int service_descovery_port_number;
    CServer s1;
    struct sockaddr_in  cliaddr;
    
    public:
    update_request_Skeleton(
       // ara::com::InstanceIdentifier instance,
       // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent
	);
       // : ara::com::SKELETON::skeleton::ServiceSkeleton("update_request_Skeleton", instance, mode)

    

        //Events
	
        //Fields

	
        //Methods
       virtual void ResetMachine();
       virtual void StopUpdateSession();
       virtual int StartUpdateSession();
       virtual int PrepareUpdate();
       virtual int VerifyUpdate();
       virtual int PrepareRollback();

        using FunctionGroupNameType = std::string;


            // [SWS_SM_91018]
            /*
             * Name        : FunctionGroupListType
             * Subelements : FunctionGroupNameType
             * Description : A list of FunctionGroups.
             */
        using FunctionGroupListType = std::vector<FunctionGroupNameType>;

        // init
       // init();
    
    void start_service()
    {
        // s1(SOCK_DGRAM);
        this->s1.OpenSocket(portNumber);
        this->s1.BindServer();
        struct SD_data service = {service_id, getpid() ,portNumber, true};

        // struct sockaddr_in  cliaddr;
        this->cliaddr.sin_family = AF_INET; // IPv4
        this->cliaddr.sin_addr.s_addr = INADDR_ANY;
        this->cliaddr.sin_port = htons(service_descovery_port_number);

        this->s1.UDPSendTo((const struct SD_data*)&service, sizeof(struct SD_data), (const struct sockaddr *) &this->cliaddr);

        // this->s1.CloseSocket();
    }


        void StopOfferService()
    {
        // CServer s1(SOCK_DGRAM);
        // s1.OpenSocket(portNumber);
        // s1.BindServer();
        struct SD_data service = {service_id, getpid() ,portNumber, false};

        // struct sockaddr_in  cliaddr;
        // cliaddr.sin_family = AF_INET; // IPv4
        // cliaddr.sin_addr.s_addr = INADDR_ANY;
        // cliaddr.sin_addr.s_addr = INADDR_ANY;
        // cliaddr.sin_port = htons(service_descovery_port_number);

        this->s1.UDPSendTo((const struct SD_data*)&service, sizeof(struct SD_data), (const struct sockaddr *) &this->cliaddr);
        int x;
        socklen_t len = sizeof(this->cliaddr);
        // (struct sockaddr *) &cliaddr
        this->s1.UDPRecFrom(&x, sizeof(int), ( struct sockaddr *) &this->cliaddr, &len);
        this->s1.CloseSocket();
    }


    // template <typename Class>
    // void handle_call(Class& c, CServer& cserver,const struct C_Info& message, std::function<int ()> func)
    // {
    //     int result = func();
    //     cserver.SendServer(&result, sizeof(int));
    //     cserver.ClientClose();
    // }

    // void handle_call(CServer& cserver,const struct C_Info& message, std::function<int (std::vector<int>)> func)
    // {
    //     int result = func(message.param1);
    //     cserver.SendServer(&result, sizeof(int));
    //     cserver.ClientClose();
    // }

    // template <typename Class>
    // void HandleCall(Class &c,
    //                 CServer& cserver,
    //                 const struct C_Info& message,
    //                 std::function<int (std::vector<int>)> func)
    // {
    //     int result = func(message.param1);
    //     cserver.SendServer(&result, sizeof(int));
    //     cserver.ClientClose();   
    // }


    void method_dispatch(const struct C_Info& message, CServer& cserver)
    {
        cout<<"Dispatch "<<message.method_name<<endl;
       if(strcmp(message.method_name , "ResetMachine") == 0)
        {
            // auto _callback =
            //             std::bind(
            //                 &ResetMachine,
            //                 this);
           HandleCall(*this ,update_request_Skeleton::ResetMachine, message , cserver);
        }
        else if(strcmp(message.method_name , "StopUpdateSession") == 0)
        {
            // auto _callback =
            //             std::bind(
            //                 &StopUpdateSession,
            //                 this);
            HandleCall(*this ,update_request_Skeleton::StopUpdateSession, message , cserver);
        }
        else if(strcmp(message.method_name , "StartUpdateSession") == 0)
        {
            // auto _callback =
            //             std::bind(
            //                 &StartUpdateSession,
            //                 this);

            HandleCall(*this ,update_request_Skeleton::StartUpdateSession, message , cserver);
        }
        else if(strcmp(message.method_name , "PrepareUpdate") == 0)
        {
            // auto _callback =
            //             std::bind(
            //                 &PrepareUpdate,
            //                 this);
             HandleCall(*this ,update_request_Skeleton::PrepareUpdate, message , cserver);
        }
        else if(strcmp(message.method_name , "VerifyUpdate") == 0)
        {
            auto _callback =
                        std::bind(
                            &VerifyUpdate,
                            this);
             HandleCall(*this ,update_request_Skeleton::VerifyUpdate, message , cserver);
        }
        else if(strcmp(message.method_name , "PrepareRollback") == 0)
        {
            // auto _callback =
            //             std::bind(
            //                 &PrepareRollback,
            //                 this);
             HandleCall(*this ,update_request_Skeleton::PrepareRollback, message , cserver);
        }
        else
        {
            int result = -1;
            cserver.SendServer(&result, sizeof(int));
            cserver.ClientClose();
        }


    }
    
};
}
}
}
}

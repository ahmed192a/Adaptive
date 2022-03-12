/**
 * @file skeleton.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/SD_s/skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
using SD_data = ara::com::proxy_skeleton::SD_data;


using namespace std;
skeleton::skeleton( int service_id, CServer* server_udp)
:ara::com::proxy_skeleton::skeleton::ServiceSkeleton("skeleton",service_id, server_udp),
s1{server_udp}, 
event1(this , "event1" , 0),
event2(this , "event2" , 1),
field1(this , "field1" , 2)
{
    this->service_id = service_id;
    // this->s1.OpenSocket(portNumber);
    // this->s1.BindServer();
}

skeleton::~skeleton()
{
}

void skeleton::start_service()
{
    SD_data service = {service_id, getpid() ,portNumber, true};

    this->cliaddr.sin_family = AF_INET; // IPv4
    this->cliaddr.sin_addr.s_addr = INADDR_ANY;
    this->cliaddr.sin_port = htons(service_descovery_port_number);

    this->s1->UDPSendTo(( SD_data*)&service, sizeof( SD_data), ( struct sockaddr *) &this->cliaddr);
}

int skeleton::Add(std::vector<uint8_t> msg)
{
    ara::com::Deserializer dser;
    int val1 = dser.deserialize<int>(msg,sizeof(int));
    int val2 = dser.deserialize<int>(msg,sizeof(int)*2);

    return (val1 + val2);
}

void handle_call(Socket& cserver,const C_Info& message, std::function<int (int, int)> func)
{
    int result = func(message.param1, message.param2);
    cserver.Send(&result, sizeof(int));
    cserver.CloseSocket();
}

void skeleton::method_dispatch(std::vector<uint8_t>& message, Socket& cserver)
{
    ara::com::Deserializer dser;
    int methodID = dser.deserialize<int>(message,0);
    int result = -1;
	cout<<"\t[SERVER] Dispatch " << methodID << endl;

    switch (methodID)
    {
    case 0:
        result = Add(message);
        cserver.Send(&result, sizeof(int));
    	cserver.CloseSocket();
        break;
    default:
    	cserver.Send(&result, sizeof(int));
    	cserver.CloseSocket();
        break;
    }

    

}

void skeleton::StopOfferService()
{
     SD_data service = {service_id, getpid() ,portNumber, false};

    this->s1->UDPSendTo((  void *)&service, sizeof( SD_data), ( struct sockaddr *) &this->cliaddr);
    int x;
    socklen_t len = sizeof(this->cliaddr);
    // this->s1.CloseSocket();
}


#include "skeleton.h"

using namespace std;
skeleton::skeleton(int portNumber, int sd, int service_id):s1(SOCK_DGRAM)
{
    this->portNumber = portNumber;
    this->service_id = service_id;
    this->service_descovery_port_number=sd;
}

skeleton::~skeleton()
{
}


struct C_Info
{
    int process_id;
    char method_name[30];
    int param1;
    int param2;
};

//udp

void skeleton::start_service()
{
    this->s1.OpenSocket(portNumber);
    this->s1.BindServer();
    struct SD_data service = {service_id, getpid() ,portNumber, true};

    this->cliaddr.sin_family = AF_INET; // IPv4
    this->cliaddr.sin_addr.s_addr = INADDR_ANY;
    this->cliaddr.sin_port = htons(service_descovery_port_number);

    this->s1.UDPSendTo((const struct SD_data*)&service, sizeof(struct SD_data), (const struct sockaddr *) &this->cliaddr);
}

int add(int num1, int num2)
{
    return (num1 + num2);
}

void handle_call(CServer& cserver,const struct C_Info& message, std::function<int (int, int)> func)
{
    int result = func(message.param1, message.param2);
    cserver.SendServer(&result, sizeof(int));
    cserver.ClientClose();
}

void skeleton::method_dispatch(const struct C_Info& message, CServer& cserver)
{
	cout<<"Dispatch " << message.method_name << endl;
    if(strcmp(message.method_name , "add") == 0)
    {
        handle_call(cserver, message, add);
    }
    else
    {
    	int result = -1;
    	cserver.SendServer(&result, sizeof(int));
    	cserver.ClientClose();
    }

}

void skeleton::StopOfferService()
{
    struct SD_data service = {service_id, getpid() ,portNumber, false};

    this->s1.UDPSendTo((const struct SD_data*)&service, sizeof(struct SD_data), (const struct sockaddr *) &this->cliaddr);
    int x;
    socklen_t len = sizeof(this->cliaddr);
    this->s1.CloseSocket();
}


#ifndef CCLIENT_H
#define CCLIENT_H
#include<netinet/in.h>
#include<netdb.h>
#include<string>
#include"../errors.h"

class CClient
{
public:
	int sockfd,portno,type;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	CClient(int type);
	error_kind OpenSocket();
	error_kind GetHost(std::string hostname,int hostno);
	error_kind ClientConnect();
	error_kind ClientWrite(void* data, int size);
	error_kind ClientRead(void* data, int size);
	void CloseSocket();
	
};

#endif

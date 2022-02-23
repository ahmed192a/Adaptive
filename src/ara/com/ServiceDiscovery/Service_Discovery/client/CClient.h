#ifndef CCLIENT_H
#define CCLIENT_H
#include<netinet/in.h>
#include<netdb.h>
#include<string>
#include"Utility.h"

class CClient
{
public:
	int sockfd,portno,type;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	CClient(int type);
	eErrorType OpenSocket();
	eErrorType GetHost(std::string hostname,int hostno);
	eErrorType ClientConnect();
	eErrorType ClientWrite(void* data, int size);
	eErrorType ClientRead(void* data, int size);
	void CloseSocket();
	
};

#endif

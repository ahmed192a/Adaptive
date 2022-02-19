#ifndef CLIENT_H
#define CLIENT_H
#include<netinet/in.h>
#include<netdb.h>
#include<string>
#include"errors.h"

class Client
{
public:
	int sockfd,portno,type;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	Client(int type);
	error_kind OpenSocket();
	error_kind  GetHost(std::string hostname,int hostno);
	error_kind  ClientConnect();
	error_kind  ClientWrite(char* data);
	error_kind  ClientRead(char* data);
	void CloseSocket();
	
};

#endif

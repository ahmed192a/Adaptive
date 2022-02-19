#ifndef CSERVER_H
#define CSERVER_H
#include<netinet/in.h>
#include<sys/socket.h>
#include"errors.h"

class Server
{
public:
	int sockfd,newsockfd,portno,type;
	socklen_t clientlen;

	struct sockaddr_in serv_addr, cli_addr;

	Server(int type);
	error_kind OpenSocket(int portno);
	error_kind BindServer();
	error_kind ListenServer(int no);
	error_kind AcceptServer();
	error_kind SendServer(char* msg);
	error_kind ReceiveServer(char* data); 
	void CloseSocket();
	
	
};


#endif

#ifndef CSERVER_H
#define CSERVER_H
#include<netinet/in.h>
#include<sys/socket.h>
#include"Utility.h"

class CServer
{
public:
	int sockfd,newsockfd,portno,type;
	socklen_t clientlen;

	struct sockaddr_in serv_addr, cli_addr;

	CServer(int type);
	~CServer();
	eErrorType OpenSocket(int portno);
	eErrorType BindServer();
	eErrorType ListenServer(int no);
	eErrorType AcceptServer();
	eErrorType SendServer(const void* buffer, size_t n);
	eErrorType UDPSendTo(const void * buffer,size_t n,const sockaddr * address);
	eErrorType ReceiveServer(void* buffer, size_t n);
	eErrorType UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	void CloseSocket();
	void ClientClose();
	
};


#endif

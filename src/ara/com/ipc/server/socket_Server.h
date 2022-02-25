#ifndef CSERVER_H
#define CSERVER_H
#include<netinet/in.h>
#include<sys/socket.h>
#include"../errors.h"


class CServer
{
public:
	int sockfd,newsockfd,portno,type;
	socklen_t clientlen;

	struct sockaddr_in serv_addr, cli_addr;

	CServer(int type);
	~CServer();
	error_kind OpenSocket(int portno);
	error_kind BindServer();
	error_kind ListenServer(int no);
	error_kind AcceptServer();
	error_kind SendServer(const void* buffer, size_t n);
	error_kind UDPSendTo(const void * buffer,size_t n,const sockaddr * address);
	error_kind ReceiveServer(void* buffer, size_t n);
	error_kind UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	void CloseSocket();
	void ClientClose();
	
};


#endif

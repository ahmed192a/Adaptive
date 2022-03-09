/**
 * @file socket_Server.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CSERVER_H
#define CSERVER_H
#include<netinet/in.h>
#include<sys/socket.h>
#include"ara/com/ipc/ipc_errors.hpp"


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
	error_kind SendServer( void* buffer, size_t n);
	error_kind UDPSendTo( void * buffer,size_t n, sockaddr * address);
	error_kind ReceiveServer(void* buffer, size_t n);
	error_kind UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	void CloseSocket();
	void ClientClose();
	
};


#endif

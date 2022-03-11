/**
 * @file socket.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IPC_SERVER_H
#define IPC_SERVER_H
#include<netinet/in.h>
#include<sys/socket.h>
#include"ara/com/ipc/ipc_errors.hpp"


class Socket
{
private:
	int m_sockfd;
	struct sockaddr_in  m_cli_addr;
public:
	Socket(int sockfd, struct sockaddr_in  cli_addr);
    Socket(){}

	~Socket();
	error_kind Send( void* buffer, size_t n);
	error_kind UDPSendTo( void * buffer,size_t n, sockaddr * address);
	error_kind Receive(void* buffer, size_t n);
	error_kind UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	void CloseSocket();	
};


#endif
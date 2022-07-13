#include "ara/com/ipc/server/socket.hpp"
#include <iostream>
#include<unistd.h>
#include<sys/types.h>
#include <cstring>

Socket::Socket(int sockfd, struct sockaddr_in  cli_addr)
:m_sockfd{sockfd},
m_cli_addr{cli_addr}
{
}
Socket::~Socket()
{
    close(this->m_sockfd);
}
error_kind Socket::Send( void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	ssize_t sndRet = send(this->m_sockfd, buffer,n,0);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<", Error Message :"<<strerror(errno)<<std::endl;
	}
	return Error;
}
error_kind Socket::UDPSendTo( void * buffer,size_t n, sockaddr * address)
{
	error_kind Error = SUCCEEDED;

	ssize_t sndRet = sendto(this->m_sockfd, buffer , n,MSG_CONFIRM, address, sizeof(sockaddr_in));
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<", Error Message :"<<strerror(errno)<<std::endl;
	}


	return Error;
}
error_kind Socket::Receive(void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	memset(buffer,'\0',n);
	// std::cout<<this->newsockfd << "  "<< this->sockfd<<std::endl;
	// recv(newSocket, ohlala, sizeof(ohlala), 0);
	ssize_t rdRet = recv(this->m_sockfd,buffer,n, 0);
	if(rdRet < 0) 
	{
		Error = RECEIVE_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<", Error Message :"<<strerror(errno)<<std::endl;
	}
	return Error;
}
error_kind Socket::UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size)
{
	error_kind Error = SUCCEEDED;

	ssize_t sndRet = recvfrom(this->m_sockfd, buffer , n,MSG_WAITALL, address, size);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<", Error Message :"<<strerror(errno)<<std::endl;
	}


	return Error;
}
void Socket::CloseSocket()
{
    close(this->m_sockfd);
}

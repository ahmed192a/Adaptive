/**
 * @file socket_Server.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<strings.h>
#include<string.h>
#include<errno.h>
#include "ara/com/ipc/server/socket_Server.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
CServer::CServer(int type)
{
	//std::cout<<"server object created"<<std::endl;
	this->type=type;

}

error_kind CServer::OpenSocket(int portno)
{
	error_kind Error = SUCCEEDED;
	//create socket
	this->sockfd = socket(AF_INET, type, 0);
	if(this->sockfd < 0)
	{
		Error = FAILEDSOCETOPEN;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
		return Error;
	}
	//clear address structure
	memset((char *) &this->serv_addr,'\0', sizeof(this->serv_addr));

	this->portno = portno;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =  inet_addr("127.0.0.1");//INADDR_ANY; 
	serv_addr.sin_port = htons(this->portno); 
	
	return Error;
}

error_kind CServer::BindServer()
{

	int yes = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
	                        (void*)&yes, sizeof(yes)) < 0) {
	   // fprintf(stderr, "setsockopt() failed. Error: %d\n", GETSOCKETERRNO());
		cout<<"[SERVER SOCKET] ERROR BIND---------\n";
	}

	error_kind Error = SUCCEEDED;
	int bindRet = bind(sockfd,(struct sockaddr *) &this->serv_addr,sizeof(this->serv_addr)); 
	std::cout<<"[SERVER SOCKET] bind result" <<bindRet<<std::endl;
	if(bindRet < 0)
	{
		Error = BIND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}
	return Error;
	
}

error_kind CServer::ListenServer(int no)
{
	error_kind Error = SUCCEEDED;
	int lisret = listen(sockfd,no);
	if(lisret < 0)
	{
		Error = LISTEN_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}
	return Error;
	
}

error_kind CServer::AcceptServer()
{
	error_kind Error = SUCCEEDED;
	this->clientlen = sizeof(this->cli_addr);
	this->newsockfd = accept(this->sockfd,(struct sockaddr *)&this->cli_addr,&this->clientlen);
	std::cout << "[SERVER SOCKET] accept " << this->newsockfd << std::endl;
	if(this->newsockfd < 0)
	{
		Error = ACCEPT_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}
	return Error;
}


error_kind CServer::SendServer(void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	ssize_t sndRet = send(this->newsockfd, buffer,n,0);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}


	return Error;
}

error_kind CServer::UDPSendTo( void * buffer,size_t n, sockaddr * address)
{
	error_kind Error = SUCCEEDED;

	ssize_t sndRet = sendto(this->sockfd, buffer , n,MSG_CONFIRM, address, sizeof(sockaddr_in));
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}


	return Error;
}

error_kind CServer::UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size)
{
	error_kind Error = SUCCEEDED;

	ssize_t sndRet = recvfrom(this->sockfd, buffer , n,MSG_WAITALL, address, size);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}


	return Error;
}


error_kind CServer::ReceiveServer(void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	memset(buffer,'\0',n);
	// std::cout<<this->newsockfd << "  "<< this->sockfd<<std::endl;
	// recv(newSocket, ohlala, sizeof(ohlala), 0);
	ssize_t rdRet = recv(this->newsockfd,buffer,n, 0);
	if(rdRet < 0) 
	{
		Error = RECEIVE_FAILED;
		std::cout<<"[SERVER SOCKET] Error Code :"<<errno<<std::endl;
	}
	return Error;
}

void CServer::CloseSocket()
{
	// close(this->newsockfd);
	close(this->sockfd);
}

void CServer::ClientClose()
{
	close(this->newsockfd);
}


CServer::~CServer(){
	close(this->newsockfd);
	close(this->sockfd);
}
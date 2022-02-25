#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<strings.h>
#include<string.h>
#include<errno.h>
#include"socket_Server.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
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
		std::cout<<"Error Code :"<<errno<<std::endl;
		return Error;
	}
	//clear address structure
	bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
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
		cout<<"ERROR---------\n";
	}

	error_kind Error = SUCCEEDED;
	int bindRet = bind(sockfd,(struct sockaddr *) &this->serv_addr,sizeof(this->serv_addr)); 
	std::cout<<"bind" <<bindRet<<std::endl;
	if(bindRet < 0)
	{
		Error = BIND_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
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
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
	
}

error_kind CServer::AcceptServer()
{
	error_kind Error = SUCCEEDED;
	this->clientlen = sizeof(this->cli_addr);
	this->newsockfd = accept(this->sockfd,(struct sockaddr *)&this->cli_addr,&this->clientlen);
	std::cout << "accept " << this->newsockfd << std::endl;
	if(this->newsockfd < 0)
	{
		Error = ACCEPT_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}


error_kind CServer::SendServer(const void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	ssize_t sndRet = send(this->newsockfd, buffer,n,0);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}


	return Error;
}

error_kind CServer::UDPSendTo(const void * buffer,size_t n,const sockaddr * address)
{
	error_kind Error = SUCCEEDED;
	// sendto(udpServer, (const struct SD_data*)&service, sizeof(struct SD_data), 
	// MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
	// 	len);
	ssize_t sndRet = sendto(this->sockfd, buffer , n,MSG_CONFIRM, address, sizeof(sockaddr_in));
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}


	return Error;
}

error_kind CServer::UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size)
{
	error_kind Error = SUCCEEDED;
	// n = recvfrom(udpServer, &shared_mem[0], sizeof(struct SD_data), 
    //                 MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
	ssize_t sndRet = recvfrom(this->sockfd, buffer , n,MSG_WAITALL, address, size);
	if(sndRet < 0)
	{
		Error = SEND_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}


	return Error;
}


error_kind CServer::ReceiveServer(void* buffer, size_t n)
{
	error_kind Error = SUCCEEDED;
	bzero(buffer,n);
	// std::cout<<this->newsockfd << "  "<< this->sockfd<<std::endl;
	// recv(newSocket, ohlala, sizeof(ohlala), 0);
	ssize_t rdRet = recv(this->newsockfd,buffer,n, 0);
	if(rdRet < 0) 
	{
		Error = RECEIVE_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
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
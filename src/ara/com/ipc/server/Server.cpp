#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<strings.h>
#include<string.h>
#include<errno.h>
#include"Server.h"

CServer::Server(int type)
{
	
	this->type=type;

}

error_kind Server::OpenSocket(int portno)
{
	error_kind error = SUCCESSED;
	//create socket
	this->sockfd = socket(AF_INET, type, 0);
	if(this->sockfd < 0)
	{
		error = FAILEDSOCETOPEN;
		return error;
	}
	//clear address structure
	bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
	this->portno = portno;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; 
	serv_addr.sin_port = htons(this->portno); 
	
	return error;
}

error_kind Server::BindServer()
{
	error_kind error = SUCCESSED;
	int bindRet = bind(sockfd,(struct sockaddr *) &this->serv_addr,sizeof(this->serv_addr)); 
	std::cout<<bindRet<<std::endl;
	if(bindRet < 0)
	{
		error = BIND_FAILED;
		
	}
	return error;
	
}

error_kind Server::ListenServer(int no)
{
	error_kind error = SUCCESSED;
	int lisret = listen(sockfd,no);
	if(lisret < 0)
	{
		error = LISTEN_FAILED;
		
	}
	return error;
	
}

error_kind Server:::AcceptServer()
{
	error_kind error = SUCCESSED;
	this->newsockfd = accept(this->sockfd,(struct sockaddr *)&this->cli_addr,&this->clientlen);
	if(this->newsockfd < 0)
	{
		error = ACCEPT_FAILED;
		
	}
	return error;
}


error_kind Server::SendServer(char* msg)
{
	error_kind error = SUCCESSED;
	ssize_t sndRet = send(this->newsockfd,msg,strlen(msg),0);
	if(sndRet < 0)
	{
		error =SEND_FAILED;
	
	}


	return error;
}


error_kind Server::ReceiveServer(char* data)
{
	error_kind error = SUCCESSED;
	bzero(data,256);
	std::cout<<this->newsockfd << "  "<< this->sockfd<<std::endl;
	ssize_t rdRet = read(this->newsockfd,data,255);
	if(rdRet < 0) 
	{
		error = RECEIVE_FAILED;
		
	}
	return error;
}

void Server::CloseSocket()
{
	close(this->newsockfd);
	close(this->sockfd);
}

#include<unistd.h>
#include<iostream>
#include<strings.h>
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include"CClient.h"
#include <iostream>
using namespace std;

CClient::CClient(int type)
{
	this->type=type;
	this->server = NULL;
}

eErrorType CClient::OpenSocket()
{
	eErrorType Error = SUCCESS;
	this->sockfd = socket(AF_INET,type,0);
	if(this->sockfd < 0)
	{
		Error = SOCKETOPENFAIL;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}


eErrorType CClient::GetHost(std::string hostname,int hostno)
{
	this->portno=hostno;
	eErrorType Error = SUCCESS;
	this->server = gethostbyname(hostname.c_str());
	if(this->server == NULL)
	{
		Error = GETHOSTFAIL;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}

eErrorType CClient::ClientConnect()
{
	eErrorType Error = SUCCESS;
	bzero((char*)&this->serv_addr,sizeof(this->serv_addr));
	this->serv_addr.sin_family = AF_INET;
	bcopy((char *)this->server->h_addr,(char *)&this->serv_addr.sin_addr.s_addr,this->server->h_length);
	this->serv_addr.sin_port = htons(this->portno);
	int conRet = connect(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(conRet < 0)
	{
		Error = CONNECTFAIL;
		std::cout << "Error Code: " << errno << std::endl;
	}
	return Error;
}

eErrorType CClient::ClientWrite(void* data, int size)
{
	eErrorType Error = SUCCESS;

	int WrtRet = send(this->sockfd, data, size, 0);
	if(WrtRet < 0)
	{
		Error = WRITEFAIL;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	
	return Error;
}

eErrorType CClient::ClientRead(void* data, int size)
{
	eErrorType Error = SUCCESS;
	bzero(data, size);
	int RdRet = read(this->sockfd, data, size);
	if(RdRet < 0)
	{
		Error = READFAIL;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}

void CClient::CloseSocket()
{
	close(this->sockfd);
}

/**
 * @file socket_Client.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<unistd.h>
#include<iostream>
#include<strings.h>
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include "ara/com/ipc/client/socket_Client.hpp"
using namespace std;

CClient::CClient(int type)
{
	this->type=type;
	this->server = NULL;
}

error_kind CClient::OpenSocket()
{
	error_kind Error = SUCCEEDED;
	this->sockfd = socket(AF_INET,type,0);
	if(this->sockfd < 0)
	{
		Error = FAILEDSOCETOPEN;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}


error_kind CClient::GetHost(std::string hostname,int hostno)
{
	this->portno=hostno;
	error_kind Error = SUCCEEDED;
	this->server = gethostbyname(hostname.c_str());
	if(this->server == NULL)
	{
		Error = GETTINGHOST_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}

error_kind CClient::ClientConnect()
{
	error_kind Error = SUCCEEDED;
	memset((char*)&this->serv_addr,'\0', sizeof(this->serv_addr));

	this->serv_addr.sin_family = AF_INET;
	bcopy((char *)this->server->h_addr,(char *)&this->serv_addr.sin_addr.s_addr,this->server->h_length);
	this->serv_addr.sin_port = htons(this->portno);
	int conRet = connect(this->sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(conRet < 0)
	{
		Error = CONNECTION_FAILED;
		std::cout << "Error Code: " << errno << std::endl;
	}
	return Error;
}

error_kind CClient::ClientWrite(void* data, int size)
{
	error_kind Error = SUCCEEDED;

	int WrtRet = send(this->sockfd, data, size, 0);
	if(WrtRet < 0)
	{
		Error = WRITING_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	
	return Error;
}

error_kind CClient::ClientRead(void* data, int size)
{
	error_kind Error = SUCCEEDED;
	memset(data, '\0', size);
	int RdRet = read(this->sockfd, data, size);
	if(RdRet < 0)
	{
		Error = READING_FAILED;
		std::cout<<"Error Code :"<<errno<<std::endl;
	}
	return Error;
}

void CClient::CloseSocket()
{
	close(this->sockfd);
}

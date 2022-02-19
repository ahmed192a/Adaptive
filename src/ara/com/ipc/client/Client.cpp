#include<unistd.h>
#include<iostream>
#include<strings.h>
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include"Client.h"
#include <iostream>
using namespace std;

Client::Client(int type)
{
	this->type=type;
	this->server = NULL;
}

error_kind Client::OpenSocket()
{
	error_kind error = SUCCEEDED;
	this->sockfd = socket(AF_INET,type,0);
	if(this->sockfd < 0)
	{
		error = FAILEDSOCETOPEN;
	}
	return error;
}


error_kind Client::GetHost(string hostname,int hostno)
{
	this->portno=hostno;
	error_kind error = SUCCEEDED;
	this->server = gethostbyname(hostname.c_str());
	if(this->server == NULL)
	{
		error = GETTINGHOST_FAILED;
	}
	return error;
}

error_kind Client::ClientConnect()
{
	error_kind error  = SUCCEEDED;
	bzero((char*)&this->serv_addr,sizeof(this->serv_addr));
	this->serv_addr.sin_family = AF_INET;
	bcopy((char *)this->server->h_addr,(char *)&this->serv_addr.sin_addr.s_addr,this->server->h_length);
	this->serv_addr.sin_port = htons(this->portno);
	int conRet = connect(this->sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(conRet < 0)
	{
		error = CONNECTION_FAILED;
	}
	return error;
}

error_kind Client::ClientWrite(char * data)
{
	error_kind error  = SUCCEEDED;

	int WrtRet = send(this->sockfd,data,strlen(data),0);
	if(WrtRet < 0)
	{
		error = WRITING_FAILED;
	
	}
	
	return error;
}

error_kind Client::ClientRead(char* data)
{
	error_kind error  = SUCCEEDED;
	bzero(data,256);
	int RdRet = read(this->sockfd,data,255);
	if(RdRet < 0)
	{
		error = READING_FAILED;
	}
	return error;
}

void Client::CloseSocket()
{
	close(this->sockfd);
}

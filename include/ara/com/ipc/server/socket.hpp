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


/**
 * @class Socket
 * @brief Socket class for any tcp or udp server sockets 
 */
class Socket
{
private:
	int m_sockfd;						//!< Socket file descriptor
	struct sockaddr_in  m_cli_addr;		//!< Client address
public:
	/**
	 * @brief Construct a new Socket object
	 * 
	 * @param sockfd     socket file descriptor
	 * @param cli_addr  client address
	 */
	Socket(int sockfd, struct sockaddr_in  cli_addr);
	/**
	 * @brief Construct a new Socket object
	 * 
	 */
    Socket(){}
	/**
	 * @brief Destroy the Socket object
	 * 
	 */
	~Socket();
	/**
	 * @brief Send the data to the client TCP
	 * 
	 * @param buffer 
	 * @param n 
	 * @return error_kind 
	 */
	error_kind Send( void* buffer, size_t n);
	/**
	 * @brief Receive the data from the client TCP
	 * 
	 * @param buffer 
	 * @param n 
	 * @return error_kind 
	 */
	error_kind Receive(void* buffer, size_t n);

	/**
	 * @brief Send the data to the client UDP
	 * 
	 * @param buffer 
	 * @param n 
	 * @param address 
	 * @return error_kind 
	 */
	error_kind UDPSendTo( void * buffer,size_t n, sockaddr * address);
	/**
	 * @brief Receive the data from the client UDP
	 * 
	 * @param buffer 
	 * @param n 
	 * @param address 
	 * @param size 
	 * @return error_kind 
	 */
	error_kind UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	/**
	 * @brief Close the socket
	 * 
	 */
	void CloseSocket();	
};


#endif // IPC_SERVER_H
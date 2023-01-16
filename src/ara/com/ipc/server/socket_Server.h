/**
 * @file socket_Server.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief CServer class for any tcp or udp server sockets
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CSERVER_H
#define CSERVER_H
#include "ara/com/ipc/server/socket.h"

/**
 * @brief CServer class for any tcp or udp server sockets
 * 
 */
class CServer
{
private:
	socklen_t clientlen;			/*!< client length */
	struct sockaddr_in serv_addr;	/*!< server address */
	struct sockaddr_in cli_addr;	/*!< client address */
public:
	int sockfd;						/*!< socket file descriptor */
	int newsockfd;					/*!< new socket file descriptor */
	int portno;						/*!< port number */
	int type;						/*!< type of socket (UDP-SOCK_DGRAM or TCP - SOCK_STREAM) */

	/**
	 * @brief Construct a new CServer object
	 * 
	 * @param type 
	 */
	CServer(int type);
	/**
	 * @brief Destroy the CServer object
	 * 
	 */
	~CServer();
	/**
	 * @brief Open the server socket
	 * 
	 * @param portno 
	 * @return error_kind 
	 */
	error_kind OpenSocket(int portno);
	/**
	 * @brief Bind the socket to the port number
	 * 
	 * @return error_kind 
	 */
	error_kind BindServer();
	/**
	 * @brief Listen for the client connection
	 * 
	 * @param no 
	 * @return error_kind 
	 */
	error_kind ListenServer(int no);
	/**
	 * @brief Accept the Client connection
	 * 
	 * @return Socket 
	 */
	Socket AcceptServer();
	/**
	 * @brief Enable Interrupt Signal on the socket
	 * 
	 * @param SIGIOHandler 
	 * @return error_kind 
	 */
	error_kind EnableInterrupt(void (*SIGIOHandler)(int) );
	/**
	 * @brief Send data to the client using the (UDP) socket
	 * 
	 * @param buffer 
	 * @param n 
	 * @param address 
	 * @return error_kind 
	 */
	error_kind UDPSendTo( void * buffer,size_t n, sockaddr * address);
	/**
	 * @brief Recieve data from the (UDP) socket 
	 * 
	 * @param buffer 
	 * @param n 
	 * @param address 
	 * @param size 
	 * @return error_kind 
	 */
	error_kind UDPRecFrom(void * buffer,size_t n, sockaddr * address, socklen_t * size);
	/**
	 * @brief  Close the socket
	 * 
	 */
	void CloseSocket();	
};


#endif // CSERVER_H

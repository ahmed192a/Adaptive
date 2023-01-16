/**
 * @file socket_Client.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief CClient class for any tcp or udp client sockets
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CCLIENT_H
#define CCLIENT_H
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include "ara/com/ipc/ipc_errors.h"

/**
 * @class CClient
 * @brief CClient class for any tcp or udp client sockets
 */
class CClient
{
private:
	int sockfd;					  /*!<  socket file descriptor */
	int portno;					  /*!<  port number */
	int type;					  /*!<  type of socket (UDP-SOCK_DGRAM or TCP - SOCK_STREAM) */
	struct sockaddr_in serv_addr; /*!<  server address */
	struct hostent *server;		  /*!<  server host */

public:
	/**
	 * @brief Construct a new CClient object
	 *
	 * @param type  type of socket (UDP-SOCK_DGRAM or TCP - SOCK_STREAM)
	 */
	CClient(int type);
	/**
	 * @brief Open the socket
	 *
	 * @return error_kind
	 */
	error_kind OpenSocket();
	/**
	 * @brief Get the Host name and port number
	 *
	 * @param hostname
	 * @param hostno
	 * @return error_kind
	 */
	error_kind GetHost(std::string hostname, int hostno);
	/**
	 * @brief Close the socket
	 *
	 * @return error_kind
	 */
	error_kind ClientConnect();
	/**
	 * @brief Enable the Intterrupt on the socket
	 *
	 * @param SIGIOHandler
	 * @return error_kind
	 */
	error_kind EnableInterrupt(void (*SIGIOHandler)(int));

	/**
	 * @brief Client send data TCP
	 *
	 * @param data
	 * @param size
	 * @return error_kind
	 */
	error_kind ClientWrite(void *data, int size);
	/**
	 * @brief Client read data TCP
	 *
	 * @param data
	 * @param size
	 * @return error_kind
	 */
	error_kind ClientRead(void *data, int size);
	/**
	 * @brief Client send data UDP
	 *
	 * @param buffer
	 * @param n
	 * @param address
	 * @return error_kind
	 */
	error_kind UDPSendTo(void *buffer, size_t n, sockaddr *address);
	/**
	 * @brief Client read data UDP
	 *
	 * @param buffer
	 * @param n
	 * @param address
	 * @param size
	 * @return error_kind
	 */
	error_kind UDPRecFrom(void *buffer, size_t n, sockaddr *address, socklen_t *size);
	/**
	 * @brief Close the socket
	 *
	 * @return void
	 */
	void CloseSocket();
};

#endif // CCLIENT_H

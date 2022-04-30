/**
 * @file ipc_errors.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef ERRORS_H
#define ERRORS_H

/// @brief sockets error code 
enum error_kind		
{
	SUCCEEDED,			//!< (value 0x00 or 0) not set => Means no error
	FAILEDSOCETOPEN,	//!< (value 0x01 or 1) means that an error happened while openning socket
	BIND_FAILED,		//!< (value 0x02 or 2) means that an error happened while binding to bort
	LISTEN_FAILED,		//!< (value 0x03 or 3) means that an error happened while listenning
	ACCEPT_FAILED,		//!< (value 0x04 or 4) means that an error happened while accepting
	SEND_FAILED,		//!< (value 0x05 or 5) means that an error happened while sending
	RECEIVE_FAILED,		//!< (value 0x06 or 6) means that an error happened while receiving
	GETTINGHOST_FAILED,	//!< (value 0x07 or 7) means that an error happened while getting host
	CONNECTION_FAILED,	//!< (value 0x08 or 8) means that an error happened while trying to connect
	WRITING_FAILED,		//!< (value 0x09 or 9) means that an error happened while writing
	READING_FAILED,		//!< (value 0x0A or 10) means that an error happened while reading
	FAILED				//!< (value 0x0B or 11) means that general failure
};


#endif


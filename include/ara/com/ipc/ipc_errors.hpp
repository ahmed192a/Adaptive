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
	/// (value 0x00 or 0) not set => Means no error 
	SUCCEEDED,
	/// (value 0x01 or 1) means that an error happened while openning socket
	FAILEDSOCETOPEN,
	/// (value 0x02 or 2) means that an error happened while binding to bort
	BIND_FAILED,
	/// (value 0x03 or 3) means that an error happened while listenning
	LISTEN_FAILED,
	/// (value 0x04 or 4) means that an error happened while accepting
	ACCEPT_FAILED,
	/// (value 0x05 or 5) means that an error happened while sending
	SEND_FAILED,
	/// (value 0x06 or 6) means that an error happened while receiving
	RECEIVE_FAILED,
	/// (value 0x07 or 7) means that an error happened while getting host
	GETTINGHOST_FAILED,
	/// (value 0x08 or 8) means that an error happened while trying to connect
	CONNECTION_FAILED,
	/// (value 0x09 or 9) means that an error happened while writing
	WRITING_FAILED,
	/// (value 0x0A or 10) means that an error happened while reading
	READING_FAILED,
	/// (value 0x0B or 11) means that general failure
	FAILED
};


#endif


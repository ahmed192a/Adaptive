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


enum error_kind
{
	SUCCEEDED,
	FAILEDSOCETOPEN,
	BIND_FAILED,
	LISTEN_FAILED,
	ACCEPT_FAILED,
	SEND_FAILED,
	RECEIVE_FAILED,
	GETTINGHOST_FAILED,
	CONNECTION_FAILED,
	WRITING_FAILED,
	READING_FAILED,
	FAILED
};


#endif


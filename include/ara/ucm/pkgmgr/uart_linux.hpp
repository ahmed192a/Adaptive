/**
 * @file uart_linux.hpp
 * @author Ahmed mohamed, Basmala magdy, Bassant yasser, Sarah mohamed,Aya sameh
 * @brief  Uart class used for any serail communication between adaptive ECU and any other ECU's
 * @version 0.1
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef UART_LINUX
#define UART_LINUX

// C library headers
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#include <bits/stdc++.h> 


/**
 * @brief UART (Serail port communication) class
 * 
 */
class uart_linux
{
private:
    /* data */
    int serial_port;            // File descriptor for the serial port

public:
    /**
     * @brief Construct a new uart_linux object
     * 
     */
    uart_linux();
    /**
     * @brief Destroy the uart linux object
     * 
     */
    ~uart_linux();  
    /**
     * @brief Send Buffer of bytes on Serial Port 
     * 
     * @param [in] msg   Buffer of bytes to send
     * @param [in] size  Size of the buffer
     */
    void UART_sendBlock(void *msg, int size);
    /**
     * @brief Receive Buffer of bytes on Serial Port
     * 
     * @param [in] read_buf  Buffer of bytes to receive
     * @param [in] size      Size of the buffer
     */
    void UART_receiveBlock(void *read_buf, int size);
};

#endif
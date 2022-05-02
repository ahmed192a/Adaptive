#ifndef UART_LINUX
#define UART_LINUX

// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h>   // Contains file controls like O_RDWR
#include <errno.h>   // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h>  // write(), read(), close()
#include <bits/stdc++.h>



class uart_linux
{
private:
    /* data */
    int serial_port;

public:
    uart_linux(/* args */);
    ~uart_linux();
    void UART_sendBlock(void *msg, int size);
    void UART_receiveBlock(void *read_buf, int size);
};

#endif
/**
 * @file uart_linux.cpp
 * @author Ahmed mohamed, Basmala magdy, Bassant yasser, Sarah mohamed,Aya sameh
 * @brief  Uart class used for any serail communication between adaptive ECU and any other ECU's
 * @version 0.1
 * @date 2022-05-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/ucm/pkgmgr/uart_linux.hpp"
#include <iostream>
uart_linux::uart_linux(/* args */)
{
    // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
    this->serial_port = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);

    // Create new termios struct, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        exit(1);
        return ;
    }
    // printf("\n\n");
    // printf("cc %x, ci %x, co %x, cl %x\n",tty.c_cflag, tty.c_iflag,tty.c_oflag, tty.c_lflag  );
    // printf("c_line %x\n", tty.c_line);

    // tty.c_iflag = 0x1c00;
    // tty.c_oflag = 0x0000;
    // tty.c_lflag = 0x8a20; 

    // tty.c_cflag &= ~PARENB;                 // Clear parity bit, disabling parity (most common)
    // tty.c_cflag &= ~CSTOPB;                 // Clear stop field, only one stop bit used in communication (most common)
    // tty.c_cflag &= ~CSIZE;                  // Clear all bits that set the data size
    // tty.c_cflag |= CS8;                     // 8 bits per byte (most common)
    // tty.c_cflag &= ~CRTSCTS;                // Disable RTS/CTS hardware flow control (most common)
 
    // tty.c_iflag |= (IXON | IXOFF | IXANY);  // Turn off s/w flow ctrl

    // // Set in/out baud rate to be 9600
    // cfsetispeed(&tty, B9600);
    // cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    // if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    // {
    //     printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    //     return ;
    // }


}
uart_linux::~uart_linux()
{
    // Close the serial port
    close(this->serial_port);              
}
void uart_linux::UART_sendBlock(void *msg, int size)
{
    // Write the data to the serial port
    write(this->serial_port, msg, size);    
}
void uart_linux::UART_receiveBlock(void *read_buf, int size)
{
    // Read the data from the serial port
    read(this->serial_port, read_buf, size);    
}

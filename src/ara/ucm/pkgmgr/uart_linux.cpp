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
    // open config file to get the device path
    std::ifstream config_file("./config.conf");
    std::string line;
    std::string device_path;
    if (config_file.is_open())
    {
        while (getline(config_file, line))
        {
            if (line.find("device_path") != std::string::npos)
            {
                device_path = line.substr(line.find("=") + 1);
            }
        }
        config_file.close();
    }
    else
    {
        std::cout << "Unable to open config file" << std::endl;
    }
    if(device_path.empty())
    {
        std::cout << "Device path is empty" << std::endl;
        device_path = "/dev/ttyACM1";
    }
    this->serial_port = open(device_path.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

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

    // configure uart port to communicate with uart in tiva C 
    // set baud rate to 9600
    cfsetospeed(&tty, (speed_t)B9600);
    cfsetispeed(&tty, (speed_t)B9600);
    // 8N1
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication
    tty.c_cflag &= ~CSIZE;  // Clear size field
    tty.c_cflag |= CS8;     // Set 8 data bits
    // disable hardware flow control
    tty.c_cflag &= ~CRTSCTS;
    // disable software flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    // disable hardware flow control
    tty.c_cflag &= ~HUPCL;
    // disable software flow control
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    // disable canonical mode
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // read minimum number of characters
    tty.c_cc[VMIN] = 1;
    // read timeout value
    tty.c_cc[VTIME] = 0;
    // disable output processing
    tty.c_oflag &= ~OPOST;
    // disable input processing
    tty.c_iflag &= ~(ICRNL | INLCR | IGNCR | ISTRIP | IXON);
    // disable output processing
    tty.c_oflag &= ~OPOST;

    // Set the new options for the port...
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        exit(1);
        return ;
    }





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

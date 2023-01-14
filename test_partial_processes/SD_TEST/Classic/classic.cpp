#include "iostream"
#include "ara/com/ipc/server/socket_Server.h"
#include "vector"
#include <bits/stdc++.h>


void SaveBlock(const char *filename, std::vector<uint8_t> &data_block)
{
    std::ofstream outfile(filename, std::ios::out | std::ofstream::app);
    outfile.write((const char *)&data_block[0], data_block.size());
    outfile.close();
}

#define CLASSIC_PORT 3600
int main(void)
{
    CServer server_main_socket(SOCK_STREAM);
    server_main_socket.OpenSocket(CLASSIC_PORT);
    server_main_socket.BindServer();
    server_main_socket.ListenServer(5);
    Socket Sclient = server_main_socket.AcceptServer();
    int temp_size;
    std::vector<uint8_t> Temp_data2 ;
    Sclient.Receive(&temp_size, sizeof(temp_size));
    std::cout << "temp_size= " << temp_size << std::endl;
    Temp_data2.resize(temp_size);
    Sclient.Receive(&Temp_data2[0], temp_size);

    SaveBlock("/home/bassant/Documents/GitHub/Adaptive/test_partial_processes/SD_TEST/Classic/classic.zip", Temp_data2);
    Sclient.CloseSocket();
    server_main_socket.CloseSocket();
    while(1){}
}
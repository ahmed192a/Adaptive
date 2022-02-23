#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#include "proxy.hpp"
#include "data.h"

using namespace std;



int main(int argc, char **argv)
{


    proxy proxy_client;

    proxy_client.Create(atoi(argv[1]), 32);

    proxy_client.Method();

   return 0;
}
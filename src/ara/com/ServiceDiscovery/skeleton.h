/**
 * @file skeleton.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../ipc/server/socket_Server.h"
#include <unistd.h>
#include "functional"
#include <iostream>
#include <string.h>
#include "data.h"
class skeleton 
{
private:
    /* data */
    int portNumber;
    int service_id;
    int service_descovery_port_number;
    CServer s1;
    struct sockaddr_in  cliaddr;
    
public:

    skeleton(int portNumber, int sd, int service_id);
    ~skeleton();
    void start_service();
    void method_dispatch(const struct C_Info& message, CServer& cserver);
    void StopOfferService();
};











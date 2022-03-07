/**
 * @file data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DATA_H
#define DATA_H

// SD: service discovery 
struct SD_data{
    int service_id;
    int process_id;
    int port_number;
    bool message_type; // offer service or stop offer service
};

#endif
#ifndef DATA_H
#define DATA_H

// SD: service discovery 
struct SD_data{
    int service_id;
    int process_id;
    int port_number;
    bool message_type;
};

struct event_info{
    int process_id;
    char event_name[30];
};
#endif
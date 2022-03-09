/**
 * @file event.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_
#define ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

#include "ara/com/proxy_skeleton/proxy/service_proxy.hpp"
namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace proxy
            {

                template <typename T>
                class Event
                {
                public:
                    Event(
                    ServiceProxy *service,
                    std::string name) 
                    :   Cient_Server_connection(SOCK_STREAM),
                        m_service{service},
                        m_name{name}
                    {                        
                    }
                    ~Event(){}
                    void Subscribe(char event_name[])
                    {
                        // We first use signals to inform the sever that we wanna subscribe to an event
                        union sigval sigval;
                        sigval.sival_int = 2;
                        printf("sender: sending %d to PID %d\n", sigval.sival_int, m_service->server_handle.process_id);

                        // here we're sending number 2 to the server
                        sigqueue(m_service->server_handle.process_id, SIGUSR1, sigval);

                        // then here we open a socket between server and client
                        
                        Cient_Server_connection.OpenSocket();
                        Cient_Server_connection.GetHost("127.0.0.1", m_service->server_handle.port_number);
                        Cient_Server_connection.ClientConnect();

                        // here we're sending the event_name
                        event_info e1;
                        e1.process_id = getpid();
                        strcpy(e1.event_name, event_name);
                        Cient_Server_connection.ClientWrite((void *)&e1, sizeof(e1));
                        Cient_Server_connection.CloseSocket();
                    }


                    void handlecall(T msg_data){
                        event_data= msg_data;
                    }
                    T get_value()
                    {
                        return event_data;
                    }

                private:
                    ServiceProxy *m_service;
                    std::string m_name;
                    CClient Cient_Server_connection;
                    T event_data;

                }; // Event
            }      // proxy
        }          // proxy_skeleton
    }              // com
} // ara

#endif // ARA_COM_PROXY_SKELETON_PROXY_EVENT_H_

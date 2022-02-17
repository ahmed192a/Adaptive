#ifndef ARA_SM_POWERMODE_H
#define ARA_SM_POWERMODE_H

#include  <iostream>
#include <map>
namespace ara
{
namespace sm{
class PowerMode {
 public:
    //**************************TYPE DEFINITIONS AND MEMBERS*************************//
    //Reply message from Process, which received PowerModeMessage from State Management//

    enum PowerModeRespMsg{
        Done,  //requested mode sucessfully reached//
        Failed,//requested mode not reached.//
        Busy,  //cant process requested mode e.g. important things are ongoing//
        Notsupported //requested mode not supported//

    };
    using PowerModeMsg = std::string; //Message to all running Processes in the system to indicate a request for a PowerMode switch//
    PowerModeMsg On="On"; //normal operation//
    PowerModeMsg Off="Off";  //persist data preparation for shutdown.//
    PowerModeMsg Suspend="Suspend";//prepare for suspend2ram.//
    /*1.
     *Method: message
     *Description: Message to all running Processes in the system to indicate a request for a PowerMode switch
     *Parameter: msg
     *Description: sends PowerModeMsg
     *Type: PowerModeMsg
     *Direction: OUT
     */
    void message (PowerMode::PowerModeMsg &msg) noexcept;

    /*2.
     *Method: event
     *Description: All Processes which got a PowerMode request sends this as answer to State Management.
     *Parameter: respMsg
     *Description: ResponseMessage from a Processes which received PowerMode request from State Management
     *Type: PowerModeRespMsg
     *Direction: OUT
     */
     void event (PowerMode::PowerModeRespMsg &respMsg) noexcept;
            };


       }
}
#endif

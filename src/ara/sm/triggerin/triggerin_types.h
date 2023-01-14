#ifndef SM_TRIGGERIN_TYPES_H_
#define SM_TRIGGERIN_TYPES_H_

namespace ara
{
    namespace sm
    {
        namespace triggerin
        {
            using TriggerInType = int;
            // define enum for ucm states
            typedef enum  {
                UCM_STATE_UNKNOWN,
                UCM_STATE_INITIALIZED,
                UCM_STATE_STARTED,
                UCM_STATE_STOPPED,
                UCM_STATE_ERROR
            } UCM_State;
            enum  OTA_State {
                OTA_STATE_UNKNOWN,
                OTA_STATE_INITIALIZED,
                OTA_STATE_STARTED,
                OTA_STATE_STOPPED,
                OTA_STATE_ERROR
            };
        }
    }
}

#endif 
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
            enum class UCM_State {
                UCM_STATE_UNKNOWN,
                UCM_STATE_INITIALIZED,
                UCM_STATE_STARTED,
                UCM_STATE_STOPPED,
                UCM_STATE_ERROR
            };
        }
    }
}

#endif 
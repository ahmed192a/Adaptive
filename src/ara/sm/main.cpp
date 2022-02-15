#include "state_manager.h"

int main(void)
{
    // creating an instance from the state manager
    ara::sm::StateManager sm;

    // initializing the state manager with the needed information about the platform
    ara::sm::StateManager::init();

    return 0;
}




    // while(1) {
    //     //  Ex:  (Will not be defined here)
    //     std::string Trigger = ""; // (should be initialized out of the loop)
    //     std::string Notifier = "";
    //     //  read the Trigger each loop turn and this trigger should clarify
    //     //  - to which function_group if belings
    //     //  - to which state the transition requests
        
    //     if(Trigger != "") {
    //         Trigger = "";
    //         // convert trigger to instance of function_group_state
    //         FunctionGroupState state();
    //         manager.SetState(state); // assuming that it succeded 
            
    //         // changing the current state in the FunctionGroup vector
    //         // search in the vector for the function group
    //         // change the current state attribute

    //         // notifuing the application with the transfered state
    //         // notifing happens thought the notifier
    //         Notifier = "test-notification";

    //     }
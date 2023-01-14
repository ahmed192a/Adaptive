#include "ara/sm/update_request.h"
#include "ara/sm/state_manager.h"

using namespace ara::sm;

// initially there is no update sessions executing
bool UpdateRequest::activeSession = false;


Result UpdateRequest::ResetMachine(void) {
    // resetting the machine will be rejected in case
    // - There is an active session
    // - The RequestUpdateSession() was not called successfully
    if((activeSession == true) || (status == UpdateStatus::unactive)) {
        //return errorDomains::kRejected;
    }
    else {
       // ara::exec::FunctionGroupState state;    
        
        //StateManager::EM.SetState();
        // StateManager::MachineFG.state = "Restart";
    }

}

Result UpdateRequest::StopUpdateSession(void) {
    if(status == UpdateStatus::unactive) {
        // RequestUpdateSession() was not called successfully
        //return errorDomains::kRejected;
    } 
    else 
    {
        // closing the active session
        activeSession = false;
        status = UpdateStatus::unactive;
        //return;        
    }
}

Result UpdateRequest::RequestUpdateSession(void) {
    if(activeSession == 1) {
        // There is another active update session
        //return errorDomains::kNotAllowedMultipleUpdateSessions; // error code
    }

    // There is no active session currently
    // if( StateManager::MachineFG.state != "Running") {
    //     // The Machine current status do not accept session activation
    //     //return errorDomains::kRejected;
    // }
    // else {
    //     // accepted the update request and openned an update session
    //     activeSession = true;
    //     status = UpdateStatus::acquired;
    //     //return;
    // }       
}

errorDomains UpdateRequest::PrepareUpdate(UpdateRequest::FunctionGroupListType functionGroupList) {
    
    if (status == UpdateStatus::acquired) {
            for(int i = 0; i < functionGroupList.size(); i++) {
                
                
                //functionGroupList[i]=StateManager::EM.SetState(); // setting the states to "off" state 
               }           

    }
    else {
        return errorDomains::kRejected;
    }

}


Result UpdateRequest::VerifyUpdate(UpdateRequest::FunctionGroupListType functionGroupList) {


}

Result UpdateRequest::PrepareRollback(UpdateRequest::FunctionGroupListType functionGroupList) {


}

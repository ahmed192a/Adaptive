#include "ara/sm/update_request.hpp"
// #include "ara/sm/state_manager.hpp"

using namespace ara::sm;

// initially there is no update sessions executing
bool UpdateRequest::activeSession = false;


std::future<update_request::ResetMachineOutput> UpdateRequest::ResetMachine() {
    
    std::future<update_request::ResetMachineOutput> f = std::async( [&]() {

        // resetting the machine will be rejected in case
        //      - There is an active session
        //      - The RequestUpdateSession() was not called successfully
        // if((activeSession == true) || (status == UpdateStatus::unactive)) {
            update_request::ResetMachineOutput result;
            result.status = false; // false for carrying an error
            result.error = errorDomains::kRejected;
            return result;
        // }
        // else {
        // // ara::exec::FunctionGroupState state;    
            
        //     //StateManager::EM.SetState();
        //     // StateManager::MachineFG.state = "Restart";
        // }

    });

    return f; // return the std::future result
}

std::future<update_request::StopUpdateSessionOutput> UpdateRequest::StopUpdateSession() {
   
    std::future<update_request::StopUpdateSessionOutput> f = std::async( [&]() {

        /** request refused **/
        if(status == UpdateStatus::unactive) {
            // StartUpdateSession() was not called successfully
            update_request::StopUpdateSessionOutput result;
            result.status = false; // false for carrying an error
            result.error = errorDomains::kRejected;
            return result;
        }

        /** request accepted **/

        // closing the active session
        activeSession = false;
        status = UpdateStatus::unactive;
        
        update_request::StopUpdateSessionOutput result;
        result.status = true; // true for accepting the request
        return result;       

    });

    return f; // return the std::future result

}

std::future<update_request::StartUpdateSessionOutput> UpdateRequest::StartUpdateSession() {

    std::future<update_request::StartUpdateSessionOutput> f = std::async( [&]() {

        /** request refused **/
        if(activeSession == true) {
            // There is another active update session
            update_request::StartUpdateSessionOutput result;
            result.status = false; // false for carrying an error
            result.error = errorDomains::kRejected;
            return result;
        }

        // There is no active session currently
        // if( StateManager::MachineFG.state != "Running") {
        //     // The Machine current status do not accept session activation
        //     //return errorDomains::kRejected;
        // }


        /** request accepted **/
        // accepted the update request and openned an update session
        activeSession = true;
        status = UpdateStatus::acquired;
        
        update_request::StartUpdateSessionOutput result;
        result.status = true; // true for accepting the request
        return result;

    });

    return f; // return the std::future result
}

std::future<update_request::PrepareUpdateOutput> UpdateRequest::PrepareUpdate(FunctionGroupListType functionGroupList) {
    
    std::future<update_request::PrepareUpdateOutput> f = std::async( [&, functionGroupList]() {
        
        /** request refused **/
        if (status != UpdateStatus::acquired) {
            update_request::PrepareUpdateOutput result;
            result.status = false; // false for carrying an error
            result.error = errorDomains::kRejected;
            return result;
        }

        /** request accepted **/
        for(int i = 0; i < functionGroupList.size(); i++) {
                
            //functionGroupList[i]=StateManager::EM.SetState(); // setting the states to "off" state 
        
        } 

    });

    return f; // return the std::future result



}


std::future<update_request::VerifyUpdateOutput> UpdateRequest::VerifyUpdate(FunctionGroupListType functionGroupList) {
    std::future<update_request::VerifyUpdateOutput> f = std::async( [&, functionGroupList]() {
        
        // dummy implementation
        update_request::VerifyUpdateOutput result;
        return result;
    

    });

    return f; // return the std::future result
}




std::future<update_request::PrepareRollbackOutput> UpdateRequest::PrepareRollback(FunctionGroupListType functionGroupList) {

    std::future<update_request::PrepareRollbackOutput> f = std::async( [&, functionGroupList]() {

        // dummy implementation
        update_request::PrepareRollbackOutput result;
        return result;

        
    });

    return f; // return the std::future result

}

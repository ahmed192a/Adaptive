#ifndef ARA_SM_UPDATE_REQUEST_H
#define ARA_SM_UPDATE_REQUEST_H

//#include <cstdint>
#include <string>
#include <vector>
#include "sm_error_domain.h"
#include "result.h"

namespace ara {
    namespace sm {

        using Result = ara::core::Result<void>;
        
        enum class UpdateStatus{
            unactive, // initial state or after calling StopUpdateSession()
            acquired, // RequestUpdateSession() called and succeeded
            prepared, // PrepareUpdate() called and succeeded
            verified  // VerifyUpdate() called and succeeded
        };

    
        class UpdateRequest
        {
        public:

            static bool activeSession;
            UpdateStatus status = UpdateStatus::unactive;


            /** Type definitions **/

            // [SWS_SM_91019]
            /*
             * Name        : FunctionGroupNameType
             * Kind        : STRING
             * Description : full qualified FunctionGroup shortName.
             */
            using FunctionGroupNameType = std::string;


            // [SWS_SM_91018]
            /*
             * Name        : FunctionGroupListType
             * Kind        : VECTOR
             * Subelements : FunctionGroupNameType
             * Description : A list of FunctionGroups.
             */
            using FunctionGroupListType = std::vector<FunctionGroupNameType>;


            /** Provided Service Interfaces **/

            /*
             * Method             : ResetMachine
             * Description        : Requests a reset of the machine. Before the reset is performed all information within the machine shall
             *                      be persisted. Request will be rejected when RequestUpdateSession was not called successfully before.
             * FireAndForget      : false
             * Application Errors : kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             */
            Result ResetMachine(void);


            /*
             * Method             : StopUpdateSession
             * Description        : Has to be called by Update And Configuration Management once the update is finished to let State
                                    Management know that the update is done and the Machine is in a stable state. Request will be rejected
                                    when RequestUpdateSession was not called successfully before.
             * FireAndForget      : false
             * Application Errors : kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             */

            Result StopUpdateSession(void);


            /*
             * Method             : RequestUpdateSession
             * Description        : Has to be called by Update And Configuration Management once it has to start interaction with State
                                    Management. State Management might decline this request when machine is not in a state to be
                                    updated.
             * FireAndForget      : false
             * Application Errors : kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             *                    : kNotAllowedMultipleUpdateSessions (Request for new session was rejected as only single active (update) session is allowed)
             */

            Result RequestUpdateSession(void);


            /*
             * Method             : PrepareUpdate
             * Description        : Has to be called by Update And Configuration Management after State Management allowed to update.
                                    State Management will decline this request when RequestUpdateSession was not called before
                                    successfully.
             * FireAndForget      : false
             * Parameter          : - Name        : functionGroupList
                                      Description : The list of FunctionGroups within the SoftwareCluster to be prepared to be updated.
                                      Type        : functionGroupListType
                                      Direction   : IN

             * Application Errors : - kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             *                      - kPrepareFailed (Preparation step of update failed.)
             */


            errorDomains PrepareUpdate(UpdateRequest::FunctionGroupListType functionGroupList);


            /*
             * Method             : VerifyUpdate
             * Description        : Has to be called by Update And Configuration Management after State Management allowed to update
                                    and the update preparation has been done. State Management will decline this request when Prepare
                                    Update was not called before successfully.
             * FireAndForget      : false
             * Parameter          : - Name        : functionGroupList
                                      Description : The list of FunctionGroups within the SoftwareCluster to be verified
                                      Type        : functionGroupListType
                                      Direction   : IN

             * Application Errors : - kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             *                      - kVerifyFailed (Verification step of update failed.)
             */

            Result VerifyUpdate(UpdateRequest::FunctionGroupListType functionGroupList);


            /*
             * Method             : PrepareRollback
             * Description        : Has to be called by Update And Configuration Management after State Management allowed to update.
             * FireAndForget      : false
             * Parameter          : - Name        : functionGroupList
                                      Description : The list of FunctionGroups within the SoftwareCluster to be prepared to roll back.
                                      Type        : functionGroupListType
                                      Direction   : IN

             * Application Errors : - kRejected  (Requested operation was rejected due to State Managements/machines internal state)
             *                      - kRollbackFailed (Rollback step of update failed.)
             */

            Result PrepareRollback(UpdateRequest::FunctionGroupListType functionGroupList);

        };

    } // namespace sm
} // namespace ara

#endif // ARA_SM_UPDATE_REQUEST_H

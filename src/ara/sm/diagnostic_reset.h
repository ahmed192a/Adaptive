#ifndef ARA_SM_DIAGNOSTIC_RESET_H
#define ARA_SM_DIAGNOSTIC_RESET_H

#include <iostream>
#include <map>


namespace ara
{
    namespace sm
    {
        class DiagnosticReset
        {
        public:
            //**************************TYPE DEFINITIONS AND MEMBERS*************************//
            //1.Reply message from Process, which received DiagnosticResetMessage from State Management
            enum class DiagnosticResetRespMsg{
                Done,         //reset performed sucessfully
                Failed,       //reset not sucessfully performed
                Busy,         //can’t perform reset(e.g. important things are ongoing)
                NotSupported  //reset not supported
            };


            //2.Message to all Processes(in a SoftwareCluster) to indicate a request to perform Diagnostic Reset
            using DiagnosticResetMsg = std::string;

            //2.1 Message to all Processes(in a SoftwareCluster) to indicate a request to perform Diagnostic SoftReset
            DiagnosticResetMsg SoftReset = "SoftReset"; //normal operation

            //3. to represent if there is active session
            static bool activeSession; 

            //***********************************METHODS************************************//

            //Disable copy constructor
            DiagnosticReset(DiagnosticReset &) = delete;

            /*1.
             *Method: message
             *Description: sends DiagnosticResetMsg Type definition to all Processes in a SoftwareCluster.
             *Parameter: msg
                 *Description: Message to all running Processes in the SoftwareCluster to indicate a request to perform softReset.
                 *Type: DiagnosticResetMsg
                 *Direction: OUT
             */
            void message (DiagnosticReset::DiagnosticResetMsg &msg) noexcept;


            /*2.
             *Method: event
             *Description: All Processes which got a DiagnosticReset request sends this as answer to State Management.
             *Parameter: respMsg
                 *Description: ResponseMessage from a Processes which received DiagnosticReset request from State Management.
                 *Type: DiagnosticResetRespMsg
                 *Direction: OUT
             */
            void event (DiagnosticReset::DiagnosticResetRespMsg &respMsg) noexcept;


        };


    }

}

#endif // ARA_SM_DIAGNOSTIC_RESET_H

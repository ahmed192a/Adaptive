#ifndef _DIAGNOSTIC_RESET_RETURN_TYPES_H_
#define _DIAGNOSTIC_RESET_RETURN_TYPES_H_
#include <string>
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
#endif
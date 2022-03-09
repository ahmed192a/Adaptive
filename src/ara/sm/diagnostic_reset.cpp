#include "ara/sm/diagnostic_reset.hpp"

using namespace ara::sm;

bool DiagnosticReset::activeSession = false;

void DiagnosticReset::message(DiagnosticReset::DiagnosticResetMsg &msg) noexcept
{
    // use methods in the communication management skeleton to send to the clients the soft response message..
    msg = SoftReset;
}

void DiagnosticReset::event(DiagnosticReset::DiagnosticResetRespMsg &respMsg) noexcept
{
    // use methods in the communication management skeleton to receive messages from the clients received the soft response message..
    if (respMsg == DiagnosticResetRespMsg::Done)
    {
        // Do something..
    }
    else if (respMsg == DiagnosticResetRespMsg::Failed)
    {
        // Do something..
    }
    else if (respMsg == DiagnosticResetRespMsg::Busy)
    {
        // Do something..
    }
    else if (respMsg == DiagnosticResetRespMsg::NotSupported)
    {
        // Do something..
    }
}

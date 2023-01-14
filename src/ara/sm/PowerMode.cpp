#include "ara/sm/powermode.h"
using namespace ara::sm;
void PowerMode::message(PowerMode::PowerModeMsg &msg) noexcept
{
    msg = On;
    msg = Off;
    msg = Suspend;
}

void PowerMode::event(PowerMode::PowerModeRespMsg &respMsg) noexcept
{

    if (respMsg == PowerModeRespMsg::Done)
    {
        // Do something..
    }
    else if (respMsg == PowerModeRespMsg::Failed)
    {
        // Do something..
    }
    else if (respMsg == PowerModeRespMsg::Busy)
    {
        // Do something..
    }
    else if (respMsg == PowerModeRespMsg::Notsupported)
    {
        // Do something..
    }
}

#ifndef SM_TYPES_H_
#define SM_TYPES_H_

#include "string"
namespace ara
{
    namespace sm
    {
        namespace powermode
        {
            using PowerModeMsg = std::string;
            enum PowerModeRespMsg
            {
                Done,        // requested mode sucessfully reached//
                Failed,      // requested mode not reached.//
                Busy,        // cant process requested mode e.g. important things are ongoing//
                Notsupported // requested mode not supported//

            };
        }
    }
}

#endif
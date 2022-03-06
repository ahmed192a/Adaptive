#ifndef ARA_COM_SAMPLE_RADAR_COMMON_H
#define ARA_COM_SAMPLE_RADAR_COMMON_H
#include "impl_adjustreturntype.h"

namespace ara
{
    namespace com
    {
        namespace sample
        {
            class Radar
            {
            public:
                struct Adjust
                {
                    Adjust() {}

                    ::ara::com::sample::AdjustReturnType result;
                    
                };
            };

        } // namespace sample

    } // namespace com

} // namespace ara

#endif //ARA_COM_SAMPLE_RADAR_COMMON_H
/**
 * @file ucm_return_types.h
 * @author your name (you@domain.com)
 * @brief UCM Return Types Definitions
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef RETURN_TYPES_H_
#define RETURN_TYPES_H_

#include "ucm_types.hpp"

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace PackageManagement
            {

                struct TransferStartOutput
                {
                    TransferIdType id;
                    uint32_t BlockSize;
                };

                struct TransferDataOutput
                {
                };

                struct TransferExitOutput
                {
                };

                struct ActivateOutput
                {
                };

                struct CancelOutput
                {
                };

                struct DeleteTransferOutput
                {
                };

                struct FinishOutput
                {
                };

                struct GetSwProcessProgressOutput
                {
                };

                struct ProcessSwPackageOutput
                {
                };

                struct RevertProcessedSwPackagesOutput
                {
                };

                struct RollbackOutput
                {
                };
            }
        }
    } // namespace ucm
} // namespace ara

#endif
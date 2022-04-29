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
#include "ucm_error.hpp"  

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
                    int aya;
                };

                struct TransferExitOutput
                {
                    int error = 0;
                };

                struct ActivateOutput
                {
                    int error = 0;
                };

                struct CancelOutput
                {
                    int error = 0;
                };

                struct DeleteTransferOutput
                {
                    int error = 0;
                };

                struct FinishOutput
                {
                    int error = 0;
                };

                struct GetSwPackagesOutput
                {
                   SwPackageInfoVectorType Packages;
                };

                struct GetSwProcessProgressOutput
                {
                    uint8_t progress;
                };

                struct GetSwClusterInfoOutput
                {
                    SwClusterInfoVectorType SwInfo;
                };
                

                struct ProcessSwPackageOutput
                {
                    int error = 0;
                };

                struct RevertProcessedSwPackagesOutput
                {
                    int error = 0;
                };

                struct RollbackOutput
                {
                    int error = 0;
                };

                struct GetSwClusterDescriptionOutput
                {
                    SwDescVectorType SoftwareClusterDescriptions;
                };

                struct GetSwClusterChangeInfoOutput
                {
                    SwClusterInfoVectorType SwInfo;
                };

                struct GetIdOutput
                {
                    UCMIdentifierType id;
                };

                struct GetHistoryOutput
                {
                    GetHistoryVectorType history;
                };
                
                
            }
        }
    } // namespace ucm
} // namespace ara

#endif
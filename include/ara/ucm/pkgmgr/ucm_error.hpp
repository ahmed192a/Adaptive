/**
 * @file ucm_error.h
 * @brief UCM Error Domain
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ARA_UCM_UCM_ERROR_H_
#define ARA_UCM_UCM_ERROR_H_
namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace PackageManagement
            {

                enum UCMErrorDomain
                {
                    NewCampaignDisabled = 31,
                    UnexpectedPackage = 32,
                    IncorrectBlock = 2,
                    IncorrectBlockSize = 30,
                    AuthenticationFailed = 8,
                    BlockInconsistent = 25,
                    CancelFailed = 16,
                    IncompatibleDelta = 29,
                    IncompatiblePackageVersion = 24,
                    IncorrectSize = 3,
                    InsufficientComputationPower = 28,
                    InsufficientData = 6,
                    InsufficientMemory = 1,
                    InvalidPackageManifest = 13,
                    InvalidTransferId = 4,
                    MissingDependencies = 21,
                    NotAbleToRevertPackages = 15,
                    NotAbleToRollback = 18,
                    OldVersion = 9,
                    OperationNotPermitted = 5,
                    PackageInconsistent = 7,
                    ProcessSwPackageCancelled = 22,
                    ProcessedSoftwarePackageInconsistent = 23,
                    ServiceBusy = 12,
                    TransferInterrupted = 26,
                    UpdateSessionRejected = 33,
                    PreActivationFailed = 19,
                    VerificationFailed = 27
                };
            }
        }
    } // namespace ucm

} // namespace ara

#endif
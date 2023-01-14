/**
 * @file ucm_types.h
 * @brief UCM Types Definitions
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ARA_UCM_UCM_TYPES_H_
#define ARA_UCM_UCM_TYPES_H_
#include <string>
#include <vector>
#include <array>
namespace ara
{
       namespace ucm
       {
              namespace pkgmgr
              {
                     namespace PackageManagement
                     {
                            /**
                             * @brief UCM Module Instantiation Identifier.
                             * 
                             */
                            using UCMIdentifierType = std::string;
                            /**
                             * @brief Represents a handle identifier used to reference a particular transfer request.
                             * 
                             */
                            using TransferIdType = std::array<uint8_t, 16>;
                            /**
                             * @brief SoftwareCluster or SoftwarePackage shortName attribute inherited from referrable meta Class.
                             * 
                             */
                            using SwNameType = std::string;
                            /**
                             * @brief Represents a dynamic size array of Software Cluster names.
                             * 
                             */
                            using SwNameVectorType = std::vector<SwNameType>;

                            /**
                             * @brief Primitive type representing SoftwareCluster (SoftwarePackage) version.
                             * 
                             */
                            using StrongRevisionLabelString = std::string;
                            /**
                             * @brief Represents the information of a Software Package (Software Cluster) name and version.
                             * 
                             */
                            struct SwNameVersionType
                            {
                                   SwNameType Name;
                                   StrongRevisionLabelString Version;
                            };
                            /**
                             * @brief Represents a dynamic size array of Software Name and Version
                             * 
                             */
                            using SwNameVersionVectorType = std::vector<SwNameVersionType>;

                            /**
                             * @brief Byte vector representing raw data.
                             * 
                             */
                             using ByteVectorType = std::vector<uint8_t>;

                            /**
                             * @brief Represents the state of a Software Package on the Platform.
                             * Range/Symbol         Limit       Description
                             * kTransferring        0x00        Software package is being transferred, i.e. not completely received.
                             * kTransferred         0x01        Software package is completely transferred and ready to be processed.
                             * kProcessing          0x02        Software package is currently being processed.
                             * kProcessed           0x03        Software package processing finished.
                             * kProcessingStream    0x04        Software package is being processed from a stream.
                             */
                            using SwPackageStateType = uint8_t ;
                            /**
                            * @brief Represents the information of a Software Package.
                            *   Name                       SwNameType  
                            *   Version                    StrongRevisionLabelString
                            *   TransferID                 TransferIdType
                            *   ConsecutiveBytesReceived   uint64_t
                            *   ConsecutiveBlocksReceived  uint64_t
                            *   State                      SwPackageStateType
                            * 
                            */
                            struct SwPackageInfoType
                            {
                                   SwNameType Name;
                                   StrongRevisionLabelString Version;
                                   TransferIdType TransferID;
                                   uint64_t ConsecutiveBytesReceived;
                                   uint64_t ConsecutiveBlocksReceived;
                                   SwPackageStateType State;
                            };
                             /**
                             * @brief Represents a dynamic size array of Software Packages
                             * 
                             */
                            using SwPackageInfoVectorType = std::vector<SwPackageInfoType>;
                            /**
                             * @brief Contains general information related to SoftwareCluster that can be used by Vehicle Driver Application or Human Interface.
                             * 
                             */
                            struct SwDescType
                            {
                                   SwNameType Name;
                                   StrongRevisionLabelString Version;
                                   std::string TypeApproval;
                                   std::string License;
                                   std::string ReleaseNotes;
                                   uint64_t Size;
                            };
                            /**
                             * @brief Represents a dynamic size array of SoftwareCluster description
                             * 
                             */
                            using SwDescVectorType = std::vector<SwDescType>;
                            /**
                             * @brief Represents the state of a SoftwareCluster on the adaptive platform.
                             * Range/Symbol     Limit   Description
                             * kPresent         0x00    State of a SoftwareCluster that is installed on the adaptive platform and installation has finished.
                             * kAdded           0x01    State of a SoftwareCluster that has been newly installed.
                             * kUpdated         0x02    State of a SoftwareCluster that has been updated.
                             * kRemoved         0x03    State of a SoftwareCluster that has been removed.
                             */
                             using SwClusterStateType = uint8_t ;
                            /**
                             * @brief Represents the information of a SoftwareCluster.
                             * 
                             */
                            struct SwClusterInfoType
                            {
                                   SwNameType Name;
                                   StrongRevisionLabelString Version;
                                   SwClusterStateType State;
                            };
                            /**
                             * @brief Represents a dynamic size array of SoftwareClusters
                             * 
                             */
                            using SwClusterInfoVectorType = std::vector<SwClusterInfoType>;
                             /**
                             * @brief Represents the state of UCM.
                             * 
                             *  Range/Symbol     Limit   Description
                             *  kIdle            0x00    UCM is ready to start processing if software packages are present.
                             *  kReady           0x01    UCM has processed one or several packages and waits for additional packages, activation or reversion of processed packages.
                             *  kProcessing      0x02    UCM is currently in the middle of processing a Software Package, i.e. a client has called ProcessSwPackage.
                             *  kActivating      0x03    UCM is performing the dependency check and preparing the activation of the processed Software packages.
                             *  kActivated       0x04    Software changes introduced with processed Software Packages has been activated and executed.
                             *  kRollingBack     0x05    UCM is reverting changes introduced with processed packages.
                             *  kRolledBack      0x06    Software changes introduced with processed Software Packages has been deactivated and original software is executed.
                             *  kCleaningUp      0x07    Making sure that the system is in a clean state.
                             *  kVerifying       0x08    UCM (via State Management) is checking that the processed packages have been properly restarted.
                             */
                            using PackageManagerStatusType = uint8_t;
                            /**
                             * @brief Represents the UCM action.
                             * Range/Symbol     Limit   Description
                             * kUpdate          0x00    Update of a SoftwareCluster.
                             * kInstall         0x01    Installation of a new SoftwareCluster.
                             * kRemove          0x02    Removal of a SoftwareCluster.
                             */
                            using ActionType = uint8_t &;
                            /**
                             * @brief Represents the result of UCM action.
                             * Range/Symbol     Limit   Description
                             * kSuccessfull     0x00    UCM’s action was successful.
                             * kFailed          0x01    UCM’s action failed.
                             */
                             using ResultType = uint8_t &;
                            /**
                             * @brief Time refers to the activation time of the software cluster. It is represented in milliseconds
                             *          of UCM’s action resolution since 01.01.1970 (UTC).
                             * 
                             */
                            struct GetHistoryType
                            {
                            uint64_t Time;
                            SwNameType Name;
                            StrongRevisionLabelString Version;
                            ActionType Action;
                            ResultType Resolution;
                            };
                            /**
                             * @brief Represents a list of UCM actions
                             * 
                             */
                            using GetHistoryVectorType = std::vector<GetHistoryType>;
                            /**
                             * @brief History of an UCM
                             * 
                             */
                            struct HistoryVectorType
                            {
                            UCMIdentifierType id;
                            GetHistoryVectorType HistoryVector;
                            };

                            /**
                             * @brief UCM Software Package step at which error occured
                             * Range/Symbol     Limit       Description
                             * kTransfer        0x00        Software Package transfer
                             * kProcess         0x01        Software Package processing
                             * kPreActivate     0x02        Software Cluster pre activation
                             * kVerify          0x03        Software Cluster verification
                             */
                            using SoftwarePackageStepType = uint8_t &;
                            /**
                             * @brief UCM Error
                             * 
                             */
                            struct UCMStepErrorType
                            {
                            UCMIdentifierType id;
                            SoftwarePackageStepType SoftwarePackageStep;
                            uint8_t ReturnedError;
                            };

                            /**
                             * @brief Campaign failure
                             * Range/Symbol                                 Limit       Description 
                             * kUCMError                                    0x01        UCM error 
                             * kInvalidVehiclePackageManifest               0x02        Vehicle Package manifest is invalid
                             * kSubordinateNotAvailableOnTheNetwork         0x03        UCM subordinate not reachable
                             * kVehicleStateManagerCommunicationError       0x04        Communication error with Vehicle State Manager
                             * kVehicleDriverInterfaceCommunicationError    0x05        Communication error with Vehicle Driver Interface
                             * kCampaignCancelled                           0x06        Campaign was cancelled
                             * 
                             */
                            using CampaignFailureType = uint8_t &;
                            /**
                             * @brief Campaign Error
                             * 
                             */
                            struct CampaignErrorType
                            {
                            CampaignFailureType CampaignFailure;
                            UCMStepErrorType UCMStepError;
                            };

                            /**
                             * @brief Campaign history
                             * 
                             */
                            struct CampaignHistoryType
                            {
                            CampaignErrorType CampaignError;
                            HistoryVectorType HistoryVector;
                            };
                            /**
                             * @brief Represents the status of Campaign.
                             * Range/Symbol                     Limit       Description
                             * kIdle                            0x00        UCM Master is ready to start a software update campaign.
                             * kSyncing                         0x01        UCM master is providing the list of installed SWCLs (GetSwCluster Info) or computing the list of SWCLs to install (SwPackageInventory).
                             * kVehiclePackageTransferring      0x02        A vehicle package is being transferred to UCM Master.
                             * kSoftwarePackage_Transferring    0x03        UCM Master is transferring software packages to the UCM subordinates.
                             * kProcessing                      0x04        The processing of software packages on UCM subordinates is ongoing. The transferring of software packages may still occur.
                             * kActivating                      0x05        The activation of SWCLs on UCM subordinates is ongoing.
                             * kVehicleChecking                 0x06        UCM Master is performing post-activation checks (OEM specific).
                             * kCancelling                      0x07        UCM Master is rolling-back the activated SWCLs on the UCM subordinates.
                             */
                            using CampaignStateType = uint8_t &;
                            /**
                             * @brief Represents the state of an update from OTA Client perspective.
                             * Range/Symbol     Limit   Description
                             * kIdle            0x00    UCM Master is ready to start a software update campaign.
                             * kTransferring    0x01    Vehicle or Software Packages are being transferred.
                             * kUpdating        0x02    Software Clusters are being updated in the vehicle.
                             * kCancelling      0x03    An error occurred, campaign is being cancelled, reverting changes.
                             */
                            using TransferStateType = uint8_t &;
                            /**
                             * @brief The type of the Safety Policy.
                             * 
                             */
                            using SafetyPolicyType = std::string;
                     }
              }
       } // namespace ucm

} // namespace ara

#endif
/**
 * @file packagemanagement_proxy.h
 * @author Sarah Mohamed
 * @brief Proxy(service requester) file for ucm::pkgmgr service interface
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_

#include "inc.h"

namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace proxy
            {
                namespace events
                {

                }
                namespace fields
                {
                    /**
                     * @brief The current status of UCM.
                     * 
                     * @todo update typedef:
                     *       field: CurrentStatus of type: PackageManagementStatusType
                     * @note int de ay haga mo2ktn
                     * 
                     */
                    using CurrentStatus = ara::com::proxy_skeleton::skeleton::FieldType<::ara::ucm::PackageManagerStatusType,true,true,false>::type;
                }
                namespace methods
                {
                    /** TODO */
                    /**
                     * @brief This method activates the processed components.
                     * 
                     * @return UCMErrorDomain (MissingDependencies - OperationNotPermitted - UpdateSessionRejected - PreActivationFailed - VerificationFailed) 
                     */
                    UCMErrorDomain Activate();

                    /**
                     * @brief This method aborts an ongoing processing of a Software Package
                     * 
                     * @param [in] id TransferIdType
                     * @return UCMErrorDomain (CancelFailed - InvalidTransferId - OperationNotPermitted)
                     */
                    UCMErrorDomain Cancel(TransferIdType id);

                    /**
                     * @brief Delete a transferred Software Package.
                     * 
                     * @param [in] id TransferIdType
                     * @return UCMErrorDomain  (InvalidTransferId - OperationNotPermitted))
                     */
                    UCMErrorDomain DeleteTransfer(TransferIdType id);

                    /**
                     * @brief This method finishes the processing for the current set of processed Software Packages. It does a
                     *          cleanup of all data of the processing including the sources of the Software Packages.
                     * 
                     * @return UCMErrorDomain (OperationNotPermitted)
                     */
                    UCMErrorDomain Finish();

                    /**
                     * @brief Getter method to retrieve all actions that have been performed by UCM.
                     * 
                     * @param [in] timestampGE   Earliest timestamp (inclusive)
                     * @param [in] timestampLT   Latest timestamp (exclusive)
                     * @param [out] history       The history of all actions that have been performed by UCM.
                     * 
                     * @return UCMErrorDomain 
                     */
                    void GetHistory(uint64_t timestampGE, uint64_t timestampLT, GetHistoryVectorType &history);
                    
                    /**
                     * @brief Get the UCM Instance Identifier.
                     * 
                     * @param [out] id UCM Module Instantiation Identifier.
                     */
                    void GetId(UCMIdentifierType &id);

                    /**
                     * @brief This method returns a list pending changes to the set of SoftwareClusters on the adaptive platform. The returned list includes all SoftwareClusters that are to be added, updated or removed. The list of changes is extended in the course of processing Software Packages.
                     * 
                     * @param [out] SwInfo      List of SoftwareClusters that are in state kAdded,kUpdated or kRemoved.
                     */
                    void GetSwClusterChangeInfo(SwClusterInfoVectorType &SwInfo);

                    /**
                     * @brief This method returns the general information of the Software Clusters present in the platform
                     * 
                     * @param [out] SwCluster List of SoftwareClusters present in the platform.
                     */
                    void GetSwClusterDescription(SwDescVectorType &SwCluster);

                    /**
                     * @brief This method returns a list of SoftwareClusters that are in state kPresent.
                     * 
                     * @param [out] SwInfo List of installed SoftwareClusters that are in state kPresent.
                     */
                    void GetSwClusterInfo(SwClusterInfoVectorType &SwInfo);

                    /**
                     * @brief This method returns the Software Packages that available in UCM.
                     * 
                     * @param [out] Packages  List of Software Packages.
                     */
                    void GetSwPackages(SwPackageInfoVectorType &Packages);

                    /**
                     * @brief Get the progress (0 - 100%) of the currently processed Software Package.
                     * 
                     * @param [in] id        The Transfer ID of the Software Package.
                     * @param [out] progress The progress of the current package processing (0% - 100%). 0x00 ... 0x64, 0xFF for "’No information available"’
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain GetSwProcessProgress(TransferIdType id, uint8_t &progress);

                    /**
                     * @brief Process a previously transferred Software Package.
                     * 
                     * @param [in] id The Transfer ID of the Software Package which should be processed.
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain ProcessSwPackage(TransferIdType id);

                    /**
                     * @brief Revert the changes done by processing (ProcessSwPackage) of one or several software packages.
                     * 
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain RevertProcessedSwPackages();

                    /**
                     * @brief Rollback the system to the state before the packages were processed.
                     * 
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain Rollback();

                    /**
                     * @brief Block-wise transfer of a Software Package to UCM.
                     * 
                     * @param [in] id   Transfer ID.
                     * @param [in] data Data block of the Software Package. 
                     * @param [in] size Block counter value of the current block. 
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain TransferData(TransferIdType id, ByteVectorType data, uint64_t size);
                    
                    /**
                     * @brief Finish the transfer of a Software Package to UCM.
                     * 
                     * @param [in] id Transfer ID of the currently running request.
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain TransferExit(TransferIdType id);

                    /**
                     * @brief Start the transfer of a Software Package. The size of the Software Package to be transferred to UCM
                     *          must be provided. UCM will generate a Transfer ID for subsequent calls to TransferData, TransferExit,
                     *          ProcessSwPackage, DeleteTransfer.
                     * 
                     * @param [in] size          Size (in bytes) of the Software Package to be transferred.
                     * @param [out] id            Return TransferId.
                     * @param [out] BlockSize     Size of the blocks to be received with TransferData method.
                     * @return UCMErrorDomain 
                     */
                    UCMErrorDomain TransferStart(uint64_t size, TransferIdType &id, uint32_t &BlockSize);
                }
                /**
                 * @brief implementation of PackageManagementProxy interface
                 * 
                 * @note . It is an instance of a C++ class local to the application/client, which uses the service.
                 *       . ref: 6.2 Proxy Class in exp_aracomAPI
                 * 
                 * @todo inherit from ara::com::proxy_skeleton::proxy::ServiceProxy
                 */
                class PackageManagementProxy
                {
                    public:
                        /**
                         * @todo: - ctor
                         *        - Events
                         *        - Fields
                         *        - Methods
                         */

                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_PROXY_H_ */

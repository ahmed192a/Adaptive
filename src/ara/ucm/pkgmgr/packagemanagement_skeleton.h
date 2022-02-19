/**
 * @file packagemanagement_skeleton.h
 * @author Sarah Mohamed
 * @brief Skeleton(service provider) file for ucm::pkgmgr
 * @version 0.1
 * @date 2022-02-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_
#define ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_
namespace ara
{
    namespace ucm
    {
        namespace pkgmgr
        {
            namespace skeleton
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
                    using CurrentStatus = int;
                }
                /**
                 * @brief implementation of PackageManagementSkeleton interface
                 * 
                 * @note . Service implementation class is derived from the (service) skeleton.
                 *       . ref: 6.3 Skeleton Class in exp_aracomAPI
                 * 
                 * @todo inherit from ara::com::internal::skeleton::ServiceSkeleton
                 */
                class PackageManagementSkeleton
                {
                    public:
                        /**
                         * @brief Construct a new Package Management Skeleton object
                         *        Ctor taking instance identifier as parameter and having default
                         *        request processing mode kEvent.
                         * 
                         * @param instance 
                         * @param mode 
                         * @todo implement arguments types 
                         * 
                         */
                        PackageManagementSkeleton(
                            // ara::com::InstanceIdentifier instance,
                            // ara::com::MethodCallProcessingMode mode = ara::com::MethodCallProcessingMode::kEvent

                        )
                        {

                        }
                         /**
                         * @todo: - Events
                         *        - Fields
                         *        - Methods
                         */

                };

            }
        }

    }
}

#endif /* ARA_UCM_PKGMGR_PACKAGEMANAGEMENT_SKELETON_H_ */

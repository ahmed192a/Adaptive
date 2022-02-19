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
                    using CurrentStatus = int;
                }
                namespace methods
                {
                    /** TODO */
                }
                /**
                 * @brief implementation of PackageManagementProxy interface
                 * 
                 * @note . It is an instance of a C++ class local to the application/client, which uses the service.
                 *       . ref: 6.2 Proxy Class in exp_aracomAPI
                 * 
                 * @todo inherit from ara::com::internal::proxy::ServiceProxy
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

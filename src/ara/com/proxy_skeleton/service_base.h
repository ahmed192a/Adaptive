/**
 * @file service_base.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ARA_COM_SKELETON_SERVICE_BASE_H_
#define ARA_COM_SKELETON_SERVICE_BASE_H_

#include "manifest.h"

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {

            class ServiceBase
            {
            public:
                ServiceBase(std::string name)
                {
                    m_name = name;
                    m_serviceInterface = std::make_shared<ara::com::proxy_skeleton::ServiceInterface>();
                }

                virtual ~ServiceBase();

            protected:
                void addMethod(std::string name)
                {
                    m_serviceInterface->methods.push_back(name);
                }
                void addEvent (std::string name)
                {
                    m_serviceInterface->events.push_back(name);
                }
                void addField (std::string name, bool hasGetter = true, bool hasNotifier = true, bool hasSetter = true)
                {
                    m_serviceInterface->fields.push_back(name);
                }

                std::string m_name;
                std::shared_ptr<ara::com::proxy_skeleton::ServiceInterface> m_serviceInterface;
            };
        } // proxy_skeleton
    } // com
} // ara

#endif // ARA_COM_proxy_skeleton_SERVICE_BASE_H_

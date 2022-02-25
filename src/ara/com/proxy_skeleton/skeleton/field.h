/**
 * @file field.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ARA_COM_proxy_skeleton_SKELETON_FIELD_H_
#define ARA_COM_proxy_skeleton_SKELETON_FIELD_H_

namespace ara
{
    namespace com
    {
        namespace proxy_skeleton
        {
            namespace skeleton
            {

                template <typename T>
                class Field
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    ara::com::FieldGetHandler<T> GetHandler;
                    ara::com::FieldSetHandler<T> SetHandler;
                    Field(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr), SetHandler(nullptr)
                    {
                        m_name = name;
                    }

                    virtual ~Field() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }
                    /*check if this implementation is right*/
                    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }
                };

                template <typename T>
                class FieldNoSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoSetter(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr)
                    {
                    }

                    virtual ~FieldNoSetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }

                    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    ara::com::FieldGetHandler<T> GetHandler;
                };

                template <typename T>
                class FieldNoGetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoGetter(ServiceSkeleton *service, std::string name)
                        : SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoGetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }

                    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    ara::com::FieldSetHandler<T> SetHandler;
                };

                template <typename T>
                class FieldNoGetterAndSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoGetterAndSetter(ServiceSkeleton *service, std::string name)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoGetterAndSetter() {}

                    void Update(const T &data)
                    {
                        m_service->SendEvent(m_name, data, true);
                    }
                };

                template <typename T>
                class FieldNoNotifier
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifier(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr), SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifier() {}

                    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    ara::com::FieldGetHandler<T> GetHandler;
                    ara::com::FieldSetHandler<T> SetHandler;
                };

                template <typename T>
                class FieldNoNotifierAndSetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndSetter(ServiceSkeleton *service, std::string name)
                        : GetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifierAndSetter() {}

                    void RegisterGetHandler(ara::com::FieldGetHandler<T> getHandler)
                    {
                        GetHandler = getHandler;
                    }

                    ara::com::FieldGetHandler<T> GetHandler;
                };

                template <typename T>
                class FieldNoNotifierAndGetter
                {
                private:
                    ServiceSkeleton *m_service;
                    std::string m_name;

                public:
                    FieldNoNotifierAndGetter(ServiceSkeleton *service, std::string name)
                        : SetHandler(nullptr)
                    {
                        m_name = name;
                        m_service = service;
                    }

                    virtual ~FieldNoNotifierAndGetter() {}

                    void RegisterSetHandler(ara::com::FieldSetHandler<T> setHandler)
                    {
                        SetHandler = setHandler;
                    }

                    ara::com::FieldSetHandler<T> SetHandler;
                };

                /* Interface for creating field opject ddepending on the input (getter/notifier/setter)*/
                template <typename T, bool hasGetter, bool hasNotifier, bool hasSetter>
                struct FieldType
                {
                    using type = typename FieldType<T, hasNotifier, hasGetter, hasSetter>::type;
                };

                /*if all true create object of Field class*/
                template <typename T>
                struct FieldType<T, true, true, true>
                {
                    using type = Field<T>;
                };
                /*if No Setter create object of FieldNoSetter class*/
                template <typename T>
                struct FieldType<T, true, true, false>
                {
                    using type = FieldNoSetter<T>;
                };

                /*if No Getter create object of FieldNoGetter class*/
                template <typename T>
                struct FieldType<T, false, true, true>
                {
                    using type = FieldNoGetter<T>;
                };

                /*if No Getter & Setter create object of FieldNoGetterAndSetter class*/
                template <typename T>
                struct FieldType<T, false, true, false>
                {
                    using type = FieldNoGetterAndSetter<T>;
                };
                /*if No Notifier create object of FieldNoNotifier class*/
                template <typename T>
                struct FieldType<T, true, false, true>
                {
                    using type = FieldNoNotifier<T>;
                };
                /*if No Notifier & setter create object of FieldNoNotifierAndSetter class*/
                template <typename T>
                struct FieldType<T, true, false, false>
                {
                    using type = FieldNoNotifierAndSetter<T>;
                };
                /*if No Notifier & Getter create object of FieldNoNotifierAndGetter class*/
                template <typename T>
                struct FieldType<T, false, false, true>
                {
                    using type = FieldNoNotifierAndGetter<T>;
                };

            } // skeleton
        }     // proxy_skeleton
    }         // com
} // ara

#endif // ARA_COM_proxy_skeleton_SKELETON_FIELD_H_

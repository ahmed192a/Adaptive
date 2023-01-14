// #include "ara/com/proxy_skeleton/skeleton/service_skeleton.h"

// namespace ara
// {
//     namespace com
//     {
//         namespace proxy_skeleton
//         {
//             namespace skeleton
//             {
//                 template <typename Class, typename R, typename... Args>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  std::future<R> (Class::*method)(Args...),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
//                 }

//                 template <typename Class, typename... Args>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  std::future<void> (Class::*method)(Args...),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
//                 }
//                 template <typename Class, typename R>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  std::future<R> (Class::*method)(),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     std::future<R> f = (c.*method)();
//                     // f.then([this, msg, binding](std::future<R> &&f) -> bool
//                     //        {
//                     R r = f.get();

//                     binding.Send(&r, sizeof(int));
//                     binding.CloseSocket();
//                     //   return true; });
//                 }
//                 template <typename Class>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  std::future<void> (Class::*method)(),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     std::future<void> f = (c.*method)();
//                     // f.then([this, msg, binding](std::future<void> &&f) -> bool
//                     //        {
//                     f.get();

//                     binding.Send(&msg, sizeof(int));
//                     binding.CloseSocket();
//                     //    return true; });
//                 }

//                 template <typename Class, typename... Args>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  void (Class::*method)(Args...),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     sHandleCall(c, method, msg, binding, std::index_sequence_for<Args...>());
//                 }

//                 template <typename Class>
//                 void ServiceSkeleton::HandleCall(Class &c,
//                                                  void (Class::*method)(),
//                                                  Message msg,
//                                                  Socket &binding)
//                 {
//                     (c.*method)();
//                 }

//             }
//         }
//     }
// }
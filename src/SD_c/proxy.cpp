#include "proxy.h"

namespace saam{
    proxy::proxy(ara::com::proxy_skeleton::proxy::ServiceProxy::SP_Handle proxy_handle)
        :ara::com::proxy_skeleton::proxy::ServiceProxy(proxy_handle), 
        ev1(this,"event1" , 0),
        ev2(this,"event2" , 1),
        fd1(this , "field1" , 2),
        ADD(this)
    {
    }

    int proxy::Add(int p1, int p2)
    {
        return 1;//SendRequest(methodid,p1,p2);
    }

    proxy::~proxy()
    {
    }
}
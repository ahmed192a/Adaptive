#include "ara/SD_c/proxy.hpp"

namespace saam{
    proxy::proxy()
        :ev1(this,"event1" , 0),
        ev2(this,"event2" , 1),
        fd1(this , "field1" , 2),
        ADD(this)
    {
    }

    int proxy::Add(int p1, int p2)
    {
        return SendRequest(0,p1,p2);
    }

    proxy::~proxy()
    {
    }
}
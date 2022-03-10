#include "ara/SD_c/proxy.hpp"

namespace saam{
proxy::proxy(/* args */)
:ev1(this,"event1" , 0),
ev2(this,"event2" , 1),
fd1(this , "field1" , 2)
{
}


proxy::~proxy()
{
}
}
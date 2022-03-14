/**
 * @file skeleton.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/SD_s/skeleton.hpp"
#include "ara/com/proxy_skeleton/definitions.hpp"
#include "ara/com/proxy_skeleton/skeleton/data_type.hpp"
using SD_data = ara::com::proxy_skeleton::SD_data;


using namespace std;
skeleton::skeleton(
    ara::com::InstanceIdentifier instance, 
    ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
    :serviceid(32)
    ,ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid,instance,skeleton_handle),
    event1(this , "event1" , 0),
    event2(this , "event2" , 1),
    field1(this , "field1" , 2)
{

}

skeleton::~skeleton()
{
}


int skeleton::Add(std::vector<uint8_t> msg)
{
    ara::com::Deserializer dser;
    int val1 = dser.deserialize<int>(msg,sizeof(int));
    int val2 = dser.deserialize<int>(msg,sizeof(int)*2);

    return (val1 + val2);
}


void skeleton::method_dispatch(std::vector<uint8_t>& message, Socket& cserver)
{
    ara::com::Deserializer dser;
    int methodID = dser.deserialize<int>(message,0);
    int result = -1;
	cout<<"\t[SERVER] Dispatch " << methodID << endl;
    std::vector<uint8_t> msg;
    msg.insert(msg.begin(), message.begin()+sizeof(int), message.end());

    switch (methodID)
    {
    case 5:
        HandleCall(*this,&skeleton::ADD,msg,cserver);

        // result = Add(message);
        // cserver.Send(&result, sizeof(int));
    	// cserver.CloseSocket();
        break;
    default:
    	cserver.Send(&result, sizeof(int));
    	cserver.CloseSocket();
        break;
    }
}



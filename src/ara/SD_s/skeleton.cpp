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

#include <future>

using SD_data = ara::com::proxy_skeleton::SD_data;

using namespace std;

skeleton::skeleton(
    ara::com::InstanceIdentifier instance,
    ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
    : serviceid(instance.GetInstanceId()),
      ara::com::proxy_skeleton::skeleton::ServiceSkeleton(serviceid, instance, skeleton_handle),
      event1(this, "event1", 0),
      event2(this, "event2", 1),
      field1(this, "field1", 2)
{
}

skeleton::~skeleton()
{
}


void skeleton::method_dispatch(ara::com::SOMEIP_MESSAGE::Message& message, Socket& cserver)
{
    ara::com::Deserializer dser;
    // int methodID = dser.deserialize<int>(message,0);

    int methodID = message.MessageId().method_id;


    std::future<int> result;
    int result2;
	cout<<"\t[SERVER] Dispatch " << methodID << endl;
    // std::vector<uint8_t> msg = message.GetPayload();
    // msg.insert(msg.begin(), message.begin()+sizeof(int), message.end());

    switch (methodID)
    {
    case 5:
        HandleCall(*this,&skeleton::ADD,message,cserver);

        break;
    default:
    	cserver.Send(&result2, sizeof(int));
    	cserver.CloseSocket();
        break;
    }
}

/**
 * @file skeleton.cpp
 * @author Flashing Adapter Graduation Project Team
 * @brief
 * @version 0.1
 * @date 2022-03-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ara/SD_s/skeleton.h"
#include "ara/com/proxy_skeleton/definitions.h"
#include "ara/com/proxy_skeleton/data_type.h"

#include <future>

using SD_data = ara::com::proxy_skeleton::SD_data;

using namespace std;

skeleton::skeleton(
    ara::com::InstanceIdentifier instance,
    ara::com::proxy_skeleton::skeleton::ServiceSkeleton::SK_Handle skeleton_handle)
    : serviceid(instance.GetInstanceId()),
        s_id{instance.GetInstanceId()},
      ara::com::proxy_skeleton::skeleton::ServiceSkeleton(s_id, instance, skeleton_handle),
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

    int methodID = message.MessageId().method_id;

	cout<<"\t[SERVER] Dispatch " << methodID << endl;


    switch (methodID)
    {
    case 5:
        HandleCall(*this,&skeleton::ADD,message,cserver);

        break;
    default:
        // send error
    	// cserver.Send(&result2, sizeof(int));
    	// cserver.CloseSocket();
        break;
    }
}

void skeleton::field_method_dispatch(ara::com::SOMEIP_MESSAGE::Message& message, Socket& cserver)
{
    ara::com::Deserializer dser;
    // int methodID = dser.deserialize<int>(message,0);

    int event_id = message.MessageId().method_id&0x7FFF;
        switch (event_id)
    {
    case 2:
    if(message.Length() > 16){
        field1.HandleGet(message, cserver);
    }
    else{
        field1.HandleSet(message, cserver);
    }
        // field1.HandleCall(message, cserver);
        break;
    default:
    	// cserver.Send(&result2, sizeof(int));
    	// cserver.CloseSocket();
       
        break;
    }
}


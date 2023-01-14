#! /bin/sh
cd ../build/test_partial_processes/SomeIP;
./some_client/cleint_someip;
echo "SomeIP client finished";
./some_server/server_someip;
echo "SomeIP server finished";
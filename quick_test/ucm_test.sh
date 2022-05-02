#! /bin/sh
cd ../build/test_partial_processes/SD_TEST;
gnome-terminal -- './SD/sd_process';
gnome-terminal -- './ucm_server/ucm_server_test';
# gnome-terminal -- './ucm_client/ucm_client_test';
# gnome-terminal -- './Classic/classic_test';
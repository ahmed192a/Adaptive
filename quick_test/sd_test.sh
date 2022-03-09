#! /bin/sh
cd ..;
cd build/test_partial_processes/SD_TEST ;
gnome-terminal -- './SD/sd_process';
gnome-terminal -- './server/server_sd';
gnome-terminal -- './client/cleint_sd';

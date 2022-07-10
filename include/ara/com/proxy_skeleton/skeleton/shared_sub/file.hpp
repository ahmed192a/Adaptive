/**
 * @file file.hpp
 * @author Flashing Adapter Graduation Project Team
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _SUBSCRIBER_FILE_H_
#define _SUBSCRIBER_FILE_H_
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include "ara/com/proxy_skeleton/definitions.hpp"
using namespace std;
class Subscriber
{
private:
    // const char *mfile_name;

public:
    // Subscriber(const char *file_name) : mfile_name{file_name}
    // {
    //     clear(mfile_name);
    // }
    void write(const char *file_name, ara::com::proxy_skeleton::Client_udp_Info client)
    {
        // first check if the data already exists
        // if exists -> do not write
        if (check(file_name, client))
        {
            return;
        }

        // open file for writing, append data
        fstream sub_file;
        sub_file.open(file_name, ios::app);

        // if opened, write the data into the file
        if (sub_file.is_open())
        {
            sub_file << client.port << ","
                     << client.addr << "\n";
        }
        else
            cout << "Error. Creating empty file." << endl;

        // close the file
        sub_file.close();
    }
    // Check before writing in file -> No repeated data
    bool check(const char *file_name, ara::com::proxy_skeleton::Client_udp_Info client)
    {
        // open file for reading
        fstream sub_file;
        sub_file.open(file_name, ios::in);

        // strings to store the rows elements in
        string first_item, second_item;

        while (getline(sub_file, first_item, ','))
        {
            getline(sub_file, second_item, '\n');
            int port = stoi(first_item);
            if (port == client.port && second_item == client.addr)
            {
                sub_file.close();
                return true;
            }
        }
        sub_file.close();
        return false;
    }
    std::vector<ara::com::proxy_skeleton::Client_udp_Info> getrows(const char *file_name)
    {
        fstream sub_file;
        std::vector<ara::com::proxy_skeleton::Client_udp_Info> vclients;
        sub_file.open(file_name, ios::in);
        ara::com::proxy_skeleton::Client_udp_Info client;
        string first_item, second_item;
        while (getline(sub_file, first_item, ','))
        {
            getline(sub_file, second_item, '\n');

            client.port = stoi(first_item);
            client.addr = second_item;
            vclients.push_back(client);
        }
        return vclients;
    }

    // Server sendes stop offer service
    void delete_record(const char *file_name, ara::com::proxy_skeleton::Client_udp_Info client)
    {
        // Open File pointers
        fstream fin, fout;

        // Open the existing file
        fin.open(file_name, ios::in);

        // Create a new file to store the non-deleted data
        fout.open("temp.sub", ios::out);

        int roll1, marks, count = 0, i;
        char sub;
        int index, new_marks;
        string line, word1,word2;
        vector<string> row;

        // Check if this record exists
        // If exists, leave it and
        // add all other data to the new file
        while (getline(fin, word1, ','))
        {
            // getline(s, word1, ',');
            getline(fin, word2, '\n');


            


            // writing all records,
            // except the record to be deleted,
            // into the new file 'reportcardnew.sub'
            // using fout pointer
            if (!(stoi(word1) == client.port && strcmp(word2.data() ,client.addr.data())==0 ))
            {
                fout << word1 << ", ";
                fout << word2 << "\n";
            }
            else
            {
                count = 1;
            }
        }
        // if (count == 1)
        //     cout << "Record deleted\n";
        // else
        //     cout << "Record not found\n";

        // Close the pointers
        fin.close();
        fout.close();

        // removing the existing file
        remove(file_name);

        // renaming the new file with the existing file name
        rename("temp.sub", file_name);
    }

    void clear(const char *file_name)
    {
        ofstream ofs;
        ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
};

#endif // _SUBSCRIBER_FILE_H_
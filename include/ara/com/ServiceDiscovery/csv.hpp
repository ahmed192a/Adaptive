/**
 * @file csv.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _SD_CSV_H_
#define _SD_CSV_H_
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include "ara/com/proxy_skeleton/definitions.hpp"
using SD_data = ara::com::proxy_skeleton::SD_data;

using namespace std;

class CSV{
    public:
    /**
     * @brief Function to write the service_info which was received from the server in a CSV File
     * 
     * @param file_name
     * @param service_info
    */
    void write (const char* file_name,  SD_data service_info)
    {
        // first check if the data already exists
        // if exists -> do not write
        if (check(file_name, service_info.service_id, service_info.instance_id))
        {
            return;
        }

        // open file for writing, append data
        fstream csv_file;
        csv_file.open(file_name, ios::app);

        // if opened, write the data into the file
        if (csv_file.is_open())
        {
            csv_file << service_info.service_id << ", " 
                        << service_info.instance_id << ", " << service_info.port_number << "\n";
        }    
        else
            cout << "Error. Creating empty file." << endl;
        
        // close the file
        csv_file.close();
    }

    /**
     * @brief Function to check if the received service_info already exists in the CSV file
     * 
     * @param file_name
     * @param service_id
     * @param instance_id 
     * @return bool
    */
    bool check(const char* file_name, int service_id, int instance_id)
    {
        // open file for reading
        fstream csv_file;
        csv_file.open(file_name, ios::in);

        // strings to store the rows elements in
        string first_item, second_item, third_item;

        while (getline(csv_file, first_item, ','))
        {
            getline(csv_file, second_item, ',');
            getline(csv_file, third_item, '\n');
            int service = stoi(first_item);
            int process = stoi(second_item);
            if (service == service_id && process == instance_id)
            {
                return true;
            }
        }

        return false;
    }

    /**
     * @brief Function to find the service_info using service_id
     * 
     * @param file_name
     * @param service_id
     * @param result 
    */
    void FindRow (const char* file_name, int service_id, vector<SD_data> &result)
    {
        // open file for reading
        fstream csv_file;
        csv_file.open(file_name, ios::in);

        SD_data data;

        // strings to store the rows elements in
        string first_item, second_item, third_item;

        while (getline(csv_file, first_item, ','))
        {
            getline(csv_file, second_item, ',');
            getline(csv_file, third_item, '\n');
            int service = stoi(first_item);
            cout<<"----------"<<endl;
            cout<<"service from file "<<service<< " sd id "<<service_id<<endl;
            if (service == service_id)
            {
                data.service_id = service;
                data.instance_id = stoi(second_item);
                data.port_number = stoi(third_item);
                result.push_back(data);
            }
        }

        if (result.empty())
        {
            // if not found, fill the struct with negative ones
            data.service_id = -1;
            data.port_number = -1;
            data.instance_id = -1;
            result.push_back(data);
        }

        csv_file.close();
    }

    /**
     * @brief Function to delete a row from the CSV file
     * 
     * @param file_name
     * @param service_id
     * @param instance_id 
    */
    void delete_record (const char* file_name, int service_id, int instance_id)
    {  
        fstream fin, fout;               /* Open File pointers */
        fin.open(file_name, ios::in);    /* Open the CSV file for reading */
        fout.open("temp.csv", ios::out); /* Create a new file to store the non-deleted data */

        int roll1, /* carry service_id of each row exists in the CSV file*/
        roll2,     /* carry instance_id of each row exists in the CSV file*/
        i;         /* iterator */
        string line, word;
        vector<string> row;

        // Check if this record exists
        // If exists, leave it and
        // add all other data to the new file
        while (!fin.eof()) {    
            row.clear();
            getline(fin, line);
            stringstream s(line);

            while (getline(s, word, ',')) {
                row.push_back(word);
            }

            int row_size = row.size();
            roll1 = stoi(row[0]);
            roll2 = stoi(row[1]);

            // writing all records,
            // except the record to be deleted,
            // into the new file 'temp.csv'
            // using fout pointer
            if (roll1 != service_id || roll2 != instance_id) {
                if (!fin.eof()) {
                    for (i = 0; i < row_size - 1; i++) {
                        fout << row[i] << ", ";
                    }
                    fout << row[row_size - 1] << "\n";
                }
            }
            else {
                // do nothing
            }
            if (fin.eof())
                break;
        }

        /* Close the pointers */
        fin.close();
        fout.close();

        remove(file_name);             /* removing the existing file */
        rename("temp.csv", file_name); /* renaming the new file with the existing file name */
    }

    /**
     * @brief Function to clear the CSV file
     * 
     * @param file_name
    */
    void clear (const char* file_name)
    {
        ofstream ofs;
        ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
};

#endif
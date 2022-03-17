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
    void write (const char* file_name,  SD_data data)
    {
        // first check if the data already exists
        // if exists -> do not write
        if (check(file_name, data.service_id, data.process_id))
        {
            return;
        }

        // open file for writing, append data
        fstream csv_file;
        csv_file.open(file_name, ios::app);

        // if opened, write the data into the file
        if (csv_file.is_open())
        {
            csv_file << data.service_id << ", " 
                        << data.process_id << ", " << data.port_number << "\n";
        }    
        else
            cout << "Error. Creating empty file." << endl;
        
        // close the file
        csv_file.close();
    }
    // Check before writing in file -> No repeated data
    bool check(const char* file_name, int service_id, int process_id)
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
            if (service == service_id && process == process_id)
            {
                return true;
            }
        }

        return false;
    }
    void FindRow (const char* file_name, int row_id, vector<SD_data> &result)
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
            if (service == row_id)
            {
                data.service_id = service;
                data.process_id = stoi(second_item);
                data.port_number = stoi(third_item);
                result.push_back(data);
            }
        }

        if (result.empty())
        {
            // if not found, fill the struct with zeros
            data.service_id = -1;
            data.port_number = -1;
            data.process_id = -1;
            result.push_back(data);
        }
        // if not found, fill the struct with zeros
        data.service_id = -1;
        data.port_number = -1;
        data.process_id = -1;

        csv_file.close();
    }
    // Server sendes stop offer service
    void delete_record (const char* file_name, int delete_record)
    {  
        // Open File pointers
        fstream fin, fout;
    
        // Open the existing file
        fin.open(file_name, ios::in);
    
        // Create a new file to store the non-deleted data
        fout.open("temp.csv", ios::out);
    
        int roll1, marks, count = 0, i;
        char sub;
        int index, new_marks;
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
    
            // writing all records,
            // except the record to be deleted,
            // into the new file 'reportcardnew.csv'
            // using fout pointer
            if (roll1 != delete_record) {
                if (!fin.eof()) {
                    for (i = 0; i < row_size - 1; i++) {
                        fout << row[i] << ", ";
                    }
                    fout << row[row_size - 1] << "\n";
                }
            }
            else {
                count = 1;
            }
            if (fin.eof())
                break;
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
        rename("temp.csv", file_name);
    }

    void clear (const char* file_name)
    {
        ofstream ofs;
        ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
};

#endif
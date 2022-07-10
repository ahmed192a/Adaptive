/**
 * @file Log.hpp
 * @author Flashing Adapter Graduation Project Team
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LOG_H_
#define LOG_H_

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

enum class LogType : uint8_t
{
    INFO = 0, 
    ERROR = 1

};

class Log
{
public:
    // location of file to write log information
    char fifo_l[30] = "Log_File.txt";

    ofstream myFile_Handler;    // file handler to write log information
    string cluster_name;        // name of cluster

    /**
     * @brief Construct a new Log object
     * @note open file to write log information
     */
    Log(std::string name) noexcept;
    /**
     * @brief Destroy the Log object
     * @note close file to write log information
     */
    ~Log() noexcept;
    /**
     * @brief Insert log information to file
     * 
     * @param data data to insert to file
     * @param T  type of log information
     * @return  void
     */
    void Insert(std::string data,  LogType T = LogType::INFO);
    /**
     * @brief insert log information to file
     * 
     * @return void
     */
    void operator<<(std::string data);

};


#endif // LOG_H_

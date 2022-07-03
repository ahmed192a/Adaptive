/**
 * @file Log.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "ara/Log_trace/Log.hpp"    
#include "sys/stat.h"   
#include "sys/types.h"   
#include "errno.h"      // for errno and EEXIST macro definition 
#include "unistd.h"     // for mkfifo
#include <fcntl.h>      // for open flags O_RDWR, O_CREAT, O_EXCL 
#include <chrono>       // chrono::system_clock
#include <ctime>        // local time
#include <sstream>      // string stream
#include <iomanip>      // put_time
#include <string>       // string


using namespace std::chrono;

/**
 * @brief Get the current time in the string format  (YYYY-MM-DD HH:MM:SS)
 * 
 * @return std::string 
 */
std::string return_current_time_and_date()
{
    // get current time
    auto now = std::chrono::system_clock::now();  

    // convert to std::time_t
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // string stream
    std::stringstream ss;   

    // convert time to string
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X"); 
    return ss.str();    // return current time in string format
}

Log::Log(std::string name) noexcept{
    this->cluster_name = name;
    // delete log file if it exists
    if (access(fifo_l, F_OK) != -1) {
        remove(fifo_l);
    }

    // open file to write
    myFile_Handler.open(fifo_l, std::ios::out);

    if(myFile_Handler.is_open()){
        myFile_Handler << "["+cluster_name+"] Log file created at " << return_current_time_and_date() << endl;
    }
    else{
        cout << "Error opening file" << endl;
    }
}

Log::~Log() noexcept{
    myFile_Handler.close();
}

void Log::Insert(std::string data, LogType T){
	switch(T){
		case LogType::INFO:
		    myFile_Handler << "[INFO]\t";
		break;

		case LogType::ERROR:
		    myFile_Handler << "[ERROR]\t";
		break;

		default:
		    myFile_Handler << "[INFO]\t";
		break;
	}
    myFile_Handler <<"["<<return_current_time_and_date()<<"]\t\t"<<cluster_name<<"\t"<< data << endl;
}

void Log::operator<<(std::string data){
    myFile_Handler <<"["<<return_current_time_and_date()<<"]\t\t"<<cluster_name<<"\t"<< data << endl;
}


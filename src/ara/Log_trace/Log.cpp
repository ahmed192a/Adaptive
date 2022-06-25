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
#include "errno.h"
#include "unistd.h"
#include <fcntl.h>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string


using namespace std::chrono;

std::string return_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

Log::Log() noexcept{

    // get file discreptor
      myFile_Handler.open(fifo_l, std::fstream::out | std::fstream::app);
     if(myFile_Handler.is_open())
    {
    	
    }
    else {
    cout<< "Unable to open the Log file!";
    //return 0;
    }
}

Log::~Log() noexcept{
    myFile_Handler.close();
}
void Log::Insert(std::string data, std::string from, LogType T){
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

	
    myFile_Handler <<"["<<return_current_time_and_date()<<"]\t\t"<<from<<"\t"<< data << endl;

}
void Log::operator<<(std::string data){
    myFile_Handler << data << endl;
}


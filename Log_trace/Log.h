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
    // location of FIFO to communicate between EM & SM
    char fifo_l[30] = "Log_File.txt";

    ofstream myFile_Handler;

    //using TimeStamp = std::chrono::time_point<ara::core::SteadyClock>;
    
    // using TimeStamp = std::chrono::time_point<std::chrono::system_clock> ;

    // TimeStamp Activated;
    Log() noexcept;
    ~Log() noexcept;
    void Insert(std::string data, std::string from, LogType T = LogType::INFO);

};


#endif // LOG_H_

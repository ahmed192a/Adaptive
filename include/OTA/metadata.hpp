#ifndef METADATA_H
#define METADATA_H

#include "updateversion.hpp"
#include "json/value.h"
#include "json/json.h"
class MetaData
{
    //MetaData variables
    std::string platformName;
    std::string appName;
    std::string appID;
    UpdateVersion v;
    unsigned long sizeInBytes;

public:
    // Constructor Overloading to support different types of initializations
    MetaData();
    MetaData(std::string platformName, std::string appName, std::string appID, unsigned long sizeInBytes, std::string ver);
    MetaData(std::string jsonStr);

    //operator overloading for ">" sign
    bool operator > (MetaData Meta2);

    // setters and getters for the class members
    void set_platformName(std::string platformName);
    std::string get_platformName(void);

    void set_appName(std::string appName);
    std::string get_appName(void);

    void set_appID(std::string appID);
    std::string get_appID(void);

    void set_sizeInBytes(unsigned long sizeInBytes);
    unsigned long get_sizeInBytes(void);

    void set_version(UpdateVersion version);
    UpdateVersion get_version();

};

#endif // METADATA_H

#ifndef METADATA_H
#define METADATA_H

#include "updateversion.h"
#include "json/value.h"
#include "json/json.h"
class MetaData
{
    //MetaData variables
    string platformName;
    string appName;
    string appID;
    UpdateVersion v;
    unsigned long sizeInBytes;

public:
    // Constructor Overloading to support different types of initializations
    MetaData();
    MetaData(string platformName, string appName, string appID, unsigned long sizeInBytes, string ver);
    MetaData(string jsonStr);

    //operator overloading for ">" sign
    bool operator > (MetaData Meta2);

    // setters and getters for the class members
    void set_platformName(string platformName);
    string get_platformName(void);

    void set_appName(string appName);
    string get_appName(void);

    void set_appID(string appID);
    string get_appID(void);

    void set_sizeInBytes(unsigned long sizeInBytes);
    unsigned long get_sizeInBytes(void);

    void set_version(UpdateVersion version);
    UpdateVersion get_version();

};

#endif // METADATA_H

#ifndef META_DATA_HPP
#define META_DATA_HPP
#include <iostream>
#include <string>
#include <vector>
// #include "./json.h"
// create class MetaData
class MetaData
{
    //MetaData variables
    std::string platformName;
    std::string appName;
    std::string appID;
    std::string v;
    unsigned long sizeInBytes;

public:
    // Constructor Overloading to support different types of initializations
    MetaData(){}
    MetaData(std::string platformName, std::string appName, std::string appID, unsigned long sizeInBytes, std::string ver)
    {
        this->platformName = platformName;
        this->appName = appName;
        this->appID = appID;
        this->sizeInBytes = sizeInBytes;
        this->v=ver;
    }
    MetaData(std::string jsonStr)
    {
        if(jsonStr.length()>0)
        {
            std::string key = "platformName";
            // find platformName and get the value
            int index = jsonStr.find(key)+key.size()+2;
            index  = jsonStr.find("\"",index)+1;
            // find next " after index and get the value between " and "
            int index2 = jsonStr.find("\"",index);
            this->platformName = jsonStr.substr(index,index2-index);

            // std::cout<<"platformName: "<<this->platformName<<std::endl;

            key = "appName";
            // find appName and get the value
            index = jsonStr.find(key)+key.size()+2;
            index  = jsonStr.find("\"",index)+1;
            // find next " after index and get the value between " and "
            index2 = jsonStr.find("\"",index);
            this->appName = jsonStr.substr(index,index2-index);

            // std::cout<<"appName: "<<this->appName<<std::endl;

            key = "appID";
            // find appID and get the value
            index = jsonStr.find(key)+key.size()+2;
            index = jsonStr.find("\"",index)+1;
            // find next " after index and get the value between " and "
            index2 = jsonStr.find("\"",index);
            this->appID = jsonStr.substr(index,index2-index);
            // std::cout<<"appID: "<<this->appID<<std::endl;

            key = "sizeInBytes";
            // find sizeInBytes and get the value
            index = jsonStr.find(key)+key.size()+2;
            index = jsonStr.find("\"",index)+1;
            // find next " after index and get the value between " and "
            index2 = jsonStr.find("\"",index);
            this->sizeInBytes = std::stoul(jsonStr.substr(index,index2-index));
            // std::cout<<"sizeInBytes: "<<this->sizeInBytes<<std::endl;

            key = "version";
            // find version and get the value
            index = jsonStr.find(key)+key.size()+2;
            index = jsonStr.find("\"",index)+1;
            // find next " after index and get the value between " and "
            index2 = jsonStr.find("\"",index);
            this->v = jsonStr.substr(index,index2-index);
            // std::cout<<"version: "<<this->v<<std::endl;



        }else{
            std::cout<<"Empty json string"<<std::endl;
        }

    }

    //operator overloading for ">" sign compare the version of the app
    bool operator > (MetaData Meta2) const
    {
        // split the version string into three parts 1.major 2.minor 3.patch and compare them
        int major1 = atoi(this->v.substr(0, this->v.find(".")).c_str());
        int minor1 = atoi(this->v.substr(this->v.find(".")+1, this->v.find(".")).c_str());
        int patch1 = atoi(this->v.substr(this->v.find(".")+1, this->v.find(".")).c_str());
        int major2 = atoi(Meta2.v.substr(0, Meta2.v.find(".")).c_str());
        int minor2 = atoi(Meta2.v.substr(Meta2.v.find(".")+1, Meta2.v.find(".")).c_str());
        int patch2 = atoi(Meta2.v.substr(Meta2.v.find(".")+1, Meta2.v.find(".")).c_str());
        if(major1 > major2)
            return true;
        else if(major1 == major2)
        {
            if(minor1 > minor2)
                return true;
            else if(minor1 == minor2)
            {
                if(patch1 > patch2)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;

    }
    //operator overloading for "<" sign compare the version of the app
    bool operator < (MetaData Meta2) const
    {
        // split the version string into three parts 1.major 2.minor 3.patch and compare them
        int major1 = atoi(this->v.substr(0, this->v.find(".")).c_str());
        int minor1 = atoi(this->v.substr(this->v.find(".")+1, this->v.find(".")).c_str());
        int patch1 = atoi(this->v.substr(this->v.find(".")+1, this->v.find(".")).c_str());
        int major2 = atoi(Meta2.v.substr(0, Meta2.v.find(".")).c_str());
        int minor2 = atoi(Meta2.v.substr(Meta2.v.find(".")+1, Meta2.v.find(".")).c_str());
        int patch2 = atoi(Meta2.v.substr(Meta2.v.find(".")+1, Meta2.v.find(".")).c_str());
       
        if(major1 < major2)
            return true;
        else if(major1 == major2)
        {
            if(minor1 < minor2)
                return true;
            else if(minor1 == minor2)
            {
                if(patch1 < patch2)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;

    }

    //operator overloading for "==" sign to compare the apppName, platformName & appID only 
    bool operator == (MetaData Meta2)
    {
        // comparing the equivalence of the platformName, appName & appId only to check it is the same app
        if ((this->platformName == Meta2.platformName) && \
        (this->appName == Meta2.appName) && \
        (this->appID == Meta2.appID))
        {
            return true;
        }
        else{
            return false;
        }
    }

    // setters and getters for the class members
    void set_platformName(std::string platformName)
    {
        this->platformName = platformName;
    }
    std::string get_platformName(void)
    {
        return this->platformName;
    }

    void set_appName(std::string appName)
    {
        this->appName = appName;
    }
    std::string get_appName(void)
    {
        return this->appName;
    }

    void set_appID(std::string appID)
    {
        this->appID = appID;
    }
    std::string get_appID(void)
    {
        return this->appID;
    }

    void set_sizeInBytes(unsigned long sizeInBytes)
    {
        this->sizeInBytes = sizeInBytes;
    }
    unsigned long get_sizeInBytes(void)
    {
        return this->sizeInBytes;
    }

    void set_version(std::string version)
    {
        this->v = version;
    }
    std::string& get_version()
    {
        return this->v;
    }


    friend std::istream & operator >> (std::istream &in,  MetaData &c)
    {
        in >> c.platformName >> c.appName >> c.appID >> c.sizeInBytes >> c.v;
        return in;
    }
    friend std::ostream & operator << (std::ostream &out, const MetaData &c)
    {
        out << c.platformName << " " << c.appName << " " << c.appID << " " << c.sizeInBytes << " " << c.v;
        return out;
    }

    // create serialize function to serialize the class members
    std::vector<uint8_t> serialize()
    {
        std::vector<uint8_t> buffer;
        buffer.reserve(sizeof(this->platformName) + sizeof(this->appName) + sizeof(this->appID) + sizeof(this->sizeInBytes) + sizeof(this->v));
        buffer.insert(buffer.end(), (uint8_t*)this->platformName.c_str(), (uint8_t*)this->platformName.c_str() + this->platformName.length());
        buffer.push_back(0);
        buffer.insert(buffer.end(), (uint8_t*)this->appName.c_str(), (uint8_t*)this->appName.c_str() + this->appName.length());
        buffer.push_back(0);
        buffer.insert(buffer.end(), (uint8_t*)this->appID.c_str(), (uint8_t*)this->appID.c_str() + this->appID.length());
        buffer.push_back(0);
        buffer.insert(buffer.end(), (uint8_t*)this->v.c_str(), (uint8_t*)this->v.c_str() + this->v.length());
        buffer.push_back(0);
        return buffer;
    }
    // create serialize function to deserialize the class members into json string format
    std::string serializeToJson()
    {
        std::string jsonStr = "{";
        jsonStr += "\"platformName\":\"" + this->platformName + "\",";
        jsonStr += "\"appName\":\"" + this->appName + "\",";
        jsonStr += "\"appID\":\"" + this->appID + "\",";
        jsonStr += "\"sizeInBytes\":\"" + std::to_string(this->sizeInBytes) + "\",";
        jsonStr += "\"version\":\"" + this->v + "\"";
        jsonStr += "}";
        return jsonStr;

    }
};
#endif
#include "metadata.hpp"

MetaData::MetaData()
{

}

MetaData::MetaData(string platformName, string appName, string appID, unsigned long sizeInBytes, string ver)
{
    UpdateVersion ver2(ver);
    this->v = ver2;
    set_platformName(platformName);
    set_appName(appName);
    set_appID(appID);
    set_sizeInBytes(sizeInBytes);

}

MetaData::MetaData(string jsonStr)
{
    Json::Reader reader;
    Json::Value root;

    //string json = """{\"appID\": \"K234\",\"appName\":\"OTA_APP\",\"sizeInBytes\":138,\"platformName\":\"adaptive\",\"version\": \"1.0.4\",\"result\":\"ok\"}""";

    bool parseSuccess = reader.parse(jsonStr, root, false);

    if (parseSuccess)
    {
      set_platformName(root["platformName"].asString());
      set_appName(root["appName"].asString());
      set_appID(root["appID"].asString());
      set_sizeInBytes(root["sizeInBytes"].asUInt());
      UpdateVersion ver2(root["version"].asString());
      this->v = ver2;
    }

}

bool MetaData::operator >(MetaData Meta2)
{
    if(this->get_sizeInBytes() > Meta2.get_sizeInBytes()){
        return true;
    }
    else{
        return false;
    }
}

void MetaData::set_platformName(string platformName)
{
    this->platformName = platformName;

}

string MetaData::get_platformName()
{
    return this->platformName;

}

void MetaData::set_appName(string appName)
{
    this->appName = appName;

}

string MetaData::get_appName()
{
    return this->appName;

}

void MetaData::set_appID(string appID)
{
    this->appID = appID;
}

string MetaData::get_appID()
{
    return this->appID;
}

void MetaData::set_sizeInBytes(unsigned long sizeInBytes)
{
    this->sizeInBytes = sizeInBytes;
}

unsigned long MetaData::get_sizeInBytes()
{
    return this->sizeInBytes;

}

void MetaData::set_version(UpdateVersion version)
{
    this->v = version;

}

UpdateVersion MetaData::get_version()
{
    return this->v;

}

#include "metadata.h"
using namespace std;

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
    // create a json object
    nlohmann::json root;
    // check if the json string is valid
    bool parseSuccess = nlohmann::json::accept(jsonStr);

    // string json = """{\"appID\": \"K234\",\"appName\":\"OTA_APP\",\"sizeInBytes\":138,\"platformName\":\"adaptive\",\"version\": \"1.0.4\",\"result\":\"ok\"}""";

    // bool parseSuccess = reader.parse(jsonStr, root, false);

    if (parseSuccess)
    {
        // parse the json string
        root = nlohmann::json::parse(jsonStr);

        set_platformName(root["platformName"]);
        set_appName(root["appName"]);
        set_appID(root["appID"]);
        set_sizeInBytes(root["sizeInBytes"]);
        UpdateVersion ver2(root["version"]);
        this->v = ver2;
    }
}

bool MetaData::operator>(MetaData Meta2)
{
    // if(this->get_sizeInBytes() > Meta2.get_sizeInBytes()){
    //     return true;
    // }
    // else{
    //     return false;
    // }
    return this->v > Meta2.v;
}

bool MetaData::operator==(MetaData Meta2)
{

    // comparing the equivalence of the platformName, appName & appId only to check it is the same app

    if ((this->platformName == Meta2.platformName) &&
        (this->appName == Meta2.appName) &&
        (this->appID == Meta2.appID))
    {
        return true;
    }

    return false;
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

void MetaData::set_version(string version)
{
    this->v.set_versionNo(version);
}

UpdateVersion &MetaData::get_version()
{
    return this->v;
}

istream &operator>>(istream &in, MetaData &c)
{
    std::string metaInput;
    in >> metaInput;
    c.set_appID(metaInput);
    in >> metaInput;
    c.set_appName(metaInput);
    in >> metaInput;
    c.set_version(metaInput);
    in >> metaInput;
    c.set_sizeInBytes(stoi(metaInput));
    in >> metaInput;
    c.set_platformName(metaInput);
    return in;
}

ostream &operator<<(ostream &out, const MetaData &c)
{
    // std::string x = c.get_appID();
    out << c.appID << " " << c.appName << " " << c.v.versionNo << " " << c.sizeInBytes << " " << c.platformName;
    return out;
}

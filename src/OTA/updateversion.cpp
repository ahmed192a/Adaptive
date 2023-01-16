#include "updateversion.h"

using namespace std;

UpdateVersion::UpdateVersion()
{
    this->major = 0;
    this->minor = 0;
    this->patch = 0;
    this->versionNo = "0.0.0";
}

UpdateVersion::UpdateVersion(int major, int minor, int patch)
{
    this->major = major;
    this->minor = minor;
    this->patch = patch;
    this->versionNo = to_string(major);
    versionNo.append(".");
    versionNo.append(to_string(minor));
    versionNo.append(".");
    versionNo.append(to_string(patch));

}

UpdateVersion::UpdateVersion(string x)
{
    stringToVersion(x);
}

bool UpdateVersion::operator >(UpdateVersion v2)
{
    //1.1- check tha major part..
    if(this->major > v2.major)
    {
        return true;
    }
    // 1.2- if major equals each other
    else if(this->major == v2.major)
    {
        //2.1- if major equal test the minor parts..
        if(this->minor > v2.minor)
        {
            return true;
        }
        // 2.2- if minor equals each other
        else if(this->minor == v2.minor)
        {
            //3.1- if minor equal test the major parts..
            if(this->patch > v2.patch){
                return true;
            }
            //3.2- if equal or less return false
            else{
                return false;
            }
        }
        //2.3- if minor in less than the other
        else
        {
            return false;
        }
    }
    //1.3- if major in less than the other
    else
    {
        return false;
    }
}

string UpdateVersion::get_versionNo()
{
    return this->versionNo;

}

void UpdateVersion::set_versionNo(string x)
{
    stringToVersion(x);

}

void UpdateVersion::stringToVersion(string x)
{
    this->versionNo = x;
    string major_str = x.substr(0,x.find("."));
    x = x.substr(x.find(".") + 1);
    string minor_str = x.substr(0,x.find("."));
    x = x.substr(x.find(".") + 1);
    string patch_str = x.substr(0);
    this->major = stoi(major_str);
    this->minor = stoi(minor_str);
    this->patch = stoi(patch_str);

}

istream &operator >>(istream &in, UpdateVersion &v)
{
    std::string versionInput;
    in >> versionInput;
    v.set_versionNo(versionInput);
    return in;

}

ostream &operator <<(ostream &out, const UpdateVersion &v)
{
    out << v.versionNo;
    return out;

}

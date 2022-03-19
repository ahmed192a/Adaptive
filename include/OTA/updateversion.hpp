#ifndef UPDATEVERSION_H
#define UPDATEVERSION_H

#include <string>
using namespace std;

class UpdateVersion
{
    int major;
    int minor;
    int patch;
    string versionNo;
public:
    // Constructor Overloading to support different types of initializations
    UpdateVersion();
    UpdateVersion(int major, int minor, int patch);
    UpdateVersion(string x);

    // Enabling copy constructor
    UpdateVersion(const UpdateVersion* v2);

    //operator overloading for ">" sign
    bool operator > (UpdateVersion v2);

    string get_versionNo();


};

#endif // UPDATEVERSION_H

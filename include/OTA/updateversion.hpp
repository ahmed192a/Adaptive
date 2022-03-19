/**
 * @file updateversion.hpp
 * @author
 * @brief  OTA::UpdateVersion class
 * @details Used by the OTA to check the update version to get the new updates
 ********************************************************************************/


#ifndef UPDATEVERSION_H
#define UPDATEVERSION_H
#include <string>


/// @brief A class used to stringify version and apply operation on version
class UpdateVersion
{
    int major;
    int minor;
    int patch;
    std::string versionNo;
public:
    /// @brief Constructor
    UpdateVersion();

    /// @brief Constructor Overloading to support different types of initializations
    /// @param[in] the three parts of the version
    UpdateVersion(int major, int minor, int patch);

    /// @brief Constructor Overloading to support different types of initializations
    /// @param[in] the string of the version
    UpdateVersion(std::string x);

    /// @brief Enabling copy constructor
    /// @param[in] the version to which it is compared
    UpdateVersion(const UpdateVersion* v2);

    /// @brief operator overloading for the binary ">" operator sign to compare between versions
    /// @return boolean to check which version is greater
    bool operator > (UpdateVersion v2);

    /// @brief Getting version of the update
    /// @return string contain the version string
    std::string get_versionNo();


};

#endif // UPDATEVERSION_H

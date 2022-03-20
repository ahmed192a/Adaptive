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
    //std::string versionNo;
public:
    std::string versionNo;

    /// @brief Constructor
    UpdateVersion();

    /// @brief Constructor Overloading to support different types of initializations
    /// @param[in] major major part of the version
    /// @param[in] minor part of the version
    /// @param[in] patch part of the version
    UpdateVersion(int major, int minor, int patch);

    /// @brief Constructor Overloading to support different types of initializations
    /// @param[in] versionString the string of the version
    UpdateVersion(std::string versionString);

    /// @brief Enabling copy constructor
    /// @param[in] ver2 object of UpdateVersion to be copied from
    UpdateVersion(const UpdateVersion* ver2);

    /// @brief operator overloading for the binary ">" operator sign to compare between versions
    /// @param[in] ver2 object of UpdateVersion to be compared with
    /// @return boolean to check which version is greater
    bool operator > (UpdateVersion ver2);

    /// @brief Getting version of the update
    /// @return string contain the version string
    std::string get_versionNo();

    /// @brief Getting version of the update
    /// @param[in] versionString string contain the version string
    void set_versionNo(std::string versionString);


    /// @brief Setting version major, minor and patch of the update
    /// @param[in] versionNo string contain the version string
    void stringToVersion(std::string versionNo);

    /// @brief Overloading input streaming operator
    /// @param[in] in stream input and the updateversion version
    /// @param[out] c UpdateVersion object modified with the input stream
    /// @return input stream contains the version string
    friend std::istream & operator >> (std::istream &in,  UpdateVersion &c);

    /// @brief Overloading input streaming operator
    /// @param[in] c update version
    /// @param[out] out stream output
    /// @return output stream contains the version string
    friend std::ostream & operator << (std::ostream &out, const UpdateVersion &c);


};

#endif // UPDATEVERSION_H

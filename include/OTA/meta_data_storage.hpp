/**
 * @file meta_data_storage.hpp
 * @author 
 * @brief  ota::MetaDataStorage class
 * @details Used by the OTA to store and retrieve old meta-data in the file system
 ********************************************************************************/

#ifndef OTA_META_DATA_STORAGE_H
#define OTA_META_DATA_STORAGE_H

#include <fstream>
#include <vector>
#include <cstdint>
#include "metadata.hpp"

/// @brief A class that deals with the file system to store and load the old meta-data of apps
class MetaDataStorage {

    /// @brief the path of the file that carries the olf meta-data
    std::string fileName;

public:
    /// @brief Constructor 
    /// @param[in] fileName the file storage to communicate with for input or output
    MetaDataStorage(std::string fileName);


    /// @brief fileName setter
    /// @param[in] fileName the file storage to communicate with for input or output
    void set_fileName(std::string fileName);
    

    /// @brief fileName getter
    /// @return std::string => fileName value
    std::string get_fileName(void);


    /// @brief Saves a single meta-data object in the file system
    /// @param[in] newData meta-data object to be stored in the file system
    void save_MetaData(MetaData & newData);     // saving a new application meta-data to the file
    
    
    /// @brief Loads all the stored meta-data objects from the file system
    /// @return vector of all the stored meta-data objects in the file system
    std::vector<MetaData> load_MetaData(void);      // loading the saved meta-data


    /// @brief gets the number of apps in the file system
    /// @return number of applications their meta-data is stored in the file system
    int get_appsCount(void);


    /// @brief deletes all the elements in the meta-data file (reset file)
    void empty_file(void); // removing all data in the file

 private:

    /// @brief Gets a single MetaData instance from the instances stored in the file storage 
    /// @param[in] file the file stream to retrieve from
    /// @param[out] metaData to carry the meta data of a single application
    void retrive_AppMetaData(ifstream file, MetaData& metaData); 

};


#endif // OTA_META_DATA_STORAGE_H
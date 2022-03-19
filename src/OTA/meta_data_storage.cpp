#include "meta_data_storage.hpp"

MetaDataStorage::MetaDataStorage(string fileName) {
    this->fileName = fileName;
}

void MetaDataStorage::set_fileName(string fileName) {
    this->fileName = fileName;
}

string MetaDataStorage::get_fileName() {
    return fileName;
}

void MetaDataStorage::save_MetaData(MetaData & newData) {
    ofstream file;

    file.open(fileName, ios::app | ios::binary);

    file << newData.get_appID().data() << " ";
    file << newData.get_appName().data() << " ";
    file << newData.get_version().get_versionNo() << " ";
    file << newData.get_sizeInBytes() << " ";
    file << newData.get_platformName().data() << " ";
    file << "\n";


}

// vector<MetaData> MetaDataStorage::load_MetaData(void){
//     // file stream to read
//     ifstream file;

//     // temporary variables to carry the data in each iteration
//     MetaData metaTemp;

//     vector<MetaData> returnedVector;


//     file.open(fileName, ios::binary);
//     file.seekg(0, ios::beg);
    
//     std::size_t fileSize = get_appsCount();
//     fileSize *= 5;
//     for(std::size_t i = 0; i < fileSize; i++) {
        
//     }

//     return returnedVector;
// }

int MetaDataStorage::get_appsCount(void){
    ifstream file;
    string temp;
    int count = 0;

    file.open(fileName);

    while(getline(file, temp)) {
        count++;
    }

    return count;

}

void MetaDataStorage::empty_file(void) {
    ofstream file;

    file.open(this->fileName, ios::out);
    file.close();

    return;
}

// void MetaDataStorage::retrive_AppMetaData(ifstream file, MetaData& metaData) {
    
//     file.open(fileName, ios::binary);
//     file.seekg(0, ios::beg);

//     // temporary variables to carry the data
//     std::string stringTemp;
//     Version versionTemp;
//     unsigned long sizeTemp;


//     // retrieve the platform name
//     file >> stringTemp;
//     metaData.set_platformName(stringTemp);

//     // retrieve the application name
//     file >> stringTemp;
//     metaData.set_appName(stringTemp);
    
//     // retrieve the application ID
//     file >> stringTemp;
//     metaData.set_appID(stringTemp);

//     // retrieve the application version
//     file >> versionTemp.major;
//     file >> versionTemp.minor;
//     file >> versionTemp.patch;
//     metaData.set_version(versionTemp);

//     // retrieve the application size
//     file >> sizeTemp;
//     metaData.set_sizeInBytes(sizeTemp);
    

//     return;
// }
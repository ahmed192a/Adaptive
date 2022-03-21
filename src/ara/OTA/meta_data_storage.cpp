#include "OTA/meta_data_storage.hpp"

using namespace OTA;

MetaDataStorage::MetaDataStorage(std::string fileName) {
    this->fileName = fileName;
    file.open(fileName, std::ios::app);
    file.close();
}

void MetaDataStorage::set_fileName(std::string fileName) {
    this->fileName = fileName;
}

std::string MetaDataStorage::get_fileName() {
    return fileName;
}

void MetaDataStorage::save_MetaData(MetaData & newData) {
    
    file.open(fileName, std::ios::app | std::ios::out);
    file << newData << "\n";
    file.close();

    return;
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

std::size_t MetaDataStorage::get_appsCount(void){
    std::string temp;
    std::size_t count = 0;

    file.open(fileName, std::ios::in);

    while(getline(file, temp)) {
        count++;
    }

    file.close();
    return count;

}

void MetaDataStorage::empty_file(void) {

    file.open(this->fileName, std::ios::out);
    file.close();

    return;
}

void MetaDataStorage::retrieve_LatestMetaData(MetaData& metaData) {
    std::size_t size = get_appsCount();

    file.open(fileName, std::ios::in);
    file.seekg(0, std::ios::beg);
    for(std::size_t i = 0; i < size; i++)
        file >> metaData; // save only the last value

    file.close();
    return;
}
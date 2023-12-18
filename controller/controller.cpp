#include "../include/controller.h"

Controller::Controller(std::string logFilePath) : logger(logFilePath), fileProcessor(logger), hasher() {}

const unsigned char* Controller::hashPath(std::string path) {
    fileMap = fileProcessor.processFiles(path);
    const unsigned char* fullHash = nullptr;
    for (const auto& pair : fileMap) {
        const unsigned char* fileHash = hasher.getHashFile(pair.second.c_str());

        if (fullHash == nullptr){
            fullHash = fileHash;
        } else{
            fullHash = hasher.hashTwoHashes(fileHash, fullHash);
        }
    }
    return fullHash;
}
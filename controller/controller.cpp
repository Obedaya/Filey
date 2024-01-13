#include "../include/controller.h"
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>

Controller::Controller(std::string logFilePath) : logger(logFilePath), fileProcessor(logger), hasher() {}

std::list<const unsigned char*> hashList;

std::list<const unsigned char*> Controller::hashPath(std::string path) {
    FileProcessingResult result = fileProcessor.processFiles(path);
    FileMap fileMap = result.fileMap;
    // Vektor für die Zwischenspeicherung des Hexadezimalstrings
    std::vector<char> hexBuffer;

    // Iteriert über alle Dateien im Ordner und Hasht diese
    for (const auto& pair : fileMap) {
        // Datei wird gehasht
        const unsigned char* fileHash = hasher.getHashFile(pair.second.c_str());

        hashList.push_back(fileHash);
    }
    return hashList;
}

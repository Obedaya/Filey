#include "../include/controller.h"
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>

Controller::Controller(std::string logFilePath) : logger(logFilePath), fileProcessor(logger), hasher() {}

std::list<std::string> hexList;

const unsigned char* Controller::hashPath(std::string path) {
    fileMap = fileProcessor.processFiles(path);
    const unsigned char* fullHash = nullptr;

    // Vektor für die Zwischenspeicherung des Hexadezimalstrings
    std::vector<char> hexBuffer;

    for (const auto& pair : fileMap) {
        const unsigned char* fileHash = hasher.getHashFile(pair.second.c_str());

        if (fullHash == nullptr){
            fullHash = fileHash;
        } else {
            fullHash = hasher.hashTwoHashes(fileHash, fullHash);
        }
    }

    // Manuelle Festlegung der Hash-Größe auf 32 (SHA-256 hat eine Ausgabegröße von 256 Bits / 32 Bytes)
    size_t hashSize = 32;

    // Konvertiere den binären FullHash in einen hexadezimalen String
    for (size_t i = 0; i < hashSize; ++i) {
        hexBuffer.push_back((fullHash[i] & 0xF0) >> 4);
        hexBuffer.push_back(fullHash[i] & 0x0F);
    }

    // Erstelle einen String aus dem Hexadezimal-Buffer
    std::stringstream stream;
    stream << std::hex << std::setfill('0');
    for (const auto& digit : hexBuffer) {
        stream << std::setw(1) << static_cast<int>(digit);
    }

    hexList.push_back(stream.str());

    // Ausgabe der Liste
    for (const auto& hexNumber : hexList) {
        std::cout << hexNumber << " ";
    }

    return fullHash;
}

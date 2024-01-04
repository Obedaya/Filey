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

    // Iteriert über alle Dateien im Ordner und Hasht diese. Alle Hashes werden dann zu einem Hash gehasht
    for (const auto& pair : fileMap) {
        // Datei wird gehasht
        const unsigned char* fileHash = hasher.getHashFile(pair.second.c_str());

        if (fullHash == nullptr){
            fullHash = fileHash;
        } else {
            // Hash wird zu jetztigem Hash hinzugefügt
            fullHash = hasher.hashTwoHashes(fileHash, fullHash);
        }
    }

    // Manuelle Festlegung der Hash-Größe auf 32 (SHA-256 hat eine Ausgabegröße von 256 Bits / 32 Bytes)
    size_t hashSize = 32;

    // Konvertiere den binären FullHash in einen hexadezimalen String
    std::string hexString = hasher.binaryToHex(fullHash, hashSize);

    // Füge den Hexadezimalstring zur Liste hinzu
    hexList.push_back(hexString);

    // Ausgabe der Liste
    for (const auto& hexNumber : hexList) {
        std::cout << hexNumber << " ";
    }

    return fullHash;
}

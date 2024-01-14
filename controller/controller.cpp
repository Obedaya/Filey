#include "../include/controller.h"
#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>

Controller::Controller(std::string logFilePath) : logger(logFilePath), fileProcessor(logger), hasher() {}

void Controller::hashPath(std::string path) {
    // Alle Dateien in dem Directory bekommen
    FileProcessingResult result = fileProcessor.processFiles(path);
    FileMap fileMap = result.fileMap;
    // Aktuelle Liste clearen
    hashList.clear();
    // Vektor für die Zwischenspeicherung des Hexadezimalstrings
    std::vector<char> hexBuffer;

    // Iteriert über alle Dateien im Ordner und Hasht diese
    for (const auto& pair : fileMap) {
        // Datei wird gehasht
        const unsigned char* fileHash = hasher.getHashFile(pair.second.c_str());

        hashList.push_back(fileHash);
    }
}
// Erste Funktion bei Programmstart
int Controller::initializeHash(std::string &path) {
    // Checken ob Datei Pfad überhaupt existiert
    if(!fileProcessor.pathExists(path)){
        std::cerr << "Gegebener Pfad existiert nicht!" << std::endl;
        return -1;
    }
    // Alle Dateien im directory und subdirectories hashen
    hashPath(path);

    // Checken, ob Hash schonmal geshasht wurde oder nicht
    FileMap currentFileMap = fileProcessor.getFileMap();

    for (const auto& pair : currentFileMap) {
        int id = pair.first;
        if (!fileProcessor.hashExists(id, "../hashes/")) {
            // Fall 1: Hash existiert noch nicht:
            // - Hash abspeichern
            if (fileProcessor.saveHash(id, getHashById(id)) == -1){
                // Fehler beim speichern vom Hash
                std::cerr << "Fehler beim speichern von Hash " << id << "!" << std::endl;
                return -1;
            }
        }
        else {
            // Fall 2: Hash existiert bereits:
            // - Mit existierendem Hash vergleichen
            // - Bei gleicher UID abspeichern
            // - Unterschiedliche UID: Alert

        }
    }
}

bool Controller::twoHashesEqual(const unsigned char *firstHash, const unsigned char *secondHash) {
    if (firstHash == secondHash){
        return true;
    }
    else {
        return false;
    }
}

const unsigned char* Controller::getHashById(int id) {
    if (id >= hashList.size()) {
        std::cerr << "ID " << id << " ist nicht in der Liste" << std::endl;
        return nullptr;
    }

    auto it = hashList.begin();
    std::advance(it, id);
    return *it;
}
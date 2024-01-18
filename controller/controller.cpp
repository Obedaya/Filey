#include "../include/controller.h"
#include "../logger/logger.cpp"
#include "../hasher/hasher.cpp"
#include "../fileprocessor/fileprocessor.cpp"

Controller::Controller(const std::string& logFilePath) : logger(logFilePath), fileProcessor(logger), hasher(logger), view() {}


void Controller::hashPath() {
    // Alle Dateien in dem Directory bekommen
    FileMap current_file_map = fileProcessor.getFileMap();
    // Aktuelle Liste leeren
    hash_list.clear();
    // Vektor für die Zwischenspeicherung des Hexadezimalstrings
    std::vector<char> hex_buffer;

    // Iteriert über alle Dateien im Ordner und Hasht diese
    for (const auto& pair : current_file_map) {
        int file_id = pair.first;
        const char* file_path = pair.second.c_str();
        // Datei wird gehasht
        const unsigned char* file_hash = hasher.getHashFile(file_path);

        hash_list[file_id] = file_hash;
    }
}

int Controller::initializeHash(bool force_flag) {
    // Alle Dateien im directory und subdirectories hashen
    hashPath();

    // Checken, ob Hash schonmal geshasht wurde oder nicht
    FileMap currentFileMap = fileProcessor.getFileMap();

    for (const auto& pair : currentFileMap) {
        int id = pair.first;
        std::string current_hash_path = pair.second;
        const unsigned char* current_hash = getHashById(id);
        const unsigned char* existing_hash = fileProcessor.hashExists(current_hash_path, "../hashes/");
        if (existing_hash == nullptr) {
            // Fall 1: Hash existiert noch nicht:
            // - Hash abspeichern
            if (fileProcessor.saveHash(id, current_hash) == -1){
                // Fehler beim Speichern vom Hash
                logger.printAndLog("Fehler beim speichern von Hash: " + std::to_string(id) + "!", true);
                return -1;
            }
            logger.printAndLog("Neuer Hash von Datei: " + current_hash_path + " und ID: " + std::to_string(id) + " wurde erstellt!", false);
        }
        else {
            // Fall 2: Hash existiert bereits:
            // - Mit existierendem Hash vergleichen
            // - Wenn force_flag gesetzt ist, hash überschreiben

            if (twoHashesEqual(existing_hash, current_hash)){
                // Hashes sind gleich, keine changes wurden gemacht
                logger.printAndLog("Datei: " + current_hash_path + " mit ID: " + std::to_string(id) + " hat sich nicht verändert!", false);
            } else{
                logger.printAndLog("Hash hat sich verändert: " + current_hash_path, true);

                // Hash überschreiben, wenn force_flag gesetzt
                if (force_flag){
                    if (fileProcessor.saveHash(id, current_hash) == -1){
                        // Fehler beim Speichern vom Hash
                        logger.printAndLog("Fehler beim speichern von Hash " + std::to_string(id) + "!", true);
                        return -1;
                    }
                    logger.printAndLog("Neuer Hash von Datei: " + current_hash_path + " und ID: " + std::to_string(id) + " wurde gespeichert!", false);
                }
            }
        }
    }
    return 0;
}



bool Controller::twoHashesEqual(const unsigned char *first_hash, const unsigned char *second_hash) {
    if (std::memcmp(first_hash, second_hash, Hasher::HASH_SIZE) == 0){
        return true;
    }
    else {
        return false;
    }
}

const unsigned char* Controller::getHashById(int id) {
    if (id >= hash_list.size()) {
        logger.printAndLog("ID: " + std::to_string(id) + " ist nicht in der Liste", true);
        return nullptr;
    }
    return hash_list[id];
}

int Controller::initializeProgram(int argc, char **argv) {
    // Input validieren und aus arguments lesen
    auto [help_flag, user_path, recursive_flag, force_flag] = View::getInput(argc, argv);
    // Beende das Programm, wenn Command falsch verwendet wurde oder der Pfad falsch oder nicht gegeben ist
    if (help_flag || user_path.empty()){
        return -1;
    }

    try {
        // Pfad von relativen zu absoluten Pfad ändern
        user_path = fileProcessor.sanitizePath(user_path);
    } catch (const fs::filesystem_error& e) {
        logger.printAndLog("Filesystem error: " + std::string(e.what()), true);
        return -1;
    }

    // Checken ob Datei Pfad überhaupt existiert
    if (!fileProcessor.pathExists(user_path)){
        logger.printAndLog("Ordner oder Datei existiert nicht!", true);
        return -1;
    }
    fileProcessor.processFiles(user_path, recursive_flag);
    if (initializeHash(force_flag) == -1){
        logger.printAndLog("Fehler beim Hashen der Dateien!", true);
        return -1;
    }
    return 0;
}
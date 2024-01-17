#include "../include/controller.h"

Controller::Controller(const std::string& logFilePath) : logger(logFilePath), fileProcessor(logger), hasher(), view() {}

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
                // Fehler beim speichern vom Hash
                std::cerr << "Fehler beim speichern von Hash " << id << "!" << std::endl;
                return -1;
            }
            std::cout << "Neuer Hash von Datei: " << current_hash_path << " und ID: " << id << " wurde erstellt!" << std::endl;
        }
        else {
            // Fall 2: Hash existiert bereits:
            // - Mit existierendem Hash vergleichen
            // - Wenn force_flag gesetzt ist, hash überschreiben

            if (twoHashesEqual(existing_hash, current_hash)){
                // Hashes sind gleich keine changes wurden gemacht
                std::cout << "Datei: " << current_hash_path << " mit ID: " << id << " hat sich nicht verändert!" << std::endl;
            } else{
                std::cout << "ALLAAAAARM bei: " << current_hash_path << std::endl;

                // Hash überschreiben wenn force_flag gesetzt
                if (force_flag){
                    if (fileProcessor.saveHash(id, current_hash) == -1){
                        // Fehler beim speichern vom Hash
                        std::cerr << "Fehler beim speichern von Hash " << id << "!" << std::endl;
                        return -1;
                    }
                    std::cout << "Neuer Hash von Datei: " << current_hash_path << " und ID: " << id << " wurde gespeichert!" << std::endl;
                }
            }
        }
    }
    return 0;
}



bool Controller::twoHashesEqual(const unsigned char *first_hash, const unsigned char *second_hash) {
    if (std::memcmp(first_hash, second_hash, 32) == 0){
        return true;
    }
    else {
        return false;
    }
}

const unsigned char* Controller::getHashById(int id) {
    if (id >= hash_list.size()) {
        std::cerr << "ID " << id << " ist nicht in der Liste" << std::endl;
        return nullptr;
    }
    return hash_list[id];
}

int Controller::initializeProgram(int argc, char **argv) {
    // Input validieren und aus arguments lesen
    auto [help_flag, user_path, recursive_flag, force_flag] = view.getInput(argc, argv);
    // Beende das Programm, wenn Command falsch verwendet wurde oder der Pfad falsch oder nicht gegeben ist
    if (help_flag || user_path.empty()){
        return -1;
    }
    // Checken ob Datei Pfad überhaupt existiert
    if (!fileProcessor.pathExists(user_path)){
        std::cerr << "Ordner oder Datei existiert nicht!" << std::endl;
        return -1;
    }
    fileProcessor.processFiles(user_path, recursive_flag);
    if (initializeHash(force_flag) == -1){
        std::cerr << "Fehler beim hashen der Dateien" << std::endl;
        return -1;
    }
    return 0;
}
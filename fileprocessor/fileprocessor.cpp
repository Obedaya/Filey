#include "../include/fileprocessor.h"

FileProcessor::FileProcessor(Logger& logger) : logger(logger) {}

void FileProcessor::processFiles(const std::string& path, bool recursive_flag) {
    // Leert Filemap
    file_map.clear();
    int id = 0;

    // Ordner rekursiv oder nicht rekursiv durchlaufen
    if (recursive_flag){
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
            // Generiert einzigartige ID
            file_map[id] = entry.path().string();
            id++;
        }
    }
    else {
        for (const auto &entry: std::filesystem::directory_iterator(path)) {
            // Generiert einzigartige ID
            file_map[id] = entry.path().string();
            id++;
        }
    }

    // FileMap loggen
    logger.addFileMapLog(file_map);
}

const FileMap& FileProcessor::getFileMap() const {
    return file_map;
}

int FileProcessor::saveHash(const int id, const unsigned char* hash) {
    std::string error_message;
    if (file_map.find(id) == file_map.end()) {

        logger.printAndLog("File ID " + std::to_string(id) + " konnte nicht in der FileMap gefunden werden.", true);
        return -1;
    }

    std::string original_path = file_map[id];
    std::string flattened_path;

    // Ersetzt '/' und '\' mit '_' um den Dateinamen schöner zu machen
    flattened_path = generateFilename(original_path);

    std::string hash_file_name = "../hashes/" + flattened_path + ".hash";

    // Sicherstellen, dass Ordner existiert
    std::filesystem::create_directories(std::filesystem::path(hash_file_name).parent_path());

    // Hashes in die Datei schreiben
    std::ofstream hash_file(hash_file_name, std::ios::binary);
    if (hash_file) {
        hash_file.write(reinterpret_cast<const char*>(hash), Hasher::HASH_SIZE);
        hash_file.close();

        // Rechte verwalten (owner kann lesen und schreiben)
        std::filesystem::permissions(hash_file_name,
                                     std::filesystem::perms::owner_read | std::filesystem::perms::owner_write);
    } else {
        logger.printAndLog("Datei konnte nicht geöffnet werden: " + hash_file_name, true);
        return -1;
    }
    return 0;
}

bool FileProcessor::pathExists(std::string &path) {
    return std::filesystem::exists(path);
}

const unsigned char* FileProcessor::hashExists(const std::string& path, const std::string& directory_path) {
    // Dateinamen erstellen
    std::string hash_file_name = generateFilename(path) + ".hash";

    try {
        // Checken ob Ordner existiert
        if (!fs::exists(directory_path) || !fs::is_directory(directory_path)) {
            logger.printAndLog("Ordner existiert nicht: " + directory_path, true);
            return nullptr;
        }

        // Durch Hash Ordner durchgehen
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            // Checken, ob aktuelle Datei gesuchter Hash ist
            if (fs::is_regular_file(entry) && entry.path().filename() == hash_file_name) {
                // Datei öffnen und Hash auslesen
                std::ifstream hash_file(entry.path(), std::ios::binary);
                if (hash_file) {
                    // Speicher für Hash reservieren
                    auto* hash = new unsigned char[Hasher::HASH_SIZE];
                    // Hash auslesen
                    hash_file.read(reinterpret_cast<char*>(hash), Hasher::HASH_SIZE);
                    hash_file.close();

                    return hash;
                } else {
                    logger.printAndLog("Datei konnte nicht geöffnet werden: " + std::string(entry.path()), true);
                    return nullptr;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        logger.printAndLog("Filesystem error: " + std::string(e.what()), true);
    }

    return nullptr;
}

std::string FileProcessor::generateFilename(const std::string& original_path) {
    std::string flattened_path;

    for (char ch : original_path) {
        if (ch == '/' || ch == '\\') {
            flattened_path += '_';
        } else {
            flattened_path += ch;
        }
    }
    return flattened_path;
}

// Wird nicht verwendet
uid_t FileProcessor::getLastModifiedUid(const std::string& filepath) {
    struct stat file_info{};
    if (stat(filepath.c_str(), &file_info) == 0) {
        return file_info.st_uid;
    } else {
        perror("stat");
        return static_cast<uid_t>(-1);
    }
}
#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include <unistd.h>
#include <sys/stat.h>

FileProcessor::FileProcessor(Logger& logger) : logger(logger) {}

FileProcessingResult FileProcessor::processFiles(const std::string& path) {
    // Leert Filemap
    fileMap.clear();
    UserMap userMap;
    int id = 0;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        // Generiert einzigartige ID
        fileMap[id] = entry.path().string();
        // UserID erhalten und speicehrn (jetztiger User)
        userMap[id] = getLastModifiedUid(entry.path().string());

        id++;
    }

    // FileMap loggen
    logger.createAndLog(fileMap);

    // Return Objekt erstellen und zurückgeben
    FileProcessingResult result;
    result.fileMap = fileMap;
    result.userMap = userMap;

    return result;
}

const FileMap& FileProcessor::getFileMap() const {
    return fileMap;
}

int FileProcessor::saveHash(const int id, const unsigned char* hash) {
    if (fileMap.find(id) == fileMap.end()) {
        std::cerr << "File ID " << id << " konnte nicht in der FileMap gefunden werden." << std::endl;
        return -1;
    }

    std::string originalPath = fileMap[id];
    std::string flattenedPath;

    // Ersetzt '/' und '\' mit '_' um den Dateinamen schöner zu machen
    flattenedPath = generateFilename(originalPath);

    std::string hashFileName = "../hashes/" + flattenedPath + ".hash";

    // Sicherstellen, dass Ordner existiert
    std::filesystem::create_directories(std::filesystem::path(hashFileName).parent_path());

    // Hashes in die Datei schreiben
    std::ofstream hashFile(hashFileName, std::ios::binary);
    if (hashFile) {
        hashFile.write(reinterpret_cast<const char*>(hash), Hasher::HASH_SIZE);
        hashFile.close();

        // Rechte verwalten (owner kann lesen und schreiben)
        std::filesystem::permissions(hashFileName,
                                     std::filesystem::perms::owner_read | std::filesystem::perms::owner_write);
    } else {
        std::cerr << "Datei konnte nicht geöffnet werden: " << hashFileName << std::endl;
        return -1;
    }
    return 0;
}

bool FileProcessor::pathExists(std::string &path) {
    return std::filesystem::exists(path);
}

const unsigned char* FileProcessor::hashExists(const std::string& path, const std::string& directoryPath) {
    // Dateinamen erstellen
    std::string hashFileName = generateFilename(path) + ".hash";

    try {
        // Checken ob Ordner existiert
        if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
            std::cerr << "Ordner existiert nicht! " << directoryPath << std::endl;
            return nullptr;
        }

        // Durch Hash Ordner durchgehen
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            // Checken ob aktuelle Datei gesuchter Hash ist
            if (fs::is_regular_file(entry) && entry.path().filename() == hashFileName) {
                // Datei öffnen und Hash auslesen
                std::ifstream hashFile(entry.path(), std::ios::binary);
                if (hashFile) {
                    // Speicher für Hash reservieren
                    unsigned char* hash = new unsigned char[Hasher::HASH_SIZE];
                    // Hash auslesen
                    hashFile.read(reinterpret_cast<char*>(hash), Hasher::HASH_SIZE);
                    hashFile.close();

                    return hash;
                } else {
                    std::cerr << "Datei konnte nicht geöffnet werden: " << entry.path() << std::endl;
                    return nullptr;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }

    return nullptr;
}

std::string FileProcessor::generateFilename(std::string originalPath) {
    std::string flattenedPath;

    for (char ch : originalPath) {
        if (ch == '/' || ch == '\\') {
            flattenedPath += '_';
        } else {
            flattenedPath += ch;
        }
    }
    return flattenedPath;
}

// Wird nicht verwendet
uid_t FileProcessor::getLastModifiedUid(const std::string& filepath) {
    struct stat fileInfo;
    if (stat(filepath.c_str(), &fileInfo) == 0) {
        return fileInfo.st_uid;
    } else {
        perror("stat");
        return static_cast<uid_t>(-1);
    }
}
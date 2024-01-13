#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include <unistd.h>

FileProcessor::FileProcessor(Logger& logger) : logger(logger) {}

FileProcessingResult FileProcessor::processFiles(const std::string& path) {
    FileMap fileMap;
    UserMap userMap;
    int id = 1;

    for (const auto& entry : fs::directory_iterator(path)) {
        // Eindeutige ID generieren
        std::string uniqueID = std::to_string(id);

        // Dateipfad und eindeutige ID speichern
        fileMap[id] = entry.path().string();
        // UserID speichern
        userMap[id] = getuid();

        id++;
    }

    // Logger verwenden, um die Log-Datei zu erstellen oder zu erweitern
    logger.createAndLog(fileMap);

    // Ergebnisobjekt erstellen und Dateipfade sowie UserIDs speichern
    FileProcessingResult result;
    result.fileMap = fileMap;
    result.userMap = userMap;

    return result;
}

void FileProcessor::saveHashes(const std::list<const unsigned char*>& hashes) {
    // Speichern der Hashes mit geeignetem Dateinamen und Rechten
    // Hash wird z.B. in eine separate Datei mit der Erweiterung ".hash" geschrieben
    int id = 1;
    for (const auto& hash : hashes) {
        std::string filePath = fileMap[id];
        std::string hashFileName = filePath + ".hash";

        std::ofstream hashFile(hashFileName, std::ios::binary);
        hashFile.write(reinterpret_cast<const char*>(hash), Hasher::HASH_SIZE);
        hashFile.close();

        // hier werden die gewünschten Rechte für die Hash-Datei gesetzt (Beispiel: Lese- und Schreibrechte für den Eigentümer)
        fs::permissions(hashFileName, fs::perms::owner_read | fs::perms::owner_write, fs::perm_options::add);

        id++;
    }
}

#include "../include/fileprocessor.h"

FileProcessor::FileProcessor(Logger& logger) : logger(logger) {}

//TODO: UID mitspeichern (Metadaten)
FileMap FileProcessor::processFiles(const std::string& path) {
    FileMap fileMap;
    int id = 1;

    for (const auto& entry : fs::directory_iterator(path)) {
        fileMap[id++] = entry.path().string();
    }

    // Logger verwenden, um die Log-Datei zu erstellen oder zu erweitern
    logger.createAndLog(fileMap);

    return fileMap;
}

// TODO: Hashes speichern mit richtigen Rechten und geignetem Dateinamen
void FileProcessor::saveHashes(std::list<const unsigned char *> hashes) {

}

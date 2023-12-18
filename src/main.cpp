#include "../include/logger.h"
#include "../include/fileprocessor.h"
#include "../include/hasher.h"

int main() {
    std::string path = "../files";
    std::string logFilePath = "../logs/log.txt";

    Logger logger(logFilePath);
    FileProcessor fileProcessor(logger);
    Hasher hasher;

    FileMap fileMap = fileProcessor.processFiles(path);


    // Ausgabe der gespeicherten Key-Value-Paare
    for (const auto& pair : fileMap) {
        std::cout << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
    }

    Logger Logger(logFilePath);

    // Funktion aufrufen, um Log-Datei zu erstellen
    logger.createAndLog(fileMap);

    // Beispiel für die Nutzung der addLog-Funktion
    logger.addLog("Bingbong");

    // Beispiel für die Nutzung des Hashers
    hasher.getHashFile("../README.md");
    return 0;
}

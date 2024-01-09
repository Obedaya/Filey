#include "../include/logger.h"
#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include "../include/controller.h"

#include <list>

int main() {
    std::string path = "../files";
    std::string logFilePath = "../logs/log.txt";

    Logger logger(logFilePath);
    FileProcessor fileProcessor(logger);
    Hasher hasher;
    Controller controller(logFilePath);

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
    std::cout << hasher.binaryToHex(hasher.getHashFile("../README.md"), 32) << std::endl;

    const unsigned char* hash1 = hasher.hashFileContent("../files/text1.txt");
    const unsigned char* hash2 = hasher.hashFileContent("../files/text2.txt");

    std::cout << "Inhalt:" << hasher.binaryToHex(hash1, 32) << std::endl;
    std::cout << "Inhalt:" << hasher.binaryToHex(hash2, 32) << std::endl;

    // Beispiel für die Nutzung des Controllers

    std::list<const unsigned char*> hashes = controller.hashPath("../files");

    for (const auto& hash : hashes) {
        std::cout << hasher.binaryToHex(hash, 32) << std::endl;
    }

    return 0;
}
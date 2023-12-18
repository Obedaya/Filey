#include "../include/logger.h"
#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include "../include/controller.h"

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

    const unsigned char* hash1 = hasher.getHashFile("../files/text1.txt");
    const unsigned char* hash2 = hasher.getHashFile("../files/text1.txt");

    std::cout << hasher.binaryToHex(hasher.hashTwoHashes(hash1, hash2), 32) << std::endl;

    // Beispiel für die Nutzung des Controllers

    const unsigned char* hashes = controller.hashPath("../files");

    std::cout << hasher.binaryToHex(hashes, 32) << std::endl;

    return 0;
}
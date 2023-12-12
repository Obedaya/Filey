#include "../include/logger.h"
#include "../include/fileprocessor.h"

int main() {
    std::string path = "../files";
    std::string logFilePath = "../logs/log.txt";

    Logger logger(logFilePath);
    FileProcessor fileProcessor(logger);

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
    return 0;
}

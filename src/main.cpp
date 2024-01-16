//==========================================================
//   ________  _   __
//  |_   __  |(_) [  |
//    | |_ \_|__   | | .---.   _   __
//    |  _|  [  |  | |/ /__\\ [ \ [  ]
//   _| |_    | |  | || \__.,  \ '/ /
//  |_____|  [___][___]'.__.'[\_:  /
//                          \__.'
//============================================================
//
// File integrity checker, to check the integrity of directories and folders
//


#include "../include/logger.h"
#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include "../include/controller.h"
#include "../include/view.h"

#include <list>

// TODO: Logik implementieren
// TODO: Programm starten implementieren
// TODO: Inotify implementiern
int main(int argc, char* argv[]) {
    bool programRunning = true;

    std::string path = "../files/";
    std::string logFilePath = "../logs/log.txt";

    Logger logger(logFilePath);
    FileProcessor fileProcessor(logger);
    Hasher hasher;
    Controller controller(logFilePath);
   // View view;
/*
    std::cout << fileProcessor.pathExists(path) << std::endl;

    FileProcessingResult result = fileProcessor.processFiles(path);
    FileMap file_map = result.file_map;

    // Ausgabe der gespeicherten Key-Value-Paare
    for (const auto& pair : file_map) {
        std::cout << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
    }

    Logger Logger(log_file_path);

    // Funktion aufrufen, um Log-Datei zu erstellen
    logger.createAndLog(file_map);

    // Beispiel für die Nutzung der addLog-Funktion
    logger.addLog("Bingbong");

    // Beispiel für die Nutzung des Hashers
    std::cout << hasher.binaryToHex(hasher.getHashFile("../README.md"), 32) << std::endl;

    const unsigned char* hash1 = hasher.hashFileContent("../files/text1.txt");
    const unsigned char* hash2 = hasher.hashFileContent("../files/text2.txt");

    std::cout << "Inhalt:" << hasher.binaryToHex(hash1, 32) << std::endl;
    std::cout << "Inhalt:" << hasher.binaryToHex(hash2, 32) << std::endl;

    // Beispiel für die Nutzung des Controllers
*/
    if (controller.initializeProgram(argc, argv)) {
        return -1;
    }
    return 0;
}
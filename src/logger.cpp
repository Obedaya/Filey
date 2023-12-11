#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <fstream>

    namespace fs = std::filesystem;
    using FileMap = std::unordered_map<int, std::string>;

// Funktion zum Erstellen einer Log-Datei und Logging wesentlicher Schritte
    void createAndLog(const FileMap& fileMap) {
        std::ofstream logFile("../logs/log.txt");

        if (logFile.is_open()) {
            logFile << "Log-Datei für wesentliche Schritte" << std::endl;

            for (const auto& pair : fileMap) {
                logFile << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
            }

            logFile << "Log abgeschlossen." << std::endl;

            logFile.close();
            std::cout << "Log-Datei erstellt: log.txt" << std::endl;
        } else {
            std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
        }
    }

// Funktion zum Hinzufügen eines Logs zu einer vorhandenen Log-Datei
    void addLog(const std::string& logText) {
        std::ofstream logFile("../logs/log.txt", std::ios::app);  // std::ios::app öffnet die Datei im Anhänge-Modus

        if (logFile.is_open()) {
            logFile << logText << std::endl;
            logFile.close();
        } else {
            std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
        }
    }

    int main() {
        std::string path = "../files";
        FileMap fileMap;

        int id = 1;

        for (const auto &entry : fs::directory_iterator(path)) {
            fileMap[id++] = entry.path().string();
        }

        // Ausgabe der gespeicherten Key-Value-Paare
        for (const auto &pair : fileMap) {
            std::cout << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
        }

        // Funktion aufrufen, um Log-Datei zu erstellen
        createAndLog(fileMap);

        // Beispiel für die Nutzung der addLog-Funktion
        addLog("Bingbong");

        return 0;
    }

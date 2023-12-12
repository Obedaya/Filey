#include "../include/logger.h"

Logger::Logger(const std::string& logFilePath) : logFilePath(logFilePath) {}

void Logger::createAndLog(const FileMap& fileMap) const {
    std::ofstream logFile(logFilePath, std::ios::app);

    if (logFile.is_open()) {
        logFile << "Log-Datei für wesentliche Schritte" << std::endl;

        for (const auto& pair : fileMap) {
            logFile << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
        }

        logFile << "Log abgeschlossen." << std::endl;

        logFile.close();
        std::cout << "Log-Datei erstellt: " << logFilePath << std::endl;
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}

void Logger::addLog(const std::string& logText) const {
    std::ofstream logFile(logFilePath, std::ios::app);

    if (logFile.is_open()) {
        logFile << logText << std::endl;
        logFile.close();
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}
#include "../include/logger.h"

Logger::Logger(const std::string& log_file_path) : log_file_path(log_file_path) {}

void Logger::createAndLog(const FileMap& file_map) const {
    std::ofstream log_file(log_file_path, std::ios::app);

    if (log_file.is_open()) {
        log_file << "Log-Datei für wesentliche Schritte" << std::endl;

        for (const auto& pair : file_map) {
            log_file << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
        }

        log_file << "Log abgeschlossen." << std::endl;

        log_file.close();
        std::cout << "Log-Datei erstellt: " << log_file_path << std::endl;
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}

void Logger::addLog(const std::string& log_text) const {
    std::ofstream log_file(log_file_path, std::ios::app);

    if (log_file.is_open()) {
        log_file << log_text << std::endl;
        log_file.close();
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}
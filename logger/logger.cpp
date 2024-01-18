#include <utility>

#include "../include/logger.h"

Logger::Logger(std::string  log_file_path) : log_file_path(std::move(log_file_path)) {}

void Logger::addFileMapLog(const FileMap& file_map) const{
    std::ofstream log_file(log_file_path, std::ios::app);
    std::string time_now = getCurrentTime();

    if (log_file.is_open()) {
        for (const auto& pair : file_map) {
            log_file << time_now << "Datei gefunden in: " << pair.second << std::endl;
        }

        log_file.close();
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}

void Logger::addLog(const std::string& log_text) const {
    std::ofstream log_file(log_file_path, std::ios::app);
    std::string time_now = getCurrentTime();

    if (log_file.is_open()) {
        log_file << time_now << log_text << std::endl;
        log_file.close();
    } else {
        std::cerr << "Fehler beim Öffnen der Log-Datei!" << std::endl;
    }
}

std::string Logger::getCurrentTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "[%Y-%m-%dT%H:%M:%S]", &tm);

    return std::string(buffer);
}

void Logger::printAndLog(const std::string &log_text, bool error) const {
    if (error) {
        std::cerr << log_text << std::endl;
    } else {
        std::cout << log_text << std::endl;
    }
    addLog(log_text);
}
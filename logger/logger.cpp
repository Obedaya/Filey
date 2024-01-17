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

std::string Logger::getCurrentTime() const{
    time_t now = time(0);

    std::string dt = ctime(&now);

    dt.erase(dt.end() - 2, dt.end());

    return "[" + dt + "] ";
}

void Logger::printAndLog(const std::string &log_text, bool error) {
    if (error) {
        std::cerr << log_text << std::endl;
    } else {
        std::cout << log_text << std::endl;
    }
    addLog(log_text);
}
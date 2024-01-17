#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <list>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <ctime>

using FileMap = std::unordered_map<int, std::string>;

class Logger {
public:
    explicit Logger(std::string  log_file_path);

    void addFileMapLog(const FileMap& file_map) const;

    void addLog(const std::string& log_text) const;

    [[nodiscard]] std::string getCurrentTime() const;

    void printAndLog(const std::string& log_text, bool error);

private:
    const std::string log_file_path;
};

#endif // LOGGER_H
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using FileMap = std::unordered_map<int, std::string>;

class Logger {
public:
    explicit Logger(const std::string& logFilePath);

    void createAndLog(const FileMap& fileMap) const;

    void addLog(const std::string& logText) const;

private:
    const std::string logFilePath;
};

#endif // LOGGER_H
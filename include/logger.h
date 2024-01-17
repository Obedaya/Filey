#ifndef LOGGER_H
#define LOGGER_H

#pragma once

#include <list>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

using FileMap = std::unordered_map<int, std::string>;

class Logger {
public:
    explicit Logger(const std::string& log_file_path);

    void createAndLog(const FileMap& file_map) const;

    void addLog(const std::string& log_text) const;


private:
    const std::string log_file_path;
};

#endif // LOGGER_H
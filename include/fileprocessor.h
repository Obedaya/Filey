#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>
#include <list>
#include <map>
#include "logger.h"

namespace fs = std::filesystem;

using FileMap = std::unordered_map<int, std::string>; // Verwenden von unordered_map anstelle von map

using UserMap = std::map<int, uid_t>;

struct FileProcessingResult {
    FileMap fileMap;
    UserMap userMap;
};

class FileProcessor {
public:
    explicit FileProcessor(Logger& logger);

    [[nodiscard]] FileProcessingResult processFiles(const std::string& path);

    void saveHashes(const std::list<const unsigned char*>& hashes);

private:
    Logger& logger;
    std::map<int, std::string> fileMap;

};

#endif // FILEPROCESSOR_H
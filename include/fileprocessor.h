#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
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
    const FileMap& getFileMap() const;
    int saveHash(const int id, const unsigned char* hash);
    bool pathExists(std::string &path);
    const unsigned char* hashExists(const std::string& path, const std::string& directoryPath);
    uid_t getLastModifiedUid(const std::string& filepath);
private:
    Logger& logger;
    FileMap fileMap;
    std::string generateFilename(std::string originalPath);
};

#endif // FILEPROCESSOR_H
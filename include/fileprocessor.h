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
#include <sys/stat.h>
#include "logger.h"
#include "hasher.h"

namespace fs = std::filesystem;

using FileMap = std::unordered_map<int, std::string>; // Verwenden von unordered_map anstelle von map

using UserMap = std::map<int, uid_t>;

class FileProcessor {
public:
    explicit FileProcessor(Logger& logger);
    void processFiles(const std::string& path);
    const FileMap& getFileMap() const;
    int saveHash(const int id, const unsigned char* hash);
    bool pathExists(std::string &path);
    const unsigned char* hashExists(const std::string& path, const std::string& directory_path);
    uid_t getLastModifiedUid(const std::string& filepath);
private:
    Logger& logger;
    FileMap file_map;
    std::string generateFilename(const std::string& original_path);
};

#endif // FILEPROCESSOR_H
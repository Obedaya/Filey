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

class FileProcessor {
public:
    explicit FileProcessor(Logger& logger);
    void processFiles(const std::string& path, bool recursive_flag);
    const FileMap& getFileMap() const;
    int saveHash(int id, const unsigned char* hash, const std::string& output_path);
    static bool pathExists(std::string &path);
    const unsigned char* hashExists(const std::string& path, const std::string& directory_path);
    static std::string sanitizePath(const std::string& path);
private:
    Logger& logger;
    FileMap file_map;
    static std::string generateFilename(const std::string& original_path);
};

#endif // FILEPROCESSOR_H
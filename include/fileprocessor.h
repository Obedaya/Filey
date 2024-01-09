#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <filesystem>
#include <unordered_map>
#include <string>
#include <list>
#include "logger.h"

namespace fs = std::filesystem;

class FileProcessor {
public:
    explicit FileProcessor(Logger& logger);

    [[nodiscard]] FileMap processFiles(const std::string& path);

    void saveHashes(std::list<const unsigned char*> hashes);
private:
    Logger& logger;
};

#endif // FILEPROCESSOR_H
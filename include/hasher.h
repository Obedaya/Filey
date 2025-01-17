#ifndef FILEY_HASHER_H
#define FILEY_HASHER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstddef> // Für std::size_t
#include <openssl/sha.h>
#include <openssl/evp.h>
#include "logger.h"


class Hasher {
public:
    explicit Hasher(Logger& logger);
    const unsigned char* getHashFile(const char *path);
    static constexpr std::size_t HASH_SIZE = 32;
    static std::string binaryToHex(const unsigned char* data, size_t length);
private:
    Logger& logger;
    const unsigned char* hashFilePath(const char *path);
    const unsigned char* hashFileContent(const char *path);
    const unsigned char* hashTwoHashes(const unsigned char* hash1, const unsigned char* hash2);
};


#endif //FILEY_HASHER_H

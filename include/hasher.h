#ifndef FILEY_HASHER_H
#define FILEY_HASHER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/evp.h>


class Hasher {
public:
    explicit Hasher();
    const unsigned char* getHashFile(const char *path);
    const unsigned char* hashTwoHashes(const unsigned char* hash1, const unsigned char* hash2);
    std::string binaryToHex(const unsigned char* data, size_t length);
private:
};


#endif //FILEY_HASHER_H

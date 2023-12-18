//
// Created by simon on 12.12.23.
//

#ifndef FILEY_HASHER_H
#define FILEY_HASHER_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/evp.h>


class Hasher {
public:
    explicit Hasher();

    std::string getHashFile(const char *path);
private:
};


#endif //FILEY_HASHER_H

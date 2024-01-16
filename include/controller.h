#ifndef FILEY_CONTROLLER_H
#define FILEY_CONTROLLER_H

#include <iostream>
#include <list>
#include <iostream>
#include <vector>
#include "fileprocessor.h"
#include "hasher.h"
#include "logger.h"
#include "view.h"

class Controller {
public:
    explicit Controller(std::string logFilePath);
    void hashPath();
    int initializeHash(std::string &path);
    bool twoHashesEqual(const unsigned char* first_hash, const unsigned char* second_hash);
    int initializeProgram(int argc, char* argv[]);
private:
    Logger logger;
    FileProcessor fileProcessor;
    Hasher hasher;
    View view;

    std::map<int, const unsigned char*> hash_list;

    const unsigned char* getHashById(int id);
};


#endif //FILEY_CONTROLLER_H

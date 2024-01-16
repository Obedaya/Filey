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
    void hashPath(std::string path);
    int initializeHash(std::string &path);
    bool twoHashesEqual(const unsigned char* firstHash, const unsigned char* secondHash);
    int initializeProgram(int argc, char* argv[]);
private:
    Logger logger;
    FileProcessor fileProcessor;
    Hasher hasher;
    FileMap fileMap;
    View view;

    std::list<const unsigned char*> hashList;

    const unsigned char* getHashById(int id);
};


#endif //FILEY_CONTROLLER_H

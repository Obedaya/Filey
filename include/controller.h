#ifndef FILEY_CONTROLLER_H
#define FILEY_CONTROLLER_H

#include <iostream>
#include "../include/fileprocessor.h"
#include "../include/hasher.h"
#include "../include/logger.h"

class Controller {
public:
    explicit Controller(std::string logFilePath);
    const unsigned char* hashPath(std::string path);
private:
    Logger logger;
    FileProcessor fileProcessor;
    Hasher hasher;

    FileMap fileMap;
};


#endif //FILEY_CONTROLLER_H

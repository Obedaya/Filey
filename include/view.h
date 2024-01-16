#ifndef FILEY_VIEW_H
#define FILEY_VIEW_H

#include <map>
#include <string>
#include <iostream>
#include <regex>


class View {
public:
    explicit View();
    int getInput(int argc, char **argv);
    std::map<std::string, std::string> extractArguments(int argc, char* argv[]);
private:
    void printHelp();
};


#endif //FILEY_VIEW_H

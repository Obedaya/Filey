#ifndef FILEY_VIEW_H
#define FILEY_VIEW_H

#include <map>
#include <string>
#include <iostream>
#include <regex>
#include <tuple>

class View {
public:
    explicit View();
    static std::tuple<bool, std::string, std::string, bool, bool> getInput(int argc, char **argv);
    static std::map<std::string, std::string> extractArguments(int argc, char* argv[]);
private:
    static void printHelp();
};


#endif //FILEY_VIEW_H

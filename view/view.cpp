#include "../include/view.h"
#include <string>

View::View() {}

std::string View::getInput(int argc, char* argv[]) {
    auto args = extractArguments(argc, argv);
    //std::regex path_regex_template("^(/[^/ ]*)+/?$");

    // Hier können alle optionalen commandline Argumente hin

    // Pfad angeben
    if (args.find("-p") != args.end()) {
        std::string path_value = args["-p"];
        if (path_value == "") {
            printHelp();
            return "";
        }
        else{
            // Regex überprüfung von Pfad (schwierig)
//            if (std::regex_match (path_value, path_regex)) {
//                return path_value;
//            }
//            else {
//                printHelp();
//                return "";
//            }
            return path_value;
        }
    }
}

// Methode zum speichern der Commandline Argumente in einer Map
std::map<std::string, std::string> View::extractArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            // Überprüfen ob nächstes Argument ein Wert ist
            if (i + 1 < argc) {
                args[arg] = argv[++i];
            } else {
                args[arg] = "";
            }
        }
    }
    return args;
}

void View::printHelp() {
    std::cout << "Usage: ./filey -p path [options]...\n"
                 "Filey file integrity checker\n"
                 "\t-p path\n"
                 "\t\t Path to file or directory to check integrity" << std::endl;
}
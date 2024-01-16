#include "../include/view.h"
#include <string>

View::View() {}

int View::getInput(int argc, char* argv[]) {
    auto args = extractArguments(argc, argv);

    // Hier können alle optionalen commandline Argumente hin

    // Pfad angeben
    if (args.find("-p") != args.end()) {
        std::string path_value = args["-p"];
        if (path_value == "") {
            printHelp();
            return -1;
        }
        else{
            if (std::regex_match (path_value, std::regex("^(/[^/ ]*)+/?$") )) {
                std::cout << "string literal matched\n" << std::endl;
            }
            else {
                printHelp();
                return -1;
            }
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
                 "\t\t Path to file or directory to check integrity";
}
#include "../include/view.h"

View::View() = default;

// Nimmt die Commandline Argumente verarbeitet und sanatized diese und gibt sie als Liste zurück
std::tuple<bool, std::string, bool, bool> View::getInput(int argc, char* argv[]) {
    auto args = extractArguments(argc, argv);
    std::regex path_regex_template("^(\\.\\./|\\.\\/|/)?([^\\0]+)$");

    // Argumente die der User übergibt: {help, path, recursive}
    bool help_flag = true;
    std::string path_value;
    bool recursive_flag = false;
    bool force_flag = false;

    // Hier können alle optionalen commandline Argumente hin

    // Help Seite darstellen
    if (args.find("-h") != args.end()) {
        printHelp();
        return std::make_tuple(help_flag, path_value, recursive_flag, force_flag);
    }

    // Pfad angeben
    if (args.find("-p") != args.end()) {
        path_value = args["-p"];
        if (path_value.empty()) {
            printHelp();
            return std::make_tuple(help_flag, path_value, recursive_flag, force_flag);
        }
        else{
            if (std::regex_match (path_value, path_regex_template)) {
                help_flag = false;
            }
            else {
                printHelp();
                std::cerr << "Bitte Pfad angeben!" << std::endl;
                return std::make_tuple(help_flag, path_value, recursive_flag, force_flag);
            }
        }
    }
    else {
        printHelp();
        std::cerr << "Bitte Pfad angeben!" << std::endl;
        return std::make_tuple(help_flag, path_value, recursive_flag, force_flag);
    }

    // Rekuriv oder nicht
    if (args.find("-r") != args.end()) {
        recursive_flag = true;
    }

    // Löschen der alten Hashes forcen
    if (args.find("-f") != args.end()) {
        force_flag = true;
    }

    return std::make_tuple(help_flag, path_value, recursive_flag, force_flag);
}

// Methode zum speichern der Commandline Argumente in einer Map
std::map<std::string, std::string> View::extractArguments(int argc, char* argv[]) {
    std::map<std::string, std::string> args;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            // Überprüfen, ob nächstes Argument ein Wert ist
            if (i + 1 < argc && argv[i + 1][0] != '-') {
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
                 "\t\tPath to file or directory to check integrity\n"
                 "\t-r\n"
                 "\t\tSet if the file structure is to be traversed recursively\n"
                 "\t-f\n"
                 "\t\tForce overwriting of the old saved hashes\n"
                 "\t-h\n"
                 "\t\tDisplay this page" << std::endl;
}
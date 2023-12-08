#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <string>

namespace fs = std::filesystem;
using FileMap = std::unordered_map<int, std::string>;

int main() {
    std::string path = "/Users/vivi/Code/ProgSec_Projekt/files";
    FileMap fileMap;

    int id = 1;

    for (const auto &entry : fs::directory_iterator(path)) {
        // Hier fügst du das Key-Value-Paar (ID, Dateipfad) zur Map hinzu
        fileMap[id++] = entry.path().string();
    }

    // Ausgabe der gespeicherten Key-Value-Paare
    for (const auto &pair : fileMap) {
        std::cout << "ID: " << pair.first << ", Pfad: " << pair.second << std::endl;
    }

    return 0;
}

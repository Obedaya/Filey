//==========================================================
//   ________  _   __
//  |_   __  |(_) [  |
//    | |_ \_|__   | | .---.   _   __
//    |  _|  [  |  | |/ /__\\ [ \ [  ]
//   _| |_    | |  | || \__.,  \ '/ /
//  |_____|  [___][___]'.__.'[\_:  /
//                          \__.'
//============================================================
//
// File integrity checker, to check the integrity of directories and files
//


#include "../include/controller.h"

int main(int argc, char* argv[]) {

    std::string logFilePath = "../logs/log.txt";
    Controller controller(logFilePath);
    if (controller.initializeProgram(argc, argv)) {
        return -1;
    }
    return 0;
}
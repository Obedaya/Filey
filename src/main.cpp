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


#include "../include/logger.h"
#include "../include/controller.h"

// TODO: Logger implementieren und richtig einsetzen
// TODO: Inotify implementieren
int main(int argc, char* argv[]) {
    bool programRunning = true;

    std::string logFilePath = "../logs/log.txt";
    Controller controller(logFilePath);
    if (controller.initializeProgram(argc, argv)) {
        return -1;
    }
    return 0;
}
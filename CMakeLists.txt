#[===[cmake_minimum_required(VERSION 3.26)

project(Filey VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Logger
        fileprocessor/fileprocessor.cpp
        include/fileprocessor.h
        logger/logger.cpp
        include/logger.h
        src/main.cpp
)
add_executable(Hasher src/hasher.cpp
)

add_executable(Main src/main.cpp
        src/main.cpp
)
]===]

#_______
# CMakeLists.txt

cmake_minimum_required(VERSION 3.26)
project(Filey VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Simoms Hasher
add_executable(Hasher src/hasher.cpp
)

# Füge die Verzeichnisse mit Header-Dateien und Quelldateien hinzu
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Füge die ausführbare Datei hinzu
add_executable(Filey src/main.cpp)

# Füge die Unterprojekte (Bibliotheken) hinzu
add_subdirectory(logger)
add_subdirectory(fileprocessor)

# Verknüpfe die Bibliotheken mit dem Hauptprogramm
target_link_libraries(Filey Logger FileProcessor)

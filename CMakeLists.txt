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

if(APPLE)
    # Modify the path as necessary for your system (Intel or Apple Silicon)
    find_package(OpenSSL REQUIRED HINTS /usr/local/opt/openssl /opt/homebrew/opt/openssl)
else()
    find_package(OpenSSL REQUIRED)
endif()

# Füge die Verzeichnisse mit Header-Dateien und Quelldateien hinzu
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Füge die ausführbare Datei hinzu
add_executable(Filey src/main.cpp)

# Verknüpfe OpenSSL mit dem Hauptprogramm
target_link_libraries(Filey OpenSSL::SSL)

# Füge die Unterprojekte (Bibliotheken) hinzu
add_subdirectory(logger)
add_subdirectory(fileprocessor)
add_subdirectory(hasher)

# Verknüpfe die Bibliotheken mit dem Hauptprogramm
target_link_libraries(Filey Logger FileProcessor Hasher)


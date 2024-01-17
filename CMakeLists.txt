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
    # Passe den Pfad bei Bedarf entsprechend deinem System und der Ausgabe von 'brew info openssl' an
    set(OpenSSL_DIR /usr/local/opt/homebrew/Cellar/openssl@3/3.2.0_1)
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})

else()
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})

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
add_subdirectory(controller)
add_subdirectory(view)
add_subdirectory(encrypter)

# Verknüpfe die Bibliotheken mit dem Hauptprogramm
target_link_libraries(Filey Logger FileProcessor Hasher Controller View)


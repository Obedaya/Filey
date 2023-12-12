# fileprocessor/CMakeLists.txt

# Definiere die FileProcessor-Bibliothek
add_library(FileProcessor fileprocessor.cpp)

# Füge das include-Verzeichnis für FileProcessor hinzu
target_include_directories(FileProcessor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

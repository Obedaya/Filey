# fileprocessor/CMakeLists.txt

# Definiere die FileProcessor-Bibliothek
add_library(Hasher hasher.cpp)

# Füge das include-Verzeichnis für FileProcessor hinzu
target_include_directories(Hasher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

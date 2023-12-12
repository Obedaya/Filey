# logger/CMakeLists.txt

# Definiere die Logger-Bibliothek
add_library(Logger logger.cpp)

# Füge das include-Verzeichnis für Logger hinzu
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

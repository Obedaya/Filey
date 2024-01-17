# view/CMakeLists.txt

# Definiere die FileProcessor-Bibliothek
add_library(View view.cpp)

# Füge das include-Verzeichnis für FileProcessor hinzu
target_include_directories(View PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

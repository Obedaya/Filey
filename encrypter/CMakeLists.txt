# encrypter/CMakeLists.txt

add_library(Encrypter encrypter.cpp)

# Füge das include-Verzeichnis für Encrypter hinzu
target_include_directories(Encrypter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

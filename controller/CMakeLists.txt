# controller/CMakeLists.txt

add_library(Controller controller.cpp)

# Füge das include-Verzeichnis für Logger hinzu
target_include_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

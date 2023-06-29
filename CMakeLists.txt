cmake_minimum_required(VERSION 3.18)

project(adventurer)

set(EXECUTABLE_NAME "minesweeper")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
add_executable(minesweeper main.cpp)

find_package(SFML 2.5.1 REQUIRED system window graphics network audio)

set(SFML_STATIC_LIBRARIES TRUE)

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)

cmake_minimum_required (VERSION 3.0)

project (TP1)

add_executable( main.out src/main.cpp
    src/Vigenere.cpp)

target_link_libraries( main.out )

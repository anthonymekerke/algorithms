cmake_minimum_required (VERSION 3.0)

project (SDES)

add_executable( main.out src/main.cpp
    src/SDES.cpp)

target_link_libraries( main.out )

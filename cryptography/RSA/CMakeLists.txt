cmake_minimum_required (VERSION 3.0)

project (RSA)

add_executable( main.out src/main.cpp
    src/RSA.cpp)

target_link_libraries( main.out )

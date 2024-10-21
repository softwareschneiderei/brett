cmake_minimum_required(VERSION 3.10)
project(brett)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads REQUIRED)
find_package(Catch2 REQUIRED CONFIG)

add_subdirectory(src)
add_subdirectory(tests)

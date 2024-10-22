cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(brett CONFIG REQUIRED)

add_executable(brett_package_test brett_package_test.cpp)
target_link_libraries(brett_package_test brett::brett)

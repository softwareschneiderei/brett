cmake_minimum_required(VERSION 3.10)
project(brett)

# Setup conan dependencies
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
else()
  message(FATAL_ERROR "Please run conan install!")
endif()

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)

add_subdirectory(src)
add_subdirectory(tests)

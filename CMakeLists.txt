cmake_minimum_required(VERSION 3.16)
project(brett)

# Setup conan dependencies
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS)
else()
  message(FATAL_ERROR "Please run conan install!")
endif()

add_subdirectory(src)
add_subdirectory(tests)

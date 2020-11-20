cmake_minimum_required(VERSION 3.14)
project(LinkedList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp  LinkedListException.h)
add_executable(run ${SOURCE_FILES})

add_subdirectory(Google_tests)


cmake_minimum_required(VERSION 3.14)
project(csvParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(csvParser main.cpp CsvParser.h TuplePrinter.h TupleReader.h)
if(NOT CYGWIN)
    set(CMAKE_CXX_EXTENSIONS ON)
    message("Extensions: ${CMAKE_CXX_EXTENSIONS}")
endif()

set(CMAKE_CXX_STANDARD 11)

project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run list_test.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)

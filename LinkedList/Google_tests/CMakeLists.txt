if(NOT CYGWIN)
    set(CMAKE_CXX_EXTENSIONS ON)
    message("Extensions: ${CMAKE_CXX_EXTENSIONS}")
endif()

set(CMAKE_CXX_STANDARD 11)

project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(Google_Tests_run ListTest.cpp)
add_executable(RunAnotherTest AnotherTest.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(RunAnotherTest gtest gtest_main)

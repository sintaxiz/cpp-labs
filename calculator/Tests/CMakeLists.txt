if(NOT CYGWIN)
    set(CMAKE_CXX_EXTENSIONS ON)
    message("Extensions: ${CMAKE_CXX_EXTENSIONS}")
endif()

set(CMAKE_CXX_STANDARD 11)

project(GoogleTests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(RunTests CalculatorTest.cpp
        ../Operations/Arithmetic/Plus.cpp ../Operations/Arithmetic/Minus.cpp ../Operations/Arithmetic/Division.cpp
        ../Operations/Arithmetic/Multiplication.cpp ../Operations/Arithmetic/Root.cpp

        ../Operations/Pop.cpp ../Operations/Push.cpp
        ../Operations/Print.cpp
        ../Operations/Define.cpp


        ../Context.cpp ../Context.h ../OperationFactory.h ../InterfaceOperationMaker.h
        ../OperationMaker.h ../Calculator.cpp
        ../CalculatorException.h)

target_link_libraries(RunTests gtest gtest_main)

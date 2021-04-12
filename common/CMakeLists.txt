cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")
set(TESTCOMMON_SRC test/testcommon_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(include)

add_executable(testcommon ${TESTCOMMON_SRC})

set_property(TARGET testcommon PROPERTY CXX_STANDARD 11)

target_link_libraries(testcommon gtest gmock)


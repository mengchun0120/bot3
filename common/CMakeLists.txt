cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")
set(COMMON_SRC
    src/common_validator.cpp)
set(TESTCOMMON_SRC
    test/testcommon_main.cpp
    test/testcommon_test_validator.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(include)

add_library(common STATIC ${COMMON_SRC})
add_executable(testcommon ${TESTCOMMON_SRC})

set_property(TARGET common PROPERTY CXX_STANDARD 11)
set_property(TARGET testcommon PROPERTY CXX_STANDARD 11)

target_link_libraries(testcommon common gtest gmock)


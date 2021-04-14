cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")
set(COMMONLIB_SRC
    src/commonlib_validator.cpp)
set(TEST_COMMONLIB_SRC
    test/test_commonlib_main.cpp
    test/test_commonlib_validator.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(include)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

target_link_libraries(test_commonlib commonlib gtest gmock)


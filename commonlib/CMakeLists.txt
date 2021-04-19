cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(COMMONLIB_SRC
    src/commonlib_exception.cpp
    src/commonlib_validator.cpp
    src/commonlib_parse.cpp
    src/commonlib_argument.cpp
    src/commonlib_argument_parser.cpp)

set(TEST_COMMONLIB_SRC
    test/test_commonlib_main.cpp
    test/test_commonlib_validator.cpp
    test/test_commonlib_exception.cpp
    test/test_commonlib_argument.cpp
    test/test_commonlib_argument_parser.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(src)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

target_link_libraries(test_commonlib commonlib gtest gmock)


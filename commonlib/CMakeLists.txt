cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(COMMONLIB_MISC_SRC
    src/misc/commonlib_exception.cpp
    src/misc/commonlib_validator.cpp
    src/misc/commonlib_parse.cpp
    src/misc/commonlib_argument.cpp
    src/misc/commonlib_argument_parser.cpp)

set(COMMONLIB_SRC
    ${COMMONLIB_MISC_SRC})

set(TEST_COMMONLIB_SRC
    test/test_commonlib_main.cpp
    test/test_commonlib_validator.cpp
    test/test_commonlib_exception.cpp
    test/test_commonlib_argument.cpp
    test/test_commonlib_argument_parser.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(src/misc)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

target_link_libraries(test_commonlib commonlib gtest gmock)


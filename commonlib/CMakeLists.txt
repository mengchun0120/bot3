cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(COMMONLIB_MISC_SRC
    src/misc/commonlib_exception.cpp
    src/misc/commonlib_validator.cpp
    src/misc/commonlib_parse.cpp
    src/misc/commonlib_argument.cpp
    src/misc/commonlib_argument_parser.cpp
    src/misc/commonlib_log.cpp
    src/misc/commonlib_out_utils.cpp
    src/misc/commonlib_string_utils.cpp
    src/misc/commonlib_json_utils.cpp
    src/misc/commonlib_json_param.cpp)

set(COMMONLIB_MATH_SRC
    src/math/commonlib_math_utils.cpp
    src/math/commonlib_vector.cpp
    src/math/commonlib_matrix.cpp)

set(COMMONLIB_SRC
    ${COMMONLIB_MISC_SRC}
    ${COMMONLIB_MATH_SRC})

set(TEST_COMMONLIB_SRC
    test/test_commonlib_main.cpp
    test/test_commonlib_validator.cpp
    test/test_commonlib_exception.cpp
    test/test_commonlib_argument.cpp
    test/test_commonlib_argument_parser.cpp
    test/test_commonlib_vector.cpp
    test/test_commonlib_matrix.cpp
    test/test_commonlib_log.cpp
    test/test_commonlib_json_param.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(src/misc
                    src/math)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

target_link_libraries(test_commonlib commonlib gtest gmock)


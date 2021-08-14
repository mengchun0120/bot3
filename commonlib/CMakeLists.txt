cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

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
    src/misc/commonlib_json_param.cpp
    src/misc/commonlib_file_utils.cpp)

set(COMMONLIB_MATH_SRC
    src/math/commonlib_math_utils.cpp
    src/math/commonlib_vector.cpp
    src/math/commonlib_matrix.cpp)

set(COMMONLIB_APP_SRC
    src/app/commonlib_app.cpp)

set(COMMONLIB_STRUCTURE_SRC
    src/structure/commonlib_object_pool.cpp
    src/structure/commonlib_fixed_queue.cpp)

set(COMMONLIB_INPUT_SRC
    src/input/commonlib_input_event.cpp
    src/input/commonlib_input_manager.cpp)

set(COMMONLIB_OPENGL_SRC
    src/opengl/commonlib_shader_program.cpp
    src/opengl/commonlib_buffer_block.cpp
    src/opengl/commonlib_vertex_array.cpp)

set(COMMONLIB_SRC
    ${COMMONLIB_MISC_SRC}
    ${COMMONLIB_MATH_SRC}
    ${COMMONLIB_APP_SRC}
    ${COMMONLIB_STRUCTURE_SRC}
    ${COMMONLIB_INPUT_SRC}
    ${COMMONLIB_OPENGL_SRC})

set(TEST_COMMONLIB_SRC
    test/test_commonlib_main.cpp
    test/test_commonlib_validator.cpp
    test/test_commonlib_exception.cpp
    test/test_commonlib_argument.cpp
    test/test_commonlib_argument_parser.cpp
    test/test_commonlib_vector.cpp
    test/test_commonlib_matrix.cpp
    test/test_commonlib_log.cpp
    test/test_commonlib_json_param.cpp
    test/test_commonlib_object_pool.cpp
    test/test_commonlib_fixed_queue.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(include)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

target_link_libraries(test_commonlib commonlib gtest gmock)


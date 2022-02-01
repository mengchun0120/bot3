cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(COMMONLIB_APP_SRC
    app/commonlib_app.cpp)

set(COMMONLIB_BASE_SRC
    base/commonlib_object.cpp
    base/commonlib_named_object.cpp)

set(COMMONLIB_INPUT_SRC
    input/commonlib_input_event.cpp
    input/commonlib_input_manager.cpp)

set(COMMONLIB_MATH_SRC
    math/commonlib_collide.cpp
    math/commonlib_math_utils.cpp
    math/commonlib_matrix.cpp
    math/commonlib_vector.cpp)

set(COMMONLIB_MISC_SRC
    misc/commonlib_algorithm.cpp
    misc/commonlib_argument.cpp
    misc/commonlib_argument_parser.cpp
    misc/commonlib_exception.cpp
    misc/commonlib_file_utils.cpp
    misc/commonlib_json_param.cpp
    misc/commonlib_json_utils.cpp
    misc/commonlib_log.cpp
    misc/commonlib_out_utils.cpp
    misc/commonlib_parse.cpp
    misc/commonlib_string_utils.cpp
    misc/commonlib_time_utils.cpp
    misc/commonlib_validator.cpp)

set(COMMONLIB_OPENGL_SRC
    opengl/commonlib_buffer_block.cpp
    opengl/commonlib_color.cpp
    opengl/commonlib_opengl_utils.cpp
    opengl/commonlib_shader_program.cpp
    opengl/commonlib_texture.cpp
    opengl/commonlib_vertex_array.cpp)

set(COMMONLIB_STRUCTURE_SRC
    structure/commonlib_fixed_queue.cpp
    structure/commonlib_linked_list.cpp
    structure/commonlib_named_map.cpp
    structure/commonlib_object_pool.cpp
    structure/commonlib_region.cpp)

set(COMMONLIB_SRC
    ${COMMONLIB_APP_SRC}
    ${COMMONLIB_BASE_SRC}
    ${COMMONLIB_INPUT_SRC}
    ${COMMONLIB_MATH_SRC}
    ${COMMONLIB_MISC_SRC}
    ${COMMONLIB_OPENGL_SRC}
    ${COMMONLIB_STRUCTURE_SRC})

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${COMMONLIB_DIR})

add_library(commonlib STATIC ${COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)


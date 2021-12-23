cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(COMMONLIB_APP_SRC
    src/app/commonlib_app.cpp)

set(COMMONLIB_INPUT_SRC
    src/input/commonlib_input_event.cpp
    src/input/commonlib_input_manager.cpp)

set(COMMONLIB_MATH_SRC
    src/math/commonlib_collide.cpp
    src/math/commonlib_math_utils.cpp
    src/math/commonlib_matrix.cpp
    src/math/commonlib_vector.cpp)

set(COMMONLIB_MISC_SRC
    src/misc/commonlib_algorithm.cpp
    src/misc/commonlib_argument.cpp
    src/misc/commonlib_argument_parser.cpp
    src/misc/commonlib_exception.cpp
    src/misc/commonlib_file_utils.cpp
    src/misc/commonlib_json_param.cpp
    src/misc/commonlib_json_utils.cpp
    src/misc/commonlib_log.cpp
    src/misc/commonlib_out_utils.cpp
    src/misc/commonlib_parse.cpp
    src/misc/commonlib_string_utils.cpp
    src/misc/commonlib_time_utils.cpp
    src/misc/commonlib_validator.cpp)

set(COMMONLIB_OPENGL_SRC
    src/opengl/commonlib_buffer_block.cpp
    src/opengl/commonlib_color.cpp
    src/opengl/commonlib_opengl_utils.cpp
    src/opengl/commonlib_shader_program.cpp
    src/opengl/commonlib_texture.cpp
    src/opengl/commonlib_vertex_array.cpp)

set(COMMONLIB_STRUCTURE_SRC
    src/structure/commonlib_fixed_queue.cpp
    src/structure/commonlib_linked_list.cpp
    src/structure/commonlib_named_map.cpp
    src/structure/commonlib_object_pool.cpp
    src/structure/commonlib_region.cpp)

set(COMMONLIB_SRC
    ${COMMONLIB_APP_SRC}
    ${COMMONLIB_INPUT_SRC}
    ${COMMONLIB_MATH_SRC}
    ${COMMONLIB_MISC_SRC}
    ${COMMONLIB_OPENGL_SRC}
    ${COMMONLIB_STRUCTURE_SRC})

set(TEST_COMMONLIB_SRC
    test/test_commonlib_argument.cpp
    test/test_commonlib_argument_parser.cpp
    test/test_commonlib_collide.cpp
    test/test_commonlib_exception.cpp
    test/test_commonlib_fixed_queue.cpp
    test/test_commonlib_json_param.cpp
    test/test_commonlib_linked_list.cpp
    test/test_commonlib_log.cpp
    test/test_commonlib_main.cpp
    test/test_commonlib_matrix.cpp
    test/test_commonlib_named_map.cpp
    test/test_commonlib_object_pool.cpp
    test/test_commonlib_validator.cpp
    test/test_commonlib_vector.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(include test)

add_library(commonlib STATIC ${COMMONLIB_SRC})
add_executable(test_commonlib ${TEST_COMMONLIB_SRC})

set_property(TARGET commonlib PROPERTY CXX_STANDARD 11)
set_property(TARGET test_commonlib PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(test_commonlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor)
elseif(MINGW)
    target_link_libraries(test_commonlib commonlib opengl32 glfw3 glew32)
endif()


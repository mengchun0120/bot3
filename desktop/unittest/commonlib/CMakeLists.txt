cmake_minimum_required(VERSION 3.22.1)

list(APPEND
    UNITTEST_COMMONLIB_SRC
    test_commonlib_argument.cpp
    test_commonlib_argument_parser.cpp
    test_commonlib_collide.cpp
    test_commonlib_exception.cpp
    test_commonlib_file_utils.cpp
    test_commonlib_fixed_queue.cpp
    test_commonlib_json_param.cpp
    test_commonlib_linked_item.cpp
    test_commonlib_linked_list.cpp
    test_commonlib_log.cpp
    test_commonlib_main.cpp
    test_commonlib_matrix.cpp
    test_commonlib_named_map.cpp
    test_commonlib_object_pool.cpp
    test_commonlib_region.cpp
    test_commonlib_validator.cpp
    test_commonlib_vector.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
)

add_executable(test_commonlib ${UNITTEST_COMMONLIB_SRC})

if(UNIX)
    target_link_libraries(test_commonlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor)
elseif(MINGW)
    target_link_libraries(test_commonlib commonlib opengl32 glfw3 glew32)
endif()


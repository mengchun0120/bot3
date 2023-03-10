list(APPEND
    COMMONLIB_APP_SRC
    ${COMMONLIB_SRC_DIR}/app/commonlib_app.cpp
)

list(APPEND
    COMMONLIB_BASE_SRC
    ${COMMONLIB_SRC_DIR}/base/commonlib_object.cpp
    ${COMMONLIB_SRC_DIR}/base/commonlib_named_object.cpp
)

list(APPEND
    COMMONLIB_INPUT_SRC
    ${COMMONLIB_SRC_DIR}/input/commonlib_input_event.cpp
    ${COMMONLIB_SRC_DIR}/input/commonlib_input_manager.cpp
    ${COMMONLIB_SRC_DIR}/input/commonlib_input_map.cpp
)

list(APPEND
    COMMONLIB_MATH_SRC
    ${COMMONLIB_SRC_DIR}/math/commonlib_collide.cpp
    ${COMMONLIB_SRC_DIR}/math/commonlib_math_utils.cpp
    ${COMMONLIB_SRC_DIR}/math/commonlib_matrix.cpp
    ${COMMONLIB_SRC_DIR}/math/commonlib_vector.cpp
)

list(APPEND
    COMMONLIB_MISC_SRC
    ${COMMONLIB_SRC_DIR}/misc/commonlib_algorithm.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_argument.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_argument_parser.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_exception.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_file_utils.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_json_param.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_json_utils.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_log.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_out_utils.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_parse.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_random.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_string_utils.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_system.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_time_utils.cpp
    ${COMMONLIB_SRC_DIR}/misc/commonlib_validator.cpp
)

list(APPEND
    COMMONLIB_OPENGL_SRC
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_buffer_block.cpp
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_color.cpp
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_opengl_utils.cpp
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_shader_program.cpp
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_texture.cpp
    ${COMMONLIB_SRC_DIR}/opengl/commonlib_vertex_array.cpp
)

list(APPEND
    COMMONLIB_STRUCTURE_SRC
    ${COMMONLIB_SRC_DIR}/structure/commonlib_fixed_queue.cpp
    ${COMMONLIB_SRC_DIR}/structure/commonlib_linked_item.cpp
    ${COMMONLIB_SRC_DIR}/structure/commonlib_linked_list.cpp
    ${COMMONLIB_SRC_DIR}/structure/commonlib_named_map.cpp
    ${COMMONLIB_SRC_DIR}/structure/commonlib_object_pool.cpp
    ${COMMONLIB_SRC_DIR}/structure/commonlib_region.cpp
)

list(APPEND
    COMMONLIB_SOURCE_FILES
    ${COMMONLIB_APP_SRC}
    ${COMMONLIB_BASE_SRC}
    ${COMMONLIB_INPUT_SRC}
    ${COMMONLIB_MATH_SRC}
    ${COMMONLIB_MISC_SRC}
    ${COMMONLIB_OPENGL_SRC}
    ${COMMONLIB_STRUCTURE_SRC}
)

list(APPEND
    COMMONLIB_INCLUDE_DIR
    ${COMMONLIB_SRC_DIR}/app
    ${COMMONLIB_SRC_DIR}/base
    ${COMMONLIB_SRC_DIR}/input
    ${COMMONLIB_SRC_DIR}/math
    ${COMMONLIB_SRC_DIR}/misc
    ${COMMONLIB_SRC_DIR}/opengl
    ${COMMONLIB_SRC_DIR}/structure
)

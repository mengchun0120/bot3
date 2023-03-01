list(APPEND
    commonlib_app_src
    ${commonlib_src_dir}/app/commonlib_app.cpp
)

list(APPEND
    commonlib_base_src
    ${commonlib_src_dir}/base/commonlib_object.cpp
    ${commonlib_src_dir}/base/commonlib_named_object.cpp
)

list(APPEND
    commonlib_input_src
    ${commonlib_src_dir}/input/commonlib_input_event.cpp
    ${commonlib_src_dir}/input/commonlib_input_manager.cpp
    ${commonlib_src_dir}/input/commonlib_input_map.cpp
)

list(APPEND
    commonlib_math_src
    ${commonlib_src_dir}/math/commonlib_collide.cpp
    ${commonlib_src_dir}/math/commonlib_math_utils.cpp
    ${commonlib_src_dir}/math/commonlib_matrix.cpp
    ${commonlib_src_dir}/math/commonlib_vector.cpp
)

list(APPEND
    commonlib_misc_src
    ${commonlib_src_dir}/misc/commonlib_algorithm.cpp
    ${commonlib_src_dir}/misc/commonlib_argument.cpp
    ${commonlib_src_dir}/misc/commonlib_argument_parser.cpp
    ${commonlib_src_dir}/misc/commonlib_exception.cpp
    ${commonlib_src_dir}/misc/commonlib_file_utils.cpp
    ${commonlib_src_dir}/misc/commonlib_json_param.cpp
    ${commonlib_src_dir}/misc/commonlib_json_utils.cpp
    ${commonlib_src_dir}/misc/commonlib_log.cpp
    ${commonlib_src_dir}/misc/commonlib_out_utils.cpp
    ${commonlib_src_dir}/misc/commonlib_parse.cpp
    ${commonlib_src_dir}/misc/commonlib_random.cpp
    ${commonlib_src_dir}/misc/commonlib_string_utils.cpp
    ${commonlib_src_dir}/misc/commonlib_time_utils.cpp
    ${commonlib_src_dir}/misc/commonlib_validator.cpp
)

list(APPEND
    commonlib_opengl_src
    ${commonlib_src_dir}/opengl/commonlib_buffer_block.cpp
    ${commonlib_src_dir}/opengl/commonlib_color.cpp
    ${commonlib_src_dir}/opengl/commonlib_opengl_utils.cpp
    ${commonlib_src_dir}/opengl/commonlib_shader_program.cpp
    ${commonlib_src_dir}/opengl/commonlib_texture.cpp
    ${commonlib_src_dir}/opengl/commonlib_vertex_array.cpp
)

list(APPEND
    commonlib_structure_src
    ${commonlib_src_dir}/structure/commonlib_fixed_queue.cpp
    ${commonlib_src_dir}/structure/commonlib_linked_item.cpp
    ${commonlib_src_dir}/structure/commonlib_linked_list.cpp
    ${commonlib_src_dir}/structure/commonlib_named_map.cpp
    ${commonlib_src_dir}/structure/commonlib_object_pool.cpp
    ${commonlib_src_dir}/structure/commonlib_region.cpp
)

list(APPEND
    commonlib_source_files
    ${commonlib_app_src}
    ${commonlib_base_src}
    ${commonlib_input_src}
    ${commonlib_math_src}
    ${commonlib_misc_src}
    ${commonlib_opengl_src}
    ${commonlib_structure_src}
)

list(APPEND
    commonlib_include_dir
    ${commonlib_src_dir}/app
    ${commonlib_src_dir}/base
    ${commonlib_src_dir}/input
    ${commonlib_src_dir}/math
    ${commonlib_src_dir}/misc
    ${commonlib_src_dir}/opengl
    ${commonlib_src_dir}/structure
)
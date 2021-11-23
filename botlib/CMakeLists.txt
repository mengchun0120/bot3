cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTLIB_APP_SRC
    src/app/botlib_app_config.cpp
    src/app/botlib_bot_app.cpp
    src/app/botlib_app_actions.cpp)

set(BOTLIB_OPENGL_SRC
    src/opengl/botlib_simple_shader_program.cpp
    src/opengl/botlib_text_size.cpp
    src/opengl/botlib_text_system.cpp
    src/opengl/botlib_graphics.cpp)

set(BOTLIB_SCREEN_SRC
    src/screen/botlib_screen_type.cpp
    src/screen/botlib_screen.cpp
    src/screen/botlib_start_screen.cpp
    src/screen/botlib_game_screen.cpp
    src/screen/botlib_screen_manager.cpp)

set(BOTLIB_SHAPE_SRC
    src/shape/botlib_tex_pos_array.cpp
    src/shape/botlib_tex_rectangle.cpp
    src/shape/botlib_shape.cpp
    src/shape/botlib_polygon.cpp
    src/shape/botlib_rectangle.cpp)

set(BOTLIB_WIDGET_SRC
    src/widget/botlib_align.cpp
    src/widget/botlib_widget.cpp
    src/widget/botlib_widget_group.cpp
    src/widget/botlib_button.cpp
    src/widget/botlib_label.cpp
    src/widget/botlib_message_box.cpp)

set(BOTLIB_GAMEOBJ_SRC
    src/gameobj/botlib_component_template.cpp
    src/gameobj/botlib_component.cpp
    src/gameobj/botlib_game_object_type.cpp
    src/gameobj/botlib_game_object_template.cpp
    src/gameobj/botlib_composite_object_template.cpp
    src/gameobj/botlib_tile_template.cpp
    src/gameobj/botlib_robot_template.cpp
    src/gameobj/botlib_game_object.cpp
    src/gameobj/botlib_composite_object.cpp
    src/gameobj/botlib_tile.cpp)

set(BOTLIB_GAMEUTILS_SRC
    src/gameutils/botlib_lib_parser.cpp
    src/gameutils/botlib_game_lib.cpp
    src/gameutils/botlib_game_map_item.cpp
    src/gameutils/botlib_game_map.cpp
    src/gameutils/botlib_game_map_loader.cpp)

set(BOTLIB_MISC_SRC
    src/misc/botlib_constants.cpp)

set(BOTLIB_SRC
    ${BOTLIB_APP_SRC}
    ${BOTLIB_OPENGL_SRC}
    ${BOTLIB_SCREEN_SRC}
    ${BOTLIB_SHAPE_SRC}
    ${BOTLIB_WIDGET_SRC}
    ${BOTLIB_GAMEOBJ_SRC}
    ${BOTLIB_GAMEUTILS_SRC}
    ${BOTLIB_MISC_SRC})

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/commonlib/include
                    include)

add_library(botlib STATIC ${BOTLIB_SRC})

set_property(TARGET botlib PROPERTY CXX_STANDARD 11)


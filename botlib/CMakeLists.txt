cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTLIB_APP_SRC
    src/app/botlib_app_actions.cpp
    src/app/botlib_app_config.cpp
    src/app/botlib_bot_app.cpp)

set(BOTLIB_GAMEOBJ_SRC
    src/gameobj/botlib_ai_robot.cpp
    src/gameobj/botlib_ai_robot_template.cpp
    src/gameobj/botlib_component.cpp
    src/gameobj/botlib_component_template.cpp
    src/gameobj/botlib_composite_object.cpp
    src/gameobj/botlib_composite_object_template.cpp
    src/gameobj/botlib_game_object.cpp
    src/gameobj/botlib_game_object_template.cpp
    src/gameobj/botlib_game_object_type.cpp
    src/gameobj/botlib_hp_indicator.cpp
    src/gameobj/botlib_missile.cpp
    src/gameobj/botlib_missile_template.cpp
    src/gameobj/botlib_particle_effect_template.cpp
    src/gameobj/botlib_robot.cpp
    src/gameobj/botlib_robot_template.cpp
    src/gameobj/botlib_side.cpp
    src/gameobj/botlib_tile.cpp
    src/gameobj/botlib_tile_template.cpp)

set(BOTLIB_GAMEUTILS_SRC
    src/gameutils/botlib_add_object_checker.cpp
    src/gameutils/botlib_ai_robot_template_parser.cpp
    src/gameutils/botlib_component_parser.cpp
    src/gameutils/botlib_component_template_parser.cpp
    src/gameutils/botlib_composite_object_template_parser.cpp
    src/gameutils/botlib_dead_object_remover.cpp
    src/gameutils/botlib_game_lib.cpp
    src/gameutils/botlib_game_map.cpp
    src/gameutils/botlib_game_map_accessor.cpp
    src/gameutils/botlib_game_map_item.cpp
    src/gameutils/botlib_game_map_loader.cpp
    src/gameutils/botlib_game_object_flag_resetter.cpp
    src/gameutils/botlib_game_object_presenter.cpp
    src/gameutils/botlib_game_object_template_parser.cpp
    src/gameutils/botlib_game_object_updater.cpp
    src/gameutils/botlib_game_utils.cpp
    src/gameutils/botlib_missile_hit_checker.cpp
    src/gameutils/botlib_missile_template_parser.cpp
    src/gameutils/botlib_nonpassthrough_collide_checker.cpp
    src/gameutils/botlib_rect_parser.cpp
    src/gameutils/botlib_robot_hit_missile_checker.cpp
    src/gameutils/botlib_robot_template_parser.cpp
    src/gameutils/botlib_texture_parser.cpp
    src/gameutils/botlib_tile_template_parser.cpp
    src/gameutils/botlib_time_delta_smoother.cpp)

set(BOTLIB_MISC_SRC
    src/misc/botlib_constants.cpp)

set(BOTLIB_OPENGL_SRC
    src/opengl/botlib_graphics.cpp
    src/opengl/botlib_particle_shader_program.cpp
    src/opengl/botlib_simple_shader_program.cpp
    src/opengl/botlib_text_size.cpp
    src/opengl/botlib_text_system.cpp)

set(BOTLIB_SCREEN_SRC
    src/screen/botlib_game_screen.cpp
    src/screen/botlib_screen.cpp
    src/screen/botlib_screen_manager.cpp
    src/screen/botlib_screen_type.cpp
    src/screen/botlib_start_screen.cpp)

set(BOTLIB_SHAPE_SRC
    src/shape/botlib_polygon.cpp
    src/shape/botlib_rectangle.cpp
    src/shape/botlib_shape.cpp
    src/shape/botlib_tex_pos_array.cpp
    src/shape/botlib_tex_rectangle.cpp)

set(BOTLIB_WIDGET_SRC
    src/widget/botlib_align.cpp
    src/widget/botlib_button.cpp
    src/widget/botlib_label.cpp
    src/widget/botlib_message_box.cpp
    src/widget/botlib_widget.cpp
    src/widget/botlib_widget_group.cpp)

set(BOTLIB_SRC
    ${BOTLIB_APP_SRC}
    ${BOTLIB_GAMEOBJ_SRC}
    ${BOTLIB_GAMEUTILS_SRC}
    ${BOTLIB_MISC_SRC}
    ${BOTLIB_OPENGL_SRC}
    ${BOTLIB_SCREEN_SRC}
    ${BOTLIB_SHAPE_SRC}
    ${BOTLIB_WIDGET_SRC})

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/commonlib/include
                    include)

add_library(botlib STATIC ${BOTLIB_SRC})

set_property(TARGET botlib PROPERTY CXX_STANDARD 11)


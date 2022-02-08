cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTLIB_ACCESSOR_SRC
    accessor/botlib_add_object_checker.cpp
    accessor/botlib_game_map_accessor.cpp
    accessor/botlib_game_object_flag_resetter.cpp
    accessor/botlib_game_object_presenter.cpp
    accessor/botlib_game_object_updater.cpp
    accessor/botlib_missile_hit_checker.cpp
    accessor/botlib_nonpassthrough_collide_checker.cpp
    accessor/botlib_robot_hit_missile_checker.cpp)

set(BOTLIB_APP_SRC
    app/botlib_app_actions.cpp
    app/botlib_app_config.cpp
    app/botlib_bot_app.cpp)

set(BOTLIB_GAMEOBJ_SRC
    gameobj/botlib_ai_robot.cpp
    gameobj/botlib_component.cpp
    gameobj/botlib_composite_object.cpp
    gameobj/botlib_game_object.cpp
    gameobj/botlib_game_object_state.cpp
    gameobj/botlib_game_object_type.cpp
    gameobj/botlib_hp_indicator.cpp
    gameobj/botlib_missile.cpp
    gameobj/botlib_particle_effect.cpp
    gameobj/botlib_player.cpp
    gameobj/botlib_robot.cpp
    gameobj/botlib_side.cpp
    gameobj/botlib_tile.cpp)

set(BOTLIB_GAMEUTILS_SRC
    gameutils/botlib_game_lib.cpp
    gameutils/botlib_game_map.cpp
    gameutils/botlib_game_map_loader.cpp
    gameutils/botlib_time_delta_smoother.cpp)

set(BOTLIB_MISC_SRC
    misc/botlib_constants.cpp
    misc/botlib_typedef.cpp)

set(BOTLIB_OPENGL_SRC
    opengl/botlib_graphics.cpp
    opengl/botlib_particle_shader_program.cpp
    opengl/botlib_simple_shader_program.cpp
    opengl/botlib_text_size.cpp
    opengl/botlib_text_system.cpp)

set(BOTLIB_SCREEN_SRC
    screen/botlib_game_screen.cpp
    screen/botlib_game_screen_config.cpp
    screen/botlib_screen.cpp
    screen/botlib_screen_manager.cpp
    screen/botlib_screen_type.cpp
    screen/botlib_start_screen.cpp
    screen/botlib_start_screen_config.cpp)

set(BOTLIB_SHAPE_SRC
    shape/botlib_polygon.cpp
    shape/botlib_rectangle.cpp
    shape/botlib_shape.cpp
    shape/botlib_tex_pos_array.cpp
    shape/botlib_tex_rectangle.cpp)

set(BOTLIB_TEMPLATE_SRC
    template/botlib_ai_robot_template.cpp
    template/botlib_component_template.cpp
    template/botlib_composite_object_template.cpp
    template/botlib_game_object_template.cpp
    template/botlib_missile_template.cpp
    template/botlib_particle_effect_template.cpp
    template/botlib_player_template.cpp
    template/botlib_robot_template.cpp
    template/botlib_tile_template.cpp)

set(BOTLIB_WIDGET_SRC
    widget/botlib_align.cpp
    widget/botlib_button.cpp
    widget/botlib_label.cpp
    widget/botlib_message_box.cpp
    widget/botlib_widget.cpp
    widget/botlib_widget_group.cpp)

set(BOTLIB_SRC
    ${BOTLIB_ACCESSOR_SRC}
    ${BOTLIB_APP_SRC}
    ${BOTLIB_GAMEOBJ_SRC}
    ${BOTLIB_GAMEUTILS_SRC}
    ${BOTLIB_MISC_SRC}
    ${BOTLIB_OPENGL_SRC}
    ${BOTLIB_SCREEN_SRC}
    ${BOTLIB_SHAPE_SRC}
    ${BOTLIB_TEMPLATE_SRC}
    ${BOTLIB_WIDGET_SRC})

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${COMMONLIB_DIR}
                    ${BOTLIB_DIR})

add_library(botlib STATIC ${BOTLIB_SRC})

set_property(TARGET botlib PROPERTY CXX_STANDARD 11)


cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTLIB_AI_SRC
    ai/botlib_ai.cpp
    ai/botlib_ai_factory.cpp
    ai/botlib_ai_lib.cpp
    ai/botlib_chase_shoot_ai.cpp
    ai/botlib_chase_shoot_ai_param.cpp
    ai/botlib_robot_action.cpp
)

set(BOTLIB_APP_SRC
    app/botlib_app_actions.cpp
    app/botlib_app_config.cpp
)

set(BOTLIB_GAMEOBJ_SRC
    gameobj/botlib_ai_robot.cpp
    gameobj/botlib_ai_robot_template.cpp
    gameobj/botlib_component.cpp
    gameobj/botlib_component_template.cpp
    gameobj/botlib_component_type.cpp
    gameobj/botlib_composite_object.cpp
    gameobj/botlib_composite_object_template.cpp
    gameobj/botlib_game_object.cpp
    gameobj/botlib_game_object_factory.cpp
    gameobj/botlib_game_object_state.cpp
    gameobj/botlib_game_object_template.cpp
    gameobj/botlib_game_object_type.cpp
    gameobj/botlib_goodie.cpp
    gameobj/botlib_goodie_action.cpp
    gameobj/botlib_goodie_effect.cpp
    gameobj/botlib_goodie_template.cpp
    gameobj/botlib_goodie_type.cpp
    gameobj/botlib_missile.cpp
    gameobj/botlib_missile_template.cpp
    gameobj/botlib_particle_effect.cpp
    gameobj/botlib_particle_effect_template.cpp
    gameobj/botlib_player.cpp
    gameobj/botlib_player_template.cpp
    gameobj/botlib_robot.cpp
    gameobj/botlib_robot_template.cpp
    gameobj/botlib_side.cpp
    gameobj/botlib_tile.cpp
    gameobj/botlib_tile_template.cpp
)

set(BOTLIB_GAMEUTILS_SRC
    gameutils/botlib_context.cpp
    gameutils/botlib_game_config.cpp
    gameutils/botlib_game_lib.cpp
    gameutils/botlib_game_map.cpp
    gameutils/botlib_game_map_loader.cpp
    gameutils/botlib_game_object_dumper.cpp
    gameutils/botlib_goodie_generator.cpp
    gameutils/botlib_time_delta_smoother.cpp
    gameutils/botlib_update_context.cpp
)

set(BOTLIB_GAME_WIDGETS_SRC
    game_widgets/botlib_hp_indicator.cpp
    game_widgets/botlib_hp_indicator_config.cpp
    game_widgets/botlib_icon.cpp
    game_widgets/botlib_icon_template.cpp
    game_widgets/botlib_progress_bar.cpp
    game_widgets/botlib_progress_bar_template.cpp
    game_widgets/botlib_progress_pie.cpp
    game_widgets/botlib_progress_pie_template.cpp
)

set(BOTLIB_MAP_ACCESSOR_SRC
    map_accessor/botlib_missile_hit_checker.cpp
    map_accessor/botlib_missile_hit_checker.h
    map_accessor/botlib_passthrough_collide_checker.cpp
    map_accessor/botlib_passthrough_collide_checker.h
    map_accessor/botlib_target_finder.cpp
    map_accessor/botlib_target_finder.h
)

set(BOTLIB_MAP_GENERATOR_SRC
    map_generator/botlib_game_map_generator.cpp
    map_generator/botlib_game_map_generator_config.cpp
    map_generator/botlib_game_map_generator_factory.cpp
    map_generator/botlib_island_map_generator.cpp
    map_generator/botlib_island_map_generator_config.cpp
)

set(BOTLIB_MISC_SRC
    misc/botlib_constants.cpp
    misc/botlib_typedef.cpp
)

set(BOTLIB_OPENGL_SRC
    opengl/botlib_graphics.cpp
    opengl/botlib_particle_shader_program.cpp
    opengl/botlib_simple_shader_program.cpp
    opengl/botlib_text_size.cpp
    opengl/botlib_text_system.cpp
)

set(BOTLIB_SCREEN_SRC
    screen/botlib_game_screen.cpp
    screen/botlib_game_screen_config.cpp
    screen/botlib_screen.cpp
    screen/botlib_screen_manager.cpp
    screen/botlib_screen_type.cpp
    screen/botlib_showmap_screen.cpp
    screen/botlib_showmap_screen_config.cpp
    screen/botlib_start_screen.cpp
    screen/botlib_start_screen_config.cpp
)

set(BOTLIB_SHAPE_SRC
    shape/botlib_polygon.cpp
    shape/botlib_rectangle.cpp
    shape/botlib_shape.cpp
    shape/botlib_tex_pos_array.cpp
    shape/botlib_tex_rectangle.cpp
)

set(BOTLIB_SKILL_SRC
    skill/botlib_blast_skill.cpp
    skill/botlib_blast_skill_template.cpp
    skill/botlib_move_skill.cpp
    skill/botlib_move_skill_template.cpp
    skill/botlib_shoot_missile_skill.cpp
    skill/botlib_shoot_missile_skill_template.cpp
    skill/botlib_skill.cpp
    skill/botlib_skill_static_flag.cpp
    skill/botlib_skill_template.cpp
    skill/botlib_skill_type.cpp
    skill/botlib_skill_utils.cpp
    skill/botlib_skill_with_cost.cpp
    skill/botlib_skill_with_cost_template.cpp
    skill/botlib_targeted_blast_skill.cpp
    skill/botlib_targeted_blast_skill_template.cpp
)

set(BOTLIB_UI_WIDGETS_SRC
    ui_widgets/botlib_align.cpp
    ui_widgets/botlib_button.cpp
    ui_widgets/botlib_button_config.cpp
    ui_widgets/botlib_label.cpp
    ui_widgets/botlib_label_config.cpp
    ui_widgets/botlib_message_box.cpp
    ui_widgets/botlib_message_box_config.cpp
    ui_widgets/botlib_widget.cpp
    ui_widgets/botlib_widget_group.cpp
)

set(BOTLIB_SRC
    ${BOTLIB_APP_SRC}
    ${BOTLIB_AI_SRC}
    ${BOTLIB_GAMEOBJ_SRC}
    ${BOTLIB_GAMEUTILS_SRC}
    ${BOTLIB_GAME_WIDGETS_SRC}
    ${BOTLIB_MAP_ACCESSOR_SRC}
    ${BOTLIB_MAP_GENERATOR_SRC}
    ${BOTLIB_MISC_SRC}
    ${BOTLIB_OPENGL_SRC}
    ${BOTLIB_SCREEN_SRC}
    ${BOTLIB_SHAPE_SRC}
    ${BOTLIB_SKILL_SRC}
    ${BOTLIB_UI_WIDGETS_SRC}
)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${COMMONLIB_DIR} ${BOTLIB_DIR})

add_library(botlib STATIC ${BOTLIB_SRC})

set_property(TARGET botlib PROPERTY CXX_STANDARD 11)


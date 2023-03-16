list(APPEND
    BOTLIB_AI_SRC
    ${BOTLIB_SRC_DIR}/ai/botlib_ai.cpp
    ${BOTLIB_SRC_DIR}/ai/botlib_ai_factory.cpp
    ${BOTLIB_SRC_DIR}/ai/botlib_ai_lib.cpp
    ${BOTLIB_SRC_DIR}/ai/botlib_chase_shoot_ai.cpp
    ${BOTLIB_SRC_DIR}/ai/botlib_chase_shoot_ai_param.cpp
    ${BOTLIB_SRC_DIR}/ai/botlib_robot_action.cpp
)

list(APPEND
    BOTLIB_APP_SRC
    ${BOTLIB_SRC_DIR}/app/botlib_app_actions.cpp
    ${BOTLIB_SRC_DIR}/app/botlib_app_config.cpp
    ${BOTLIB_SRC_DIR}/app/botlib_test_map_app.cpp
    ${BOTLIB_SRC_DIR}/app/botlib_test_shape_app.cpp
    ${BOTLIB_SRC_DIR}/app/botlib_test_widget_app.cpp
)

list(APPEND
    BOTLIB_GAMEOBJ_SRC
    ${BOTLIB_SRC_DIR}/gameobj/botlib_ai_robot.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_ai_robot_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_component.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_component_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_component_type.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_composite_object.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_composite_object_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_obj_flag.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_object.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_object_factory.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_object_state.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_object_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_game_object_type.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_goodie.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_goodie_action.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_goodie_effect.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_goodie_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_goodie_type.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_missile.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_missile_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_particle_effect.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_particle_effect_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_player.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_player_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_robot.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_robot_template.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_side.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_tile.cpp
    ${BOTLIB_SRC_DIR}/gameobj/botlib_tile_template.cpp
)

list(APPEND
    BOTLIB_GAMEUTILS_SRC
    ${BOTLIB_SRC_DIR}/gameutils/botlib_context.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_game_config.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_game_lib.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_game_map.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_game_map_loader.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_game_object_dumper.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_goodie_generator.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_time_delta_smoother.cpp
    ${BOTLIB_SRC_DIR}/gameutils/botlib_update_context.cpp
)

list(APPEND
    BOTLIB_GAME_WIDGETS_SRC
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_hp_indicator.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_hp_indicator_config.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_icon.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_icon_template.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_progress_bar.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_progress_bar_template.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_progress_pie.cpp
    ${BOTLIB_SRC_DIR}/game_widgets/botlib_progress_pie_template.cpp
)

list(APPEND
    BOTLIB_MAP_ACCESSOR_SRC
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_missile_hit_checker.cpp
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_missile_hit_checker.h
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_passthrough_collide_checker.cpp
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_passthrough_collide_checker.h
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_target_finder.cpp
    ${BOTLIB_SRC_DIR}/map_accessor/botlib_target_finder.h
)

list(APPEND
    BOTLIB_MAP_GENERATOR_SRC
    ${BOTLIB_SRC_DIR}/map_generator/botlib_game_map_generator.cpp
    ${BOTLIB_SRC_DIR}/map_generator/botlib_game_map_generator_config.cpp
    ${BOTLIB_SRC_DIR}/map_generator/botlib_game_map_generator_factory.cpp
    ${BOTLIB_SRC_DIR}/map_generator/botlib_island_map_generator.cpp
    ${BOTLIB_SRC_DIR}/map_generator/botlib_island_map_generator_config.cpp
)

list(APPEND
    BOTLIB_MISC_SRC
    ${BOTLIB_SRC_DIR}/misc/botlib_constants.cpp
    ${BOTLIB_SRC_DIR}/misc/botlib_typedef.cpp
)

list(APPEND
    BOTLIB_OPENGL_SRC
    ${BOTLIB_SRC_DIR}/opengl/botlib_graphics.cpp
    ${BOTLIB_SRC_DIR}/opengl/botlib_particle_shader_program.cpp
    ${BOTLIB_SRC_DIR}/opengl/botlib_simple_shader_program.cpp
    ${BOTLIB_SRC_DIR}/opengl/botlib_text_size.cpp
    ${BOTLIB_SRC_DIR}/opengl/botlib_text_system.cpp
)

list(APPEND
    BOTLIB_SCREEN_SRC
    ${BOTLIB_SRC_DIR}/screen/botlib_game_screen.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_game_screen_config.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_screen.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_screen_manager.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_screen_type.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_show_map_screen.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_show_map_screen_config.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_start_screen.cpp
    ${BOTLIB_SRC_DIR}/screen/botlib_start_screen_config.cpp
)

list(APPEND
    BOTLIB_SHAPE_SRC
    ${BOTLIB_SRC_DIR}/shape/botlib_polygon.cpp
    ${BOTLIB_SRC_DIR}/shape/botlib_rectangle.cpp
    ${BOTLIB_SRC_DIR}/shape/botlib_shape.cpp
    ${BOTLIB_SRC_DIR}/shape/botlib_tex_pos_array.cpp
    ${BOTLIB_SRC_DIR}/shape/botlib_tex_rectangle.cpp
)

list(APPEND
    BOTLIB_SKILL_SRC
    ${BOTLIB_SRC_DIR}/skill/botlib_barrage_blast_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_barrage_blast_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_barrage_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_barrage_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_blast_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_blast_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_dynamic_skill_flag.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_move_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_move_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_shoot_missile_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_shoot_missile_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill_type.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill_utils.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill_with_cost.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_skill_with_cost_template.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_static_skill_flag.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_targeted_blast_skill.cpp
    ${BOTLIB_SRC_DIR}/skill/botlib_targeted_blast_skill_template.cpp
)

list(APPEND
    BOTLIB_UI_WIDGETS_SRC
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_align.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_button.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_button_config.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_label.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_label_config.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_message_box.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_message_box_config.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_widget.cpp
    ${BOTLIB_SRC_DIR}/ui_widgets/botlib_widget_group.cpp
)

list(APPEND
    BOTLIB_SOURCE_FILES
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

list(APPEND
    BOTLIB_INCLUDE_DIR
    ${BOTLIB_SRC_DIR}/app
    ${BOTLIB_SRC_DIR}/ai
    ${BOTLIB_SRC_DIR}/gameobj
    ${BOTLIB_SRC_DIR}/gameutils
    ${BOTLIB_SRC_DIR}/game_widgets
    ${BOTLIB_SRC_DIR}/map_accessor
    ${BOTLIB_SRC_DIR}/map_generator
    ${BOTLIB_SRC_DIR}/misc
    ${BOTLIB_SRC_DIR}/opengl
    ${BOTLIB_SRC_DIR}/screen
    ${BOTLIB_SRC_DIR}/shape
    ${BOTLIB_SRC_DIR}/skill
    ${BOTLIB_SRC_DIR}/ui_widgets
)

cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(test_game_buttons test_game_buttons_main.cpp)

target_link_libraries(test_game_buttons botlib commonlib ${LIB})

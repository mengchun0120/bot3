cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${COMMONLIB_DIR}
                    ${BOTLIB_DIR}
                    ${CMAKE_SOURCE_DIR}/itest/test_game_screen)

add_executable(test_game_screen itest_test_game_screen_app.cpp
                                test_game_screen_main.cpp)

set_property(TARGET test_game_screen PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(test_game_screen botlib commonlib GL GLEW glfw3 dl m
                          Xrandr Xi X11 Xxf86vm Xinerama Xcursor pthread)
elseif(MINGW)
    target_link_libraries(test_game_screen botlib commonlib opengl32 glfw3 glew32)
endif()

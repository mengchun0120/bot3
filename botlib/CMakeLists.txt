cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTLIB_APP_SRC
    src/app/botlib_app_config.cpp
    src/app/botlib_bot_app.cpp)

set(BOTLIB_OPENGL_SRC
    src/opengl/botlib_simple_shader_program.cpp)

set(BOTLIB_SCREEN_SRC
    src/screen/botlib_screen.cpp
    src/screen/botlib_start_screen.cpp
    src/screen/botlib_screen_manager.cpp)

set(BOTLIB_SRC
    ${BOTLIB_APP_SRC}
    ${BOTLIB_OPENGL_SRC}
    ${BOTLIB_SCREEN_SRC})

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/commonlib/include
                    include)

add_library(botlib STATIC ${BOTLIB_SRC})

set_property(TARGET botlib PROPERTY CXX_STANDARD 11)


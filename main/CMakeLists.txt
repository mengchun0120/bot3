cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall")

set(BOTMAIN_SRC
    src/bot_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(src
                    ${CMAKE_SOURCE_DIR}/commonlib/src)

add_executable(bot ${BOTMAIN_SRC})

set_property(TARGET bot PROPERTY CXX_STANDARD 11)

target_link_libraries(bot commonlib opengl32 glfw3 glew32)


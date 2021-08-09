cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(COMMONLIB_DIR ${CMAKE_SOURCE_DIR}/commonlib/src)

set(BOTMAIN_SRC
    src/bot_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(src
                    ${COMMONLIB_DIR}/misc
                    ${COMMONLIB_DIR}/math
                    ${COMMONLIB_DIR}/app
                    ${COMMONLIB_DIR}/opengl
                    ${COMMONLIB_DIR}/structure
                    ${COMMONLIB_DIR}/input)

add_executable(bot ${BOTMAIN_SRC})

set_property(TARGET bot PROPERTY CXX_STANDARD 11)

target_link_libraries(bot commonlib opengl32 glfw3 glew32)


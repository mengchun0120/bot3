cmake_minimum_required(VERSION 3.10)

project(bot CXX)

set(BOTLIB_DIR
    ${CMAKE_SOURCE_DIR}/botlib/accessor
    ${CMAKE_SOURCE_DIR}/botlib/ai
    ${CMAKE_SOURCE_DIR}/botlib/app
    ${CMAKE_SOURCE_DIR}/botlib/gameobj
    ${CMAKE_SOURCE_DIR}/botlib/gameutils
    ${CMAKE_SOURCE_DIR}/botlib/map_generator
    ${CMAKE_SOURCE_DIR}/botlib/misc
    ${CMAKE_SOURCE_DIR}/botlib/opengl
    ${CMAKE_SOURCE_DIR}/botlib/screen
    ${CMAKE_SOURCE_DIR}/botlib/shape
    ${CMAKE_SOURCE_DIR}/botlib/template
    ${CMAKE_SOURCE_DIR}/botlib/widget)

set(COMMONLIB_DIR
    ${CMAKE_SOURCE_DIR}/commonlib/app
    ${CMAKE_SOURCE_DIR}/commonlib/base
    ${CMAKE_SOURCE_DIR}/commonlib/input
    ${CMAKE_SOURCE_DIR}/commonlib/math
    ${CMAKE_SOURCE_DIR}/commonlib/misc
    ${CMAKE_SOURCE_DIR}/commonlib/opengl
    ${CMAKE_SOURCE_DIR}/commonlib/structure)

add_subdirectory(commonlib)
add_subdirectory(botlib)
add_subdirectory(app)
add_subdirectory(unittest)
add_subdirectory(itest)

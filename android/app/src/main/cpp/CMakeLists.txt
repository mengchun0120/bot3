cmake_minimum_required(VERSION 3.22.1)

project("robot")

set(DEPENDENCIES_INCLUDE_DIR "../../../../../dependencies/include")

set(COMMONLIB_SRC_DIR "../../../../../commonlib")
include(${COMMONLIB_SRC_DIR}/commonlib.cmake)

set(BOTLIB_SRC_DIR "../../../../../botlib")
include(${BOTLIB_SRC_DIR}/botlib.cmake)

include_directories(
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
    ${DEPENDENCIES_INCLUDE_DIR}
    "."
)

add_definitions(-DENABLE_LOG)

find_library(
    log-lib
    log
)

find_package(game-activity REQUIRED CONFIG)

add_library(
    robot
    SHARED
    main.cpp
    androidlib_android_out.cpp
    androidlib_robot_app.cpp
    AndroidOut.cpp
    Renderer.cpp
    Shader.cpp
    TextureAsset.cpp
    Utility.cpp
    ${COMMONLIB_SOURCE_FILES}
    ${BOTLIB_SOURCE_FILES}
)

target_link_libraries(
    robot
    android
    game-activity::game-activity
    EGL
    GLESv3
    jnigraphics
    ${log-lib}
)
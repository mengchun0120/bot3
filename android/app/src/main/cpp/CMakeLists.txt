cmake_minimum_required(VERSION 3.22.1)

project("robot")

set(dependencies_include_dir "../../../../../dependencies/include")

set(commonlib_src_dir "../../../../../commonlib")
include(${commonlib_src_dir}/commonlib.cmake)

set(botlib_src_dir "../../../../../botlib")
include(${botlib_src_dir}/botlib.cmake)

include_directories(
    ${commonlib_include_dir}
    ${botlib_include_dir}
    ${dependencies_include_dir}
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
    AndroidOut.cpp
    Renderer.cpp
    Shader.cpp
    TextureAsset.cpp
    Utility.cpp
    ${commonlib_source_files}
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
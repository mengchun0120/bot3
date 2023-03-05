cmake_minimum_required(VERSION 3.22.1)

include(${COMMONLIB_SRC_DIR}/commonlib.cmake)
include(${BOTLIB_SRC_DIR}/botlib.cmake)

add_subdirectory(testmap)
add_subdirectory(testshape)
add_subdirectory(testwidget)


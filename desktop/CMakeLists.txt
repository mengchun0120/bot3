cmake_minimum_required(VERSION 3.22.1)

project(bot CXX)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG -std=c++11")

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(COMMONLIB_SRC_DIR ${CMAKE_SOURCE_DIR}/../commonlib)
set(COMMONLIB_BUILD_DIR ${BUILD_DIR}/commonlib)

set(BOTLIB_SRC_DIR ${CMAKE_SOURCE_DIR}/../botlib)
set(BOTLIB_BUILD_DIR ${BUILD_DIR}/botlib)

add_definitions(${CPP_COMPILE_FLAG})

add_subdirectory(${COMMONLIB_SRC_DIR} ${COMMONLIB_BUILD_DIR})
add_subdirectory(${BOTLIB_SRC_DIR} ${BOTLIB_BUILD_DIR})
#add_subdirectory(app)
add_subdirectory(unittest)
add_subdirectory(itest)

cmake_minimum_required(VERSION 3.22.1)

include(commonlib.cmake)

include_directories(${COMMONLIB_INCLUDE_DIR})

add_library(commonlib STATIC ${COMMONLIB_SOURCE_FILES})


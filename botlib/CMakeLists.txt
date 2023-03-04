cmake_minimum_required(VERSION 3.22.1)

include(botlib.cmake)
include(${COMMONLIB_SRC_DIR}/commonlib.cmake)

include_directories(
    ${BOTLIB_INCLUDE_DIR}
    ${COMMONLIB_INCLUDE_DIR}
)

add_library(botlib STATIC ${BOTLIB_SOURCE_FILES})

#set_property(TARGET botlib PROPERTY CXX_STANDARD 11)

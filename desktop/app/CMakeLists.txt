cmake_minimum_required(VERSION 3.22.1)

include(${COMMONLIB_SRC_DIR}/commonlib.cmake)
include(${BOTLIB_SRC_DIR}/botlib.cmake)

set(BOT_SRC
    bot_main.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(bot bot_main.cpp)

target_link_libraries(bot botlib commonlib ${LIB})


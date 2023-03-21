cmake_minimum_required(VERSION 3.22.1)

set(SHOWMAP_SRC
    show_map_main.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(showmap ${SHOWMAP_SRC})

target_link_libraries(showmap botlib commonlib ${LIB})

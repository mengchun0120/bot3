cmake_minimum_required(VERSION 3.22.1)

set(RUNGAME_SRC
    rungame_main.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(rungame rungame_main.cpp)

target_link_libraries(rungame botlib commonlib ${LIB})

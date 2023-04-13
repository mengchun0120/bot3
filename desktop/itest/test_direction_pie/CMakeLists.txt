cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(
    test_direction_pie
    test_direction_pie_main.cpp
)

target_link_libraries(test_direction_pie botlib commonlib ${LIB})

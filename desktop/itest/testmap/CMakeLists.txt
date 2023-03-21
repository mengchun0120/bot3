cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(testmap test_map_main.cpp)

target_link_libraries(testmap botlib commonlib ${LIB})

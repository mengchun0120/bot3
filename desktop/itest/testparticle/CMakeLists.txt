cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(
    testparticle
    test_particle_main.cpp
)

target_link_libraries(testparticle botlib commonlib ${LIB})

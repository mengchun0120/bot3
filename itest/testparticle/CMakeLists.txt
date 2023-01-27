cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

add_definitions(${CPP_COMPILE_FLAG})

include_directories(. ${COMMONLIB_DIR} ${BOTLIB_DIR})

add_executable(testparticle
    itest_particle_shader_program.cpp
    itest_test_particle_app.cpp
    test_particle_main.cpp
)

set_property(TARGET testparticle PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(testparticle botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor pthread)
elseif(MINGW)
    target_link_libraries(testparticle botlib commonlib opengl32 glfw3 glew32)
endif()

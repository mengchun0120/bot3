cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${CMAKE_SOURCE_DIR}/commonlib/include
                    ${CMAKE_SOURCE_DIR}/botlib/include
                    ${CMAKE_SOURCE_DIR}/itest/testshape)

add_executable(testshape testshape_testshape_app.cpp
                         testshape_main.cpp)

set_property(TARGET testshape PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(testshape botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor pthread)
elseif(MINGW)
    target_link_libraries(testshape botlib commonlib opengl32 glfw3 glew32)
endif()

cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(UNITTEST_BOTLIB_SRC
    test_botlib_game_utils.cpp
    test_botlib_main.cpp)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(${COMMONLIB_DIR}
                    ${BOTLIB_DIR}
                    ${CMAKE_SOURCE_DIR}/unittest/botlib)

add_executable(test_botlib ${UNITTEST_BOTLIB_SRC})

set_property(TARGET test_botlib PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(test_botlib botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor)
elseif(MINGW)
    target_link_libraries(test_botlib botlib commonlib opengl32 glfw3 glew32)
endif()


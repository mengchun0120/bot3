cmake_minimum_required(VERSION 3.22.1)

list(APPEND
    UNITTEST_BOTLIB_SRC
    test_botlib_main.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(test_botlib ${UNITTEST_BOTLIB_SRC})

if(UNIX)
    target_link_libraries(test_botlib botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor)
elseif(MINGW)
    target_link_libraries(test_botlib botlib commonlib opengl32 glfw3 glew32)
endif()


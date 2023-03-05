cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(
    testwidget
    itest_testwidget_app.cpp
    testwidget_main.cpp
)

if(UNIX)
    target_link_libraries(testwidget botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor pthread)
elseif(MINGW)
    target_link_libraries(testwidget botlib commonlib opengl32 glfw3 glew32)
endif()

cmake_minimum_required(VERSION 3.10)

set(CPP_COMPILE_FLAG "-g -Wall -DENABLE_LOG")

set(BOTMAIN_SRC
    bot_app.cpp
    bot_main.cpp
)

add_definitions(${CPP_COMPILE_FLAG})

include_directories(. ${COMMONLIB_DIR} ${BOTLIB_DIR})

add_executable(bot ${BOTMAIN_SRC})

set_property(TARGET bot PROPERTY CXX_STANDARD 11)

if(UNIX)
    target_link_libraries(bot botlib commonlib GL GLEW glfw3 dl m Xrandr
                          Xi X11 Xxf86vm Xinerama Xcursor pthread)
elseif(MINGW)
    target_link_libraries(bot botlib commonlib opengl32 glfw3 glew32)
endif()


cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(testmap itest_testmap_app.cpp testmap_main.cpp)

if(UNIX)
    target_link_libraries(testmap botlib commonlib ${LIB})
elseif(MINGW)
    target_link_libraries(testmap botlib commonlib ${LIB})
endif()

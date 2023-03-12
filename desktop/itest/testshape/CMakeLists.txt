cmake_minimum_required(VERSION 3.22.1)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(testshape testshape_main.cpp)

if(UNIX)
    target_link_libraries(testshape botlib commonlib ${LIB})
elseif(MINGW)
    target_link_libraries(testshape botlib commonlib ${LIB})
endif()

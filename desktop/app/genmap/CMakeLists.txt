cmake_minimum_required(VERSION 3.22.1)

list(APPEND
    GENMAP_SRC
    gen_map_main.cpp
)

include_directories(
    .
    ${COMMONLIB_INCLUDE_DIR}
    ${BOTLIB_INCLUDE_DIR}
)

add_executable(genmap ${GENMAP_SRC})

if(UNIX)
    target_link_libraries(genmap botlib commonlib ${LIB})
elseif(MINGW)
    target_link_libraries(genmap botlib commonlib ${LIB})
endif()


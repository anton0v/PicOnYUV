cmake_minimum_required(VERSION 3.15)

project(PicOnYUV)

set(SOURCES src/Main.cpp
            src/Bitmap.cpp)

set(HEADERS src/include/Bitmap.h)

set(RES_DIST_PATH ${CMAKE_CURRENT_BINARY_DIR}/res)

add_executable(Test ${SOURCES} ${HEADERS})

target_include_directories(Test PUBLIC src/include/)

add_custom_target(copy_asset
    COMMAND ${CMAKE_COMMAND} 
    -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res/
    ${RES_DIST_PATH}
)

add_dependencies(Test copy_asset)
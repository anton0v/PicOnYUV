cmake_minimum_required(VERSION 3.15)

project(PicOnYUV)

set(SOURCES src/Main.cpp
            src/Bitmap.cpp
            src/YUVFrame.cpp
            src/Convertion.cpp)

set(HEADERS src/include/Bitmap.h
            src/include/YUVFrame.h
            src/include/Convertion.h)

set(RES_DIST_PATH ${CMAKE_CURRENT_BINARY_DIR}/res)

add_executable(PicOnYUV ${SOURCES} ${HEADERS})

target_include_directories(PicOnYUV PUBLIC src/include/)

#copy assets to build tree
add_custom_target(copy_asset
    COMMAND ${CMAKE_COMMAND} 
    -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res/
    ${RES_DIST_PATH}
)

add_dependencies(PicOnYUV copy_asset)
cmake_minimum_required(VERSION 3.10)
project(alinalib)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB SOURCES "${SRC_DIR}/*.c")

add_library(${PROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_NAME} ${LIB_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/sdl2")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_mixer_LIBRARIES} ${SDL2_TTF_LIBRARIES})

add_subdirectory(examples)

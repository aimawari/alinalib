cmake_minimum_required(VERSION 3.10)
project(alinalib)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(SDL2 REQUIRED)

file(GLOB SOURCES "src/*.c")
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}/include
                           ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

add_subdirectory(examples)

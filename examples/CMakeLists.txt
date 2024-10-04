cmake_minimum_required(VERSION 3.10)

include_directories(../ .)

add_executable(testfile testfile.c)

target_link_libraries(testfile alinalib)

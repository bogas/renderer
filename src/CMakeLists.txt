cmake_minimum_required(VERSION 3.0.0)
project(renderer VERSION 0.1.0)

link_directories(../tga)
include_directories(../tga)
add_executable(renderer main.cpp ObjReader.cpp Renderer.cpp)
target_link_libraries(renderer libtga.a)

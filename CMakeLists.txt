cmake_minimum_required(VERSION 3.0.0)
project(renderer VERSION 0.1.0)

include(CTest)
enable_testing()

#add_subdirectory(TGA)
link_directories(tga)
include_directories(tga)
add_executable(renderer main.cpp)
target_link_libraries(renderer libtga.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

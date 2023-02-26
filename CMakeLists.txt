cmake_minimum_required(VERSION 3.24)
project(fwnet)

set(CMAKE_CXX_STANDARD 17)
link_libraries(libeasyx.a)
add_executable(fwnet main.cpp quadtree.h paint.h)

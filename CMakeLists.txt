cmake_minimum_required(VERSION 3.22)

project(SO-1)

include_directories(components/include)

add_executable(SO-1 src/main.cpp components/instance.cpp components/scaling.cpp)
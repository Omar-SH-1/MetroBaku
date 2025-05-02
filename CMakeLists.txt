cmake_minimum_required(VERSION 3.22.1)
project(MetroBaku)

set(CMAKE_CXX_STANDARD 20)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
add_library(metro metrobaku.cpp)
target_include_directories(metro PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(MetroBaku main.cpp)
target_link_libraries(MetroBaku PRIVATE metro)

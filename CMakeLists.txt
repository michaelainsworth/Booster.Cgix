cmake_minimum_required(VERSION 2.6)
project(booster_cgix)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
include_directories("${CMAKE_SOURCE_DIR}/src/lib")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")

cmake_minimum_required(VERSION 2.6)
project(booster_cgix)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
include_directories("${CMAKE_SOURCE_DIR}/lib")

file(GLOB lib_headers "${CMAKE_SOURCE_DIR}/lib/booster/cgix/*.hpp")
file(GLOB lib_sources "${CMAKE_SOURCE_DIR}/lib/booster/cgix/*.cpp")

add_library(booster_cgix ${lib_sources} ${lib_headers})
target_link_libraries(booster_cgix "${Boost_LIBRARIES}")

#file(GLOB test_sources "${CMAKE_SOURCE_DIR}/test/booster/cgix/*/*.cpp")
#add_executable(booster_cgix_test ${test_sources})
#target_link_libraries(booster_cgix_test booster_unit_test_framework)

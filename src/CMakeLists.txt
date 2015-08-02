# Enable testing.
enable_testing()

# Make sure we're using C++11.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# Add support for core Boost libraries.
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# Allow angular-bracket includes, like: #include <booster/cgix/whatever.hpp>
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Compile the library.
file(GLOB lib_headers "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.hpp")
file(GLOB lib_sources "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.cpp")
add_library(booster_cgix ${lib_sources} ${lib_headers})
target_link_libraries(booster_cgix "${Boost_LIBRARIES}")

#file(GLOB test_sources "${CMAKE_SOURCE_DIR}/test/booster/cgix/*/*.cpp")
#add_executable(booster_cgix_test ${test_sources})
#target_link_libraries(booster_cgix_test booster_unit_test_framework)

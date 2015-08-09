# Make sure we're using C++11.
if(${UNIX})
    if(${APPLE})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    else(${APPLE})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
    endif(${APPLE})
endif(${UNIX})

# Add support for core Boost libraries.
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# Allow angular-bracket includes, like: #include <booster/cgix/whatever.hpp>
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Compile the library.
file(GLOB lib_headers "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.hpp")
file(GLOB lib_sources "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.cpp")
add_library(booster_cgix ${lib_sources} ${lib_headers})
target_link_libraries(booster_cgix "${Boost_LIBRARIES}")

# Enable testing.
enable_testing()
file(GLOB test_sources "${CMAKE_CURRENT_SOURCE_DIR}/test/booster/cgix/*.cpp")
foreach(test_source ${test_sources})
    get_filename_component(test_filename "${test_source}" NAME)
    string(REGEX REPLACE "\\.cpp$" "" test_target "${test_filename}")
    add_executable("test_${test_target}" ${test_source})
    target_link_libraries("test_${test_target}" ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SYSTEM_LIBRARY} booster_cgix)
    add_test("test_${test_target}" "test_${test_target}")
endforeach(test_source)

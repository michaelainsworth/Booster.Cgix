file(GLOB lib_headers "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.hpp")
file(GLOB lib_sources "${CMAKE_CURRENT_SOURCE_DIR}/lib/booster/cgix/*.cpp")

add_library(booster_cgix ${lib_sources} ${lib_headers})
target_link_libraries(booster_cgix "${Boost_LIBRARIES}")

#file(GLOB test_sources "${CMAKE_SOURCE_DIR}/test/booster/cgix/*/*.cpp")
#add_executable(booster_cgix_test ${test_sources})
#target_link_libraries(booster_cgix_test booster_unit_test_framework)

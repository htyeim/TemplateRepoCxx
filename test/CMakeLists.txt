# for each "test/atest_x.cpp", generate target "atest_x"
file(GLOB_RECURSE all_tests atest_*.cpp)
foreach(v ${all_tests})
    string(REGEX MATCH "test/.*" relative_path ${v})
    # message(${relative_path})
    string(REGEX REPLACE "test/" "" target_name ${relative_path})
    string(REGEX REPLACE ".cpp" "" target_name ${target_name})

    add_executable(${target_name} ${v})
endforeach()


# manual target (not start with "atest_")
find_package(GTest)
find_package(glog)

add_executable(test_g test_g.cpp)
target_link_libraries(test_g GTest::GTest glog::glog)

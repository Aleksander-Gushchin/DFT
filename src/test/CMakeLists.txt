enable_testing()

add_executable(test test.cpp)
include(GoogleTest)
target_include_directories(test PRIVATE ../lib)
target_link_libraries(test PRIVATE 
	${lib} 
	GTest::gtest_main)
target_compile_features(test PRIVATE cxx_std_17)
gtest_discover_tests(test)
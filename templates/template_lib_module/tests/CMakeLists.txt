add_executable(mflower_MODULE_NAME_test
	main_test.cpp)

target_include_directories(mflower_MODULE_NAME_test
	PUBLIC ../include
	PRIVATE ../src
	)

target_link_libraries(mflower_MODULE_NAME_test
    PRIVATE
	project_options
    project_warnings
	PUBLIC
	Catch2::Catch2)


include(CTest)
include(Catch)
catch_discover_tests(mflower_MODULE_NAME_test)

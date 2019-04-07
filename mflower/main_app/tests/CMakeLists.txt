add_executable(mflower_dev_main_app_test main_app_test.cpp)

target_include_directories(mflower_dev_main_app_test
	PUBLIC ../include
	PRIVATE ../src
	)

target_link_libraries(mflower_dev_main_app_test
    PRIVATE
	project_options
    project_warnings
	PUBLIC
	Catch2::Catch2)


include(CTest)
include(Catch)
catch_discover_tests(mflower_dev_main_app_test)




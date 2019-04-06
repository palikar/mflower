add_library(mflower_MODULE_NAME
	src/main.cpp
	)


target_include_directories(mflower_MODULE_NAME
	PUBLIC include
	PRIVATE src
	)

target_link_libraries(mflower_MODULE_NAME
    PRIVATE
	project_options
    project_warnings
	PUBLIC
	Threads::Threads
	fmt::fmt
	spdlog::spdlog
	)



install(TARGETS mflower_MODULE_NAME
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)





if(ENABLE_TESTING)
	add_subdirectory(tests)
endif()

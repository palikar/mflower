add_executable(mflower_main_app
	src/main.cpp
	)


target_include_directories(mflower_main_app
	PUBLIC include
	PRIVATE src
	)


target_link_libraries(mflower_main_app
    PRIVATE
	project_options
    project_warnings
	PUBLIC
	absl::flat_hash_map
	Threads::Threads
	fmt::fmt
	spdlog::spdlog
	)


install(TARGETS mflower_main_app
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/mflower/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
	INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/mflower/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR}
	)




if(ENABLE_TESTING)
	add_subdirectory(tests)
endif()

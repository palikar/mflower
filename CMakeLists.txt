cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

include(GNUInstallDirs)

project(mflower LANGUAGES CXX)

find_program(CCACHE ccache)
if(CCACHE)
		set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(project_warnings INTERFACE)
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_17)
target_include_directories(project_options INTERFACE include external)


option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
option(ONLY_COVERAGE "Build only tests necessary for coverage" FALSE)
if(ONLY_COVERAGE OR ENABLE_COVERAGE)
    target_compile_options(project_options INTERFACE --coverage -O0 -g)
    target_link_libraries(project_options INTERFACE --coverage)
endif()



option(ENABLE_ASAN "Enable address sanitizer" FALSE)
if(ENABLE_ASAN)
    target_compile_options(project_options INTERFACE -fsanitize=address)
    target_link_libraries(project_options INTERFACE -fsanitize=address)
endif()



option(ENABLE_FUZZERS "Enable fuzz testing tools" FALSE)
if(ENABLE_FUZZERS)
    # add_executable(elf_reader_fuzzer test/elf_reader_fuzzer.cpp)
    # target_link_libraries(elf_reader_fuzzer
    #     PRIVATE project_options
    #     project_warnings
    #     compiler
    #     -fsanitize=address,fuzzer)
    # target_compile_options(elf_reader_fuzzer
    #     INTERFACE -fsanitize=address,fuzzer)
endif()


target_compile_options(project_warnings
    INTERFACE
		-Wall
    -Wextra 
    -Wshadow)


option(ALL_WARNINGS "Enable all waring that the compiler supports" FALSE)
if(${ALL_WARNINGS})
		target_compile_options(project_warnings
				INTERFACE
				-Wnon-virtual-dtor
				-Wold-style-cast 
				-Wcast-align 
				-Wunused 
				-Woverloaded-virtual
				-Wpedantic 
				-Wconversion
				-Wsign-conversion 
				-Wnull-dereference
				-Wdouble-promotion                         
				-Wformat=2)
endif()


option(LIBCPP "Build with libc++" FALSE)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND ${ALL_WARNINGS})
    target_compile_options(project_warnings INTERFACE
				-Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches
				-Wlogical-op
				-Wuseless-cast)
    target_link_libraries(project_options INTERFACE stdc++fs)
else()
    if(LIBCPP)
				target_compile_options(project_options INTERFACE -stdlib=libc++)
    else()
				target_link_libraries(project_options INTERFACE stdc++fs)
		endif()
endif()


option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)

option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
if(ENABLE_CLANG_TIDY)
		find_program(CLANGTIDY clang-tidy)
		if(CLANGTIDY)
				set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
		else()
				message(SEND_ERROR "clang-tidy requested but executable not found")
		endif()
endif()

option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)
if(ENABLE_CPPCHECK)
		find_program(CPPCHECK cppcheck)
		if(CPPCHECK)
				set(CMAKE_CXX_CPPCHECK
						${CPPCHECK}
						--suppress=syntaxError
						--enable=all
						--inconclusive)
		else()
				message(SEND_ERROR "cppcheck requested but executable not found")
		endif()
endif()


add_subdirectory(libs)

#
# Project setup
#

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(MFLOWER_LIB_SRCS
		src/operations.cpp
		src/scope.cpp
		src/shape.cpp
		src/tensor.cpp)

add_library(mflower_lib ${MFLOWER_LIB_SRCS})
target_link_libraries(mflower_lib
    PRIVATE project_options project_warnings)
target_include_directories(mflower_lib PUBLIC ./include PRIVATE ./src)
target_link_libraries(mflower_lib
    PRIVATE Threads::Threads)


add_executable(flow_test src/flow.cpp)
target_link_libraries(flow_test
    PRIVATE project_options project_warnings)
target_link_libraries(flow_test
    PUBLIC mflower_lib)


install(TARGETS mflower_lib
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    RUNTIME DESTINATION       ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION      ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/
    ARCHIVE DESTINATION       ${CMAKE_INSTALL_SHAREDSTATEDIR}
    )

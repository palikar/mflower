cmake_minimum_required(VERSION 3.10)
project(mflower-dev LANGUAGES CXX)

include(cmake/safeguards.cmake)

include(GNUInstallDirs)



option(ONLY_COVERAGE "Build only tests necessary for coverage" FALSE)
option(LIBCPP "Build with libc++" FALSE)
option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
option(ENABLE_ASAN "Enable address sanitizer" FALSE)
option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)
option(ENABLE_TESTING "Enable the building of the test" FALSE)
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)



add_library(project_warnings INTERFACE)
add_library(project_options INTERFACE)



target_compile_features(project_options INTERFACE cxx_std_17)

if(ONLY_COVERAGE OR ENABLE_COVERAGE)
    target_compile_options(project_options INTERFACE --coverage -O0 -g)
    target_link_libraries(project_options INTERFACE --coverage)
endif()


if(ENABLE_ASAN)
    target_compile_options(project_options INTERFACE -fsanitize=address)
    target_link_libraries(project_options INTERFACE -fsanitize=address)
endif()




target_compile_options(project_warnings
    INTERFACE -Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic  -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 )


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(project_warnings
        INTERFACE -Wmisleading-indentation  -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)
    target_link_libraries(project_options INTERFACE stdc++fs)
endif()


find_program(CCACHE ccache)
if(CCACHE)
	set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()


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

if(ENABLE_CLANG_TIDY)
	find_program(CLANGTIDY clang-tidy)
	if(CLANGTIDY)
		set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
	else()
		message(SEND_ERROR "clang-tidy requested but executable not found")
	endif()
endif()


if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check(REQUIRED)
conan_cmake_run(CONANFILE
	conanfile.txt
	BASIC_SETUP
	CONAN_COMMAND
	${CONAN_CMD}
	CMAKE_TARGETS
	BUILD
	missing)



if(CONAN_CATCH2_ROOT_DEBUG)
	include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
	include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()
find_package(Catch2 REQUIRED)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


# find_package(rang REQUIRED)

find_package(fmt)

find_package(spdlog)


if(ENABLE_TESTING)
	enable_testing()
endif()



set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)


add_subdirectory(libs)
add_subdirectory(mflower-dev)



message("#########################################")
message("\t \t Summary")
message("#########################################")
message("Build type:       \t ${CMAKE_BUILD_TYPE}")
message("Install prefix:   \t ${CMAKE_INSTALL_PREFIX}")
message("Testing enabled:  \t ${ENABLE_TESTING}")
message("Clang-tidy:       \t ${ENABLE_CLANG_TIDY}")
message("Cppcheck:         \t ${ENABLE_CPPCHECK}")
message("Compiler:         \t ${CMAKE_CXX_COMPILER_ID}")
message("Sanizizers:       \t ${ENABLE_ASAN}")
message("Shared libs:      \t ${BUILD_SHARED_LIBS}")
message("Build libcpp:     \t ${LIBCPP}")
message("------------------------------------------")
message("Version:        \t ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("########################################")


####################################################
##############    Available Targets   ##############
####################################################
# Catch2::Catch2 
####################################################
# absl::base
# absl::algorithm
# absl::debugging
# absl::flat_hash_map
# absl::memory
# absl::meta
# absl::numeric
# absl::strings
# absl::synchronization
# absl::time
# absl::utility
####################################################
# Threads::Threads
####################################################
# fmt::fmt
####################################################
# spdlog::spdlog

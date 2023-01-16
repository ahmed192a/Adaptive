cmake_minimum_required(VERSION 3.20)
project(
  Adaptive_Platform 
  VERSION 0.1.0
  LANGUAGES CXX)



# This AUTOSAR Adaptive Platform requires C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable 'rdyamic' switch to export the executable's symbols for debugging
set(CMAKE_ENABLE_EXPORTS 1)

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set the install prefix folder
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set (CMAKE_INSTALL_INCLUDEDIR ${CMAKE_BINARY_DIR}/install/include)
set (CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR}/install/lib)
set (CMAKE_INSTALL_BINDIR ${CMAKE_BINARY_DIR}/install/bin)

########################################################################
#
# Dependencies:
# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()
add_subdirectory(cmake)

# set option BUILD_TESTS to ON to build tests
option(BUILD_TESTS "Build tests" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# set option BUILD_TESTS to ON to build tests
set (BUILD_TESTS ON)
set (ENABLE_COVERAGE ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as no build type was specified")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (NOT BUILD_TESTS)
        message(FATAL_ERROR "Tests must be enabled for code coverage!")
    endif (NOT BUILD_TESTS)
    
    include(cmake/CodeCoverage.cmake)
    
    append_coverage_compiler_flags()
    # exclude /usr/include/, Testing and _deps folders from coverage
    set(COVERAGE_EXCLUDES "/usr/include/\\*;${CMAKE_BINARY_DIR}/Testing/\\*;${CMAKE_BINARY_DIR}/_deps/\\*;${CMAKE_SOURCE_DIR}/App/\\*")
    
    setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
else (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)


# The compiled library code is here
add_subdirectory(src)
add_subdirectory(App)


## For Subsystem testing

# add_subdirectory(test_partial_processes/SAM/server)
# add_subdirectory(test_partial_processes/SD_TEST/server)
# add_subdirectory(test_partial_processes/SD_TEST/client)
# add_subdirectory(test_partial_processes/SD_TEST/SD)
# add_subdirectory(test_partial_processes/SD_TEST/ucm_client)
# add_subdirectory(test_partial_processes/SD_TEST/ucm_server)
# add_subdirectory(test_partial_processes/SD_TEST/Classic)

# add_subdirectory(test_partial_processes/SomeIP/some_client)
# add_subdirectory(test_partial_processes/SomeIP/some_server)




# copy manifest files to the build directory
file(COPY App/Manifests DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App)
file(COPY App/UCM/sw_packages.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/processes/UCM_SERVER)
file(COPY App/UCM/config.conf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/processes/UCM_SERVER)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/App/processes/redirected)



enable_testing()

# option for unit testing
add_subdirectory(Testing)


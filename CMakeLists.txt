cmake_minimum_required(VERSION 3.0.0)
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

########################################################################
#
# Dependencies:
# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()


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
file(COPY App/UCM/config.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/processes/UCM_SERVER)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/App/processes/redirected)




# option for unit 0testing
option(build_tests "Build all the tests.")
set(build_tests ON)
message(STATUS "print_all_variables------------------------------------------${build_tests}")
add_subdirectory(Testing)


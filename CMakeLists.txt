cmake_minimum_required(VERSION 3.0.0)
project(
  Adaptive_Platform 
  VERSION 0.1.0
  LANGUAGES CXX)



# This AUTOSAR Adaptive Platform requires C++17
set(CMAKE_CXX_STANDARD 17)
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
# add_subdirectory(test_partial_processes/SAM/server)
add_subdirectory(test_partial_processes/SD_TEST/server)
add_subdirectory(test_partial_processes/SD_TEST/client)
add_subdirectory(test_partial_processes/SD_TEST/SD)
add_subdirectory(test_partial_processes/SD_TEST/ucm_client)
add_subdirectory(test_partial_processes/SD_TEST/ucm_server)


# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY src/processes)



# add_executable(
#   SOMEIP_SP
#   test_partial_processes/server_someip.cpp
#   ${SRC_FILES}
# )
# target_link_libraries(
#   SOMEIP_SP
#   PUBLIC
#   ara
#   nlohmann_json::nlohmann_json

# )
# add_executable(
#   SOMEIP_CP
#   test_partial_processes/client_someip.cpp
#   ${SRC_FILES}
# )
# target_link_libraries(
#   SOMEIP_CP
#   PUBLIC
#   ara
#   nlohmann_json::nlohmann_json
  
# )



# option for testing
option(build_tests "Build all the tests.")
set(build_tests ON)
message(STATUS "print_all_variables------------------------------------------${build_tests}")
add_subdirectory(Testing)


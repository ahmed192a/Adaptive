cmake_minimum_required(VERSION 3.0.0)
project(Adaptive_Platform VERSION 0.1.0)



# This AUTOSAR Adaptive Platform requires C++14
set(CMAKE_CXX_STANDARD 14)
# Enable 'rdyamic' switch to export the executable's symbols for debugging
set(CMAKE_ENABLE_EXPORTS 1)




########################################################################
#
# Dependencies:

#https://discourse.cmake.org/t/better-way-to-work-by-modules-with-cmake-and-gtest-or-any-library/3699/3
#message(STATUS "Fetching googletest")
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(googletest)

#message(STATUS "Fetching JSON library")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.9.1
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(json)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

########################################################################
#
# Source Directories:

  set(source_ara_dir
  "${CMAKE_SOURCE_DIR}/src/ara")

file(GLOB_RECURSE SRC_FILES ${source_ara_dir}/*.cpp)
file(GLOB_RECURSE HED_FILES ${source_ara_dir}/*.h)
add_library(
    ara 
    ${SRC_FILES}
    ${HED_FILES}
    )

# set_target_properties(
#   ara
#   PROPERTIES LINKER_LANGUAGE CXX
# )
target_link_libraries(
  ara
  PUBLIC
  nlohmann_json::nlohmann_json
) 

target_include_directories(
  ara 
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/exec>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/core>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/exec/parser>
)
# get executable 
add_executable(
  process1
  src/test_process.cpp
)

add_executable(
  ${PROJECT_NAME} 
  src/exec_main.cpp 
  )
target_link_libraries(
  ${PROJECT_NAME} 
  ara
)



# option for testing
option(build_tests "Build all the tests.")
set(build_tests ON)
message(STATUS "print_all_variables------------------------------------------${build_tests}")

if(build_tests)

  enable_testing()
  add_executable(
    ara_unit_test
    Testing/hello_test.cpp
  )
  target_link_libraries(
    ara_unit_test
    gtest_main
    gmock_main
    ara
    
  )

endif()

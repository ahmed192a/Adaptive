cmake_minimum_required(VERSION 3.0.0)
project(Adaptive_Platform VERSION 0.1.0)



# This AUTOSAR Adaptive Platform requires C++17
set(CMAKE_CXX_STANDARD 17)
# Enable 'rdyamic' switch to export the executable's symbols for debugging
set(CMAKE_ENABLE_EXPORTS 1)




########################################################################
#
# Dependencies:

#https://discourse.cmake.org/t/better-way-to-work-by-modules-with-cmake-and-gtest-or-any-library/3699/3
message(STATUS "Fetching googletest")
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(googletest)

message(STATUS "Fetching JSON library")
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
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/core>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/exec>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/exec/parser>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/ipc>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/ipc/server>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/ipc/client>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/proxy_skeleton>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/proxy_skeleton/skeleton>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/proxy_skeleton/SOMEIP>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/SOMEIP/entry>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/SOMEIP/option>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/com/SOMEIP/helper>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ara/sm>  
)
# get executable 
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY src/processes)
add_executable(
  process1
  src/test_process.cpp
)
target_link_libraries(
  process1
  ara
)
add_executable(
  SOMEIP_SP
  test_partial_processes/server_someip.cpp
)
target_link_libraries(
  SOMEIP_SP
  ara
)
add_executable(
  SOMEIP_CP
  test_partial_processes/client_someip.cpp
)
target_link_libraries(
  SOMEIP_CP
  ara
)
##################### SD process
add_executable(
  sd_process
  test_partial_processes/SD_TEST/SD/service_descovery.cpp
)
target_link_libraries(
  sd_process
  ara
)
##################### SD server
file(GLOB_RECURSE SD_S_SRC_FILES test_partial_processes/SD_TEST/server/lib/*.cpp)
file(GLOB_RECURSE SD_S_HED_FILES test_partial_processes/SD_TEST/server/lib/*.h)
add_library(
  server_lib 
  ${SD_S_SRC_FILES}
  ${SD_S_HED_FILES}
  )
set_target_properties(
  server_lib
  PROPERTIES LINKER_LANGUAGE CXX
)
add_executable(
  sd_server
  test_partial_processes/SD_TEST/server/server.cpp
)
target_link_libraries(
  sd_server
  ara
  server_lib
)
##################### SD client
file(GLOB_RECURSE SD_C_SRC_FILES test_partial_processes/SD_TEST/client/lib/*.cpp)
file(GLOB_RECURSE SD_C_HED_FILES test_partial_processes/SD_TEST/client/lib/*.h)
add_library(
    client_lib 
    ${SD_C_SRC_FILES}
    ${SD_C_HED_FILES}
    )
add_executable(
  sd_client
  test_partial_processes/SD_TEST/client/main.cpp
)
target_link_libraries(
  sd_client
  ara
  client_lib
)

#################################### Main APP
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY src)
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
file(GLOB_RECURSE TEST_SRC_FILES Testing/*.cpp)
if(build_tests)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY src/test)

  enable_testing()
 
  add_executable(
    ${PROJECT_NAME}-ut 
    ${TEST_SRC_FILES}
  )
  target_link_libraries(
    ${PROJECT_NAME}-ut 
    PUBLIC
    gtest
    gmock
    gtest_main
    gmock_main
    ara
  )
  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}-ut)

endif()

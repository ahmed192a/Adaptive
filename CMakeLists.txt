cmake_minimum_required(VERSION 3.0.0)
project(Adaptive_Platform VERSION 0.1.0)



# This AUTOSAR Adaptive Platform requires C++14
set(CMAKE_CXX_STANDARD 14)
# Enable 'rdyamic' switch to export the executable's symbols for debugging
set(CMAKE_ENABLE_EXPORTS 1)

include(CTest)
option(build_tests "Build all the tests." ON)


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

set(source_ara_exec_dir
  "${CMAKE_SOURCE_DIR}/src/ara/exec")
set(source_ara_core_dir
  "${CMAKE_SOURCE_DIR}/src/ara/core")



file(GLOB_RECURSE SRC_FILES ${source_ara_exec_dir}/*.cpp)
file(GLOB_RECURSE HED_FILES ${source_ara_exec_dir}/*.h)
add_library(
    ara_exec 
    ${SRC_FILES}
    ${HED_FILES}
    )
set_target_properties(
  ara_exec
  PROPERTIES LINKER_LANGUAGE CXX
)
  
file(GLOB_RECURSE CORE_SRC_FILES ${source_ara_core_dir}/*.cpp)
file(GLOB_RECURSE CORE_HED_FILES ${source_ara_core_dir}/*.h)
add_library(
    ara_core 
    ${ORE_SRC_FILES}
    ${CORE_HED_FILES} 
    )
set_target_properties(
    ara_core
    PROPERTIES LINKER_LANGUAGE CXX
)
  
  
    



target_link_libraries(
  ara_core
  ara_exec
  
)
target_link_libraries(
  ara_exec
  nlohmann_json::nlohmann_json
  
)




#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

if(build_tests)
  enable_testing()
  add_executable(
    ara_unit_test
    hello_test.cc
  )
  target_link_libraries(
    ara_unit_test
    gtest_main
  )
  include(GoogleTest)
  gtest_discover_tests(ara_unit_test)

endif()

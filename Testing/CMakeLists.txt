
message(STATUS "Fetching googletest")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if(build_tests)
  file(GLOB_RECURSE TEST_SRC_FILES ./*.cpp ./EM/*.cpp)
  # set(CMAKE_RUNTIME_OUTPUT_DIRECTORY src/test)

  enable_testing()
 
  add_executable(
    ${PROJECT_NAME}-ut 
    ${TEST_SRC_FILES}

  )
  target_compile_features(${PROJECT_NAME}-ut  PRIVATE cxx_std_17)
  target_link_libraries(
    ${PROJECT_NAME}-ut  
    PUBLIC 
    ara_lib
    gtest_main
    gmock_main
    gtest
    gmock
    )

  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}-ut)

endif()
